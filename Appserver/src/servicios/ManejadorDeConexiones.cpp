#include "ManejadorDeConexiones.h"
#include "Servidor.h"
#include "servicioRegistro.h"

#define MAXIMOS_MILISEGUNDOS_ESPERA 1000
const string HEADER_HOST = "Host";


using namespace std;



ManejadorDeConexiones::ManejadorDeConexiones(){
    mg_mgr_init(&(this->manager), NULL);
}

ManejadorDeConexiones::~ManejadorDeConexiones(){
    mg_mgr_free(&manager);
}



void ManejadorDeConexiones::iniciarConexionComoServidor(string puerto, Servidor* servidor){
    // Se bindea al localhost 8000 y se guarda la conexion
    mg_connection* conexionListening = mg_bind(&(this->manager), puerto.c_str(), this->handlerServer);
    // Configuro al manager como http
    mg_set_protocol_http_websocket(conexionListening);
    //Cada conexion que entra se va a manejar en un thread deatacheado distinto usando el handlerServer
    mg_enable_multithreading(conexionListening);
    /////////////////////////////////////////////////////////////////////
    conexionListening->user_data = servidor;

    Logger::Instance()->log(INFO,"Se inicia la conexion como Servidor en Mongoose, en el puerto " + puerto );
    this->escucharMensajes();
}


void ManejadorDeConexiones::escucharMensajes(){
    this->escuchar = true;
    while(this->escuchar){
        mg_mgr_poll(&(this->manager), MAXIMOS_MILISEGUNDOS_ESPERA);
    }
}

void ManejadorDeConexiones::terminarConexionComoServidor(){
    this->escuchar = false;
    Logger::Instance()->log(INFO,"Se termina la conexion como Servidor en Mongoose");
}


void ManejadorDeConexiones::handlerServer(struct mg_connection* conexion, int evento, void* ev_data) {

    struct mbuf* recvBuffer = &(conexion->recv_mbuf);
    struct mbuf* sendBuffer = &(conexion->send_mbuf);

    switch (evento) {
        case MG_EV_HTTP_REQUEST:
            {
                struct http_message* mensajeHTTP = (struct http_message *) ev_data;

                Logger::Instance()->log(DEBUG,"HTTP Request que llega al server:\n" + string (recvBuffer->buf, recvBuffer->len));

                /*Esto de castear a (Servidor*) lo puedo hacer porque estoy seguro que la UNICA conexion que esta listening (la misma que recibe los HTTP_REQUEST)
                  es la conexion del Servidor
                */
                string respuesta = ((Servidor*)(conexion->user_data))->getRespuestaDelServicio(MensajeHTTPRequest(mensajeHTTP));

                Logger::Instance()->log(DEBUG,"Respuesta del servicio:\n" + respuesta);
                mg_printf(conexion,"%s",StringUtil::stringToChar(respuesta));
                conexion->flags |= MG_F_SEND_AND_CLOSE;
                mbuf_remove(recvBuffer, recvBuffer->len);
            }
            break;
    }
}


string ManejadorDeConexiones::getHost(MensajeHTTPRequest* request, string puertoLocal){
    string host = request->getHeader(HEADER_HOST);

    //Si NO es un localhost, moongose tiene que recibir la direccion a la que se conecta como , por ejemplo, "t2shared.herokuapp.com:80"
    //Si SI es un localhost, moongose tiene que recibir la direccion a la que se conecta como , por ejemplo, "localhost:5000"
    if (host.find("localhost") == std::string::npos){
        host = host + ":" + puertoLocal;
    }
    return host;
}

MensajeHTTPReply ManejadorDeConexiones::enviarMensajeHTTP(MensajeHTTPRequest* request, string puertoLocal){
    //Se va a crear un manager para cada cliente, no se si traiga problemas internos pero esto permite que las conexiones como cliente se hagan MUCHO mas rapido y en paralelo
    mg_mgr managerCliente;
    mg_mgr_init(&managerCliente, NULL);

    ClienteDelSharedServer cliente;

    string direccion = this->getHost(request, puertoLocal);
/*
    string direccion = request->getHeader(HEADER_HOST);
    if (direccion != "localhost:5000"){
        direccion = direccion + ":" + puertoLocal;
    }
*/

    Logger::Instance()->log(INFO,"Direccion a la que se conecta como cliente: " + direccion);
    Logger::Instance()->log(DEBUG,"HTTP Request que se enviara:\n" + request->toString());
    mg_connection* conexionParaRegistrarse = mg_connect(&managerCliente, direccion.c_str() , this->handlerCliente);
    mg_set_protocol_http_websocket(conexionParaRegistrarse);
    conexionParaRegistrarse->user_data = &cliente;
    mg_printf(conexionParaRegistrarse,"%s", request->toString().c_str());

    while (cliente.conexionActiva){
        mg_mgr_poll(&managerCliente, MAXIMOS_MILISEGUNDOS_ESPERA);
    }

    mg_mgr_free(&managerCliente);

    //ESTO NO ES NECESARIO CON EL CLIENTE PROPIO, CONEXION ACTIVA ALCANZA
    cliente.esperarRespuesta();//aca el cliente implmenta el loop de espera

    MensajeHTTPReply respuesta = cliente.getRespuesta();
    Logger::Instance()->log(INFO,"Se obtuvo una respuesta de " + direccion);
    Logger::Instance()->log(DEBUG,"HTTP Reply de "+ direccion + ":\n"+ respuesta.toString());
    if (respuesta.getCodigo() == 0){
        Logger::Instance()->log(ERROR,"Direccion invalida: " + direccion);
    }
    return respuesta;
}


void ManejadorDeConexiones::handlerCliente(struct mg_connection* conexion, int evento, void* ev_data){
    struct mbuf* recvBuffer = &(conexion->recv_mbuf);
    struct mbuf* sendBuffer = &(conexion->send_mbuf);

    switch (evento) {
        case MG_EV_HTTP_REPLY:
            {
                //NOTA: castear el ev_data a http_message* se puede hacer aca porque el caso MG_EV_HTTP_REPLY garantiza que haya un http_message en el ev_data
                ((ClienteDelSharedServer*)conexion->user_data)->setRespuesta(MensajeHTTPReply((http_message*) ev_data));
                mbuf_remove(recvBuffer, recvBuffer->len);
                //Esto es porque ya no tiene sentido que esa conexion siga activa luego de recibir la respuesta
                conexion->flags |= MG_F_CLOSE_IMMEDIATELY;
            }
            break;
        case MG_EV_CLOSE:
            {
                ((ClienteDelSharedServer*)conexion->user_data)->terminarConexion();
            }
            break;
    }
}


