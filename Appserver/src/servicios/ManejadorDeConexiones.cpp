#include "ManejadorDeConexiones.h"
#include "Servidor.h"
#include "servicioRegistro.h"
using namespace std;


int ManejadorDeConexiones::tiempo = 0;

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

    this->escucharMensajes();
}


void ManejadorDeConexiones::escucharMensajes(){
    this->escuchar = true;
    //for (;;) {
    while(this->escuchar){
        mg_mgr_poll(&(this->manager), 1000);
        //cout<<"POLL----------------------------------------------------\n";
    }
}

void ManejadorDeConexiones::terminarConexionComoServidor(){
    this->escuchar = false;
}

void ManejadorDeConexiones::handlerServer(struct mg_connection* conexion, int evento, void* ev_data) {

    struct mbuf* recvBuffer = &(conexion->recv_mbuf);
    struct mbuf* sendBuffer = &(conexion->send_mbuf);

    /*if (evento!=0){
        cout<<"EL evento de no se quien es: "<<evento<<" \n";
    }*/

    cout<<"Conexion en el main direccion: "<<conexion<<"-----------------------\n";

    switch (evento) {
        case MG_EV_HTTP_REPLY:
            {
                /*
                    cout<<"Esto se dispara?\n";
                    printf("Lo que hay en el buffer es:\n%.*s\n", (int)recvBuffer->len,recvBuffer->buf);
                    mbuf_remove(recvBuffer, recvBuffer->len);
                    //conexion->flags |= MG_F_CLOSE_IMMEDIATELY;
                */
            }
        break;
        case MG_EV_HTTP_REQUEST:
            {

                /*Esto lo puedo hacer porque estoy seguro que la UNICA conexion que esta listening (la misma que recibe los HTTP_REQUEST)
                  es la conexion del Servidor
                */
                struct http_message* mensajeHTTP = (struct http_message *) ev_data;
                //Refactorizar: que sea una interfaz como "Recibidor de mensajes"
                string respuesta = ((Servidor*)(conexion->user_data))->getRespuestaDelServicio(MensajeHTTPRequest(mensajeHTTP));
                printf("Mensaje de llegada al server:\n%.*s\n", (int)recvBuffer->len,recvBuffer->buf);


                cout<<"ESTO ES LO QUE SE VA PRINTEAR EN EL BUFFER\n"<<respuesta<<"\n";

                mg_printf(conexion,"%s",StringUtil::stringToChar(respuesta));
                printf("Lo que hay en el sendBuffer del HTTP_REQUEST es:\n%.*s\n", (int)sendBuffer->len,sendBuffer->buf);
                conexion->flags |= MG_F_SEND_AND_CLOSE;
                //Refactorizar: limpiarElBuffer(...), tal vez en un archivo "Utilities" xq esto tambien lo va a tener que usar el registrador
                mbuf_remove(recvBuffer, recvBuffer->len);
            }
            break;
        case MG_EV_SEND:
            {
                cout<<"SE MANDO EL BUFFER\n";
            }
            break;

        case MG_EV_CONNECT:
            {
                cout<<"SE CONECTO AL SISTEMA, le escribo aca lo que tiene que mandar\n";
                /*  CON ESTO ESTUVE PROBANDO SI HAY MULTITHREADING EN LAS CONEXIONES OUTBOUND
                cout<<"El indice de CONNECT es: "<<(int)(conexion->user_data)<<"\n";
                //mbuf_remove(sendBuffer, sendBuffer->len);
                int i = 0;
                while (i < 10){
                    i++;
                    tiempo++;
                    cout<<"Tiempo en la conexion nro "<<(int)conexion->user_data<<" "<<tiempo<<" segundo\n";
                    sleep(1);
                }
                */
            }
            break;
        /*WARNING IMPORTANTE: SI ESTA EL CASE MG_EV_RECV ENTONCES SE USA ESTE EN VEZ DEL MG_EV_HTTP_REPLY
        case MG_EV_RECV:
            {
                cout<<"Se recibio algo\n";
                printf("Lo que hay en el buffer es:\n%.*s\n", recvBuffer->len,recvBuffer->buf);
                mbuf_remove(recvBuffer, recvBuffer->len);
                //mg_printf(conexion, "GET /users/18 HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\nContent-Length: 0\r\n\r\n");
            }
            break;
        */
        case MG_EV_CLOSE:
            {

                cout<<"SE CERRO LA CONEXION en el main\n";// a los "<<tiempo<<" segundos\n";
                /*  CON ESTO ESTUVE PROBANDO SI HAY MULTITHREADING EN LAS CONEXIONES OUTBOUND
                cout<<"El indice de CLOSE es: "<<(int)conexion->user_data<<"\n";
                */

            }
            break;
        default:
                /*if (evento!=0){
                    cout<<"EL evento de no se quien es: "<<evento<<" \n";
                }*/

            break;
    }
}

/*
void ManejadorDeConexiones::iniciarConexionComoCliente(string metodo, string uri, string body, string puertoLocal, string host, servicioRegistro* servicio){

    string direccion = host + ":" + puertoLocal;

    mg_connection* conexionParaRegistrarse = mg_connect(&(this->manager), direccion.c_str() , this->handlerCliente);
    mg_set_protocol_http_websocket(conexionParaRegistrarse);

    //Refactorizar// TODO, hacer que la user data sea un Servicio o que implemente una interfaz "Cliente"
    conexionParaRegistrarse->user_data = servicio;
    servicio->esperarRespuesta();

    string mensaje = metodo + " " + uri + " HTTP/1.1\r\nHost: "+host + "\r\nContent-Length: "+ StringUtil::int2string(body.length()) +"\r\nContent-Type: application/json\r\n\r\n"+body;
    mg_printf(conexionParaRegistrarse,"%s", mensaje.c_str());
}
*/



void ManejadorDeConexiones::iniciarConexionComoCliente(string metodo, string uri, string body, string puertoLocal, string host, ClienteDelSharedServer* cliente){

    string direccion = host + ":" + puertoLocal;

    mg_connection* conexionParaRegistrarse = mg_connect(&(this->manager), direccion.c_str() , this->handlerCliente);
    mg_set_protocol_http_websocket(conexionParaRegistrarse);

    //Refactorizar// TODO, hacer que la user data sea un Servicio o que implemente una interfaz "Cliente"
    conexionParaRegistrarse->user_data = cliente;

    string mensaje = metodo + " " + uri + " HTTP/1.1\r\nHost: "+host + "\r\nContent-Length: "+ StringUtil::int2string(body.length()) +"\r\nContent-Type: application/json\r\n\r\n"+body;
    mg_printf(conexionParaRegistrarse,"%s", mensaje.c_str());
    cliente->esperarRespuesta();//aca el cliente implmenta el loop de espera
}








void ManejadorDeConexiones::handlerCliente(struct mg_connection* conexion, int evento, void* ev_data){

    struct mbuf* recvBuffer = &(conexion->recv_mbuf);
    struct mbuf* sendBuffer = &(conexion->send_mbuf);


    switch (evento) {
        case MG_EV_CONNECT:
            {
                cout<<"EL REGISTRO SE CONECTO AL SERVER\n";
                cout<<"El indice de CONNECT es: "<<conexion<<"\n";
                //PARA PROBAR SI LAS CONEXIONES OUTBOUNDS SE MANEJAN EN UN MISMO THREAD
                /*int i = 0;
                while (i < 5){ //con 10seg y dos conexiones tira segmentation faults
                    i++;
                    tiempo++;
                    cout<<"Tiempo en la conexion con direccion "<<conexion<<" "<<tiempo<<" segundos\n";
                    sleep(1);
                }*/
            }
            break;

        case MG_EV_HTTP_REPLY:
            {
                cout<<"EL SERVER TIRO EL REPLY\n";
                //NOTA: castear el ev_data a http_message* se puede hacer aca porque el caso MG_EV_HTTP_REPLY garantiza que haya un http_message en el ev_data
                //TODO: Aca es en donde se tiene que setear el codigo de retorno

                //((servicioRegistro*)conexion->user_data)->setCodigoResuesta( ((http_message*) ev_data)->resp_code  );
                ((ClienteDelSharedServer*)conexion->user_data)->setRespuesta(MensajeHTTPReply((http_message*) ev_data));

                //((servicioRegistro*)conexion->user_data)->desbloquear( ((http_message*) ev_data)->resp_code );
                printf("Lo que hay en el buffer DEL REGISTRO en RECV es:\n%.*s\n", (int)recvBuffer->len,recvBuffer->buf);
                mbuf_remove(recvBuffer, recvBuffer->len);
                //Esto es porque ya no tiene sentido que esa conexion siga activa luego de recibir la respuesta
                conexion->flags |= MG_F_CLOSE_IMMEDIATELY;
            }
            break;
        case MG_EV_SEND:
            {
                cout<<"Se envio algo\n";
                printf("Lo que hay en el buffer DEL REGISTRO en SEND es:\n%.*s\n", (int)sendBuffer->len,sendBuffer->buf);
            }
            break;
        case MG_EV_CLOSE:
            {
                //cout<<"SE CERRO LA CONEXION\n";
                //Deberia setearse arriba el codigo y aca nada mas ->desbloquear()

                //((servicioRegistro*)conexion->user_data)->dejarDeEsperar();
                ((ClienteDelSharedServer*)conexion->user_data)->terminarConexion();


                //cout<<"SE CERRO LA CONEXION a los "<<tiempo<<" segundos "<<"El indice de CLOSE es: "<<conexion<<"\n";
            }
            break;
    }
}


