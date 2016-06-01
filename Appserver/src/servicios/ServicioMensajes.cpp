#include "ServicioMensajes.h"

ServicioMensajes::ServicioMensajes(MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones){
    this->mensajeHTTP = mensajeHTTP;
    this->sesiones = sesiones;
    this->conversaciones = conversaciones;

    this->atenderMensajes();
}

ServicioMensajes::~ServicioMensajes(){
    //dtor
}


void ServicioMensajes::atenderMensajes(){
    string usuario1 = this->mensajeHTTP->getHeader("Usuario1");
    string tokenIngresado = this->mensajeHTTP->getHeader("Token");

    //if (this->sesiones->validarTokenConUsuario(usuario1, tokenIngresado)){
    if (true){
        if (true){//Ahora me tengo que fijar si hubo match
            //aca SI hubo match y tengo el token correcto
            string usuario2 = this->mensajeHTTP->getHeader("Usuario2");
            string desde = this->mensajeHTTP->getHeader("Desde");
            string cantidad = this->mensajeHTTP->getHeader("Cantidad");

            Mensajes mensajes = this->conversaciones->obtenerCantidadMensajesDesdeEntre(StringUtil::str2int(cantidad),StringUtil::str2int(desde),usuario1,usuario2);
            //string mensajesPedidos = mensajes.toString();
            //delete mensajes;

            RespuestaMensajes* respuestaMensajes = new RespuestaMensajes();
            respuestaMensajes->setMensajesComoRespuesta(mensajes);
            this->respuesta = respuestaMensajes;
            //this->respuesta = "HTTP/1.1 201 OK\r\n\r\n" + mensajesPedidos;
        }
        else{
            //this->respuesta = "HTTP/1.1 400 No hubo match\r\n\r\n";
        }
    }
    else{
        //this->respuesta = "HTTP/1.1 400 No tiene autorizacion\r\n\r\n";
    }
}

/*string ServicioMensajes::getRespuesta(){
    return this->respuesta;
}*/

RespuestaDelServicio* ServicioMensajes::getRespuesta(){
    return this->respuesta;
}
