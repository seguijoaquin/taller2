#include "Servidor.h"

Servidor::Servidor(){

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
    //iniciarServidor();
}

void Servidor::iniciarServidor(){
    this->manejadorDeConexiones.iniciarConexionComoServidor("8000", this);
}


void Servidor::iniciarBaseDeDatos(){
    //this->credencialesDeUsuarios = new CredencialesDeUsuarios("./usuariosRegistrados");
    //this->conversaciones = new Conversaciones("./Conversaciones");
}





string Servidor::getRespuestaDelServicio(MensajeHTTPRequest mensajeHTTPRequest){
    //string respuesta;

    //AtendedorHTTP atendedor(mensajeHTTPRequest, &(this->sesionesDeUsuarios));
/*
    //Refactorizar: lanzarServicio(...), ademas podria hacer que Servicios hereden de una clase Servicio y subo ahi el getRespuesta
    switch (atendedor.getServicioALanzar()){
        case LANZAR_SERVICIO_REGISTRO:
            {
                servicioRegistro registrador(&(this->manejadorDeConexiones), mensajeHTTPRequest, this->credencialesDeUsuarios);
                respuesta = registrador.getRespuesta()->toString();
                delete registrador.getRespuesta();
                cout<<"RESPUESTA DEL SERVICIO REGISTRO:\n"<<respuesta<<"\n";
            }
            break;
        case LANZAR_SERVICIO_LOGIN:
            {
                servicioLogin logginer(&(this->sesionesDeUsuarios), mensajeHTTPRequest, this->credencialesDeUsuarios);
                respuesta = logginer.getRespuesta()->toString();
                delete logginer.getRespuesta();
                cout<<"RESPUESTA DEL SERVICIO LOGIN:\n"<<respuesta<<"\n";
            }
            break;
        case LANZAR_SERVICIO_CHAT:
            {
                ServicioChat chat(&(this->manejadorDeConexiones),&mensajeHTTPRequest,&(this->sesionesDeUsuarios), this->conversaciones);
                respuesta = chat.getRespuesta()->toString();
                delete chat.getRespuesta();
                cout<<"RESPUESTA DEL SERVICIO CHAT:\n"<<respuesta<<"\n";
            }
            break;
        case LANZAR_SERVICIO_MENSAJES:
            {
                ServicioMensajes mensajes(&mensajeHTTPRequest,&(this->sesionesDeUsuarios),this->conversaciones);
                respuesta = mensajes.getRespuesta()->toString();
                delete mensajes.getRespuesta();
                cout<<"RESPUESTA DEL SERVICIO MENSAJES:\n"<<respuesta<<"\n";
            }
            break;
        case LANZAR_SERVICIO_SIN_PERMISO:
            {
                //respuesta = CONSTANTE_MENSAJE_DE_ERROR
                respuesta = "HTTP/1.1 400 No tiene autorizacion\r\n\r\n";
            }
            break;
        case LANZAR_SERVICIO_TEST:
            {
                respuesta = "HTTP/1.1 200 Server online\r\n\r\n";
            }
            break;
        case LANZAR_SERVICIO_CERRAR:
            {
                //ESTO ES TEMPORAL PARA PODER OBTENER LOS REPORTES DE COVERTURA, HABRIA QUE VER QUE PASA CON LOS QUE ESTAN CONECTADOS
                respuesta = "HTTP/1.1 200 Se cerrara el server\r\n\r\n";
                this->manejadorDeConexiones.terminarConexionComoServidor();
            }
            break;
    }
*/

    Servicio* servicio = this->factoryServicios.fabricarServicio(mensajeHTTPRequest);
    string respuesta;
    if (servicio != nullptr){
        respuesta = servicio->getRespuesta()->toString();
        delete servicio->getRespuesta();
        delete servicio;
    }
    else{
        //ESTO ES TEMPORAL PARA PODER OBTENER LOS REPORTES DE COVERTURA, HABRIA QUE VER QUE PASA CON LOS QUE ESTAN CONECTADOS
        respuesta = "HTTP/1.1 200 Se cerrara el server\r\n\r\n";
        this->manejadorDeConexiones.terminarConexionComoServidor();
    }
    return respuesta;
}

Servidor::~Servidor(){
    delete this->conversaciones;
    delete this->credencialesDeUsuarios;
}
