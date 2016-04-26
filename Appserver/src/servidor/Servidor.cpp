#include "Servidor.h"


Servidor::Servidor(){

    iniciarManager();

/*  CON ESTO ESTUVE PROBANDO SI HAY MULTITHREADING EN LAS CONEXIONES OUTBOUND
    mg_connection* nc = mg_connect(&manager,"t2shared.herokuapp.com:80", handlerServer); //SI
    mg_set_protocol_http_websocket(nc);
    //mg_printf(nc, "GET /users/18 HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\nContent-Length: 0\r\n\r\n"); //Funciona
    mg_printf(nc, "GET /users/18 HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\n\r\n"); //Funciona


    mg_connection* nc2 = mg_connect(&manager,"t2shared.herokuapp.com:80", handlerServer); //SI
    mg_set_protocol_http_websocket(nc2);
    mg_printf(nc2, "GET /users/42 HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\n\r\n"); //Funcio


    tiempo = 0;

//Le pongo user data y veo que pasa....
    nc->user_data = (void*) 1;
    nc2->user_data = (void*) 2;
*/

    iniciarBaseDeDatos();
    escucharMensajes();
}

void Servidor::escucharMensajes(){
    /*Ahora solo sale si se cierra por la fuerza, se podria agregar que se le puede mandar un mensaje como administrador (o algo asi)
      para que lo cierre de forma ordenada
    */
    for (;;) {
        mg_mgr_poll(&(this->manager), 1000);
        //cout<<"POLL----------------------------------------------------\n";
    }
}


void Servidor::iniciarManager(){

    mg_mgr_init(&(this->manager), NULL);
    // Se bindea al localhost 8000 y se guarda la conexion
    this->conexionListening = mg_bind(&(this->manager), "8000", this->handlerServer);
    // Configuro al manager como http
    mg_set_protocol_http_websocket(this->conexionListening);
    //Cada conexion que entra se va a manejar en un thread deatacheado distinto usando el handlerServer
    mg_enable_multithreading(this->conexionListening);
    /////////////////////////////////////////////////////////////////////
    this->conexionListening->user_data = this;
}


void Servidor::iniciarBaseDeDatos(){
    //https://github.com/facebook/rocksdb/issues/957 diferentes alternativas para guardar datos, tambien se podria usar un json...
    rocksdb::Options options;
    options.create_if_missing = true;
    //Lanzar errores si fuera necesario
    //WARNING: no se si las opciones pueden perder scope antes de que se destruya la base de datos, si no puede--> options variable privada
    rocksdb::Status status = rocksdb::DB::Open(options, "./usuariosRegistrados", &(this->credencialesUsuarios));
}







string Servidor::getRespuestaDelServicio(http_message* mensajeHTTP){
    string respuesta;
    AtendedorHTTP atendedor(mensajeHTTP, &(this->tokensDeUsuarios));

    //Refactorizar: lanzarServicio(...), ademas podria hacer que Servicios hereden de una clase Servicio y subo ahi el getRespuesta
    switch (atendedor.getServicioALanzar()){
        case LANZAR_SERVICIO_REGISTRO:
            {
                //servicioRegistro registrador(&manager, mensajeHTTP, &listaUsuarios);
                servicioRegistro registrador(&(this->manager), mensajeHTTP, this->credencialesUsuarios);
                respuesta = registrador.getRespuesta();
                cout<<"RESPUESTA DEL SERVICIO REGISTRO:\n"<<respuesta<<"\n";
            }
            break;
        case LANZAR_SERVICIO_LOGIN:
            {
                servicioLogin logginer(mensajeHTTP, this->credencialesUsuarios, &(this->tokensDeUsuarios));
                respuesta = logginer.getRespuesta();
                cout<<"RESPUESTA DEL SERVICIO LOGIN:\n"<<respuesta<<"\n";
            }
            break;
        case LANZAR_SERVICIO_SIN_PERMISO:
            {
                //respuesta = CONSTANTE_MENSAJE_DE_ERROR
                respuesta = "HTTP/1.1 400 No tiene autorizacion\r\n\r\n";
            }
            break;
    }

    return respuesta;
}


void Servidor::handlerServer(struct mg_connection* conexion, int evento, void* ev_data) {

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
                string respuesta = ((Servidor*)(conexion->user_data))->getRespuestaDelServicio(mensajeHTTP);
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



Servidor::~Servidor(){
    delete this->credencialesUsuarios;
    mg_mgr_free(&manager);

}
