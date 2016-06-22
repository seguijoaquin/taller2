#include "ServicioMensajes.h"

ServicioMensajes::ServicioMensajes(MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones){
    Logger::Instance()->log(INFO, "Se crea el Servicio para pedir Mensajes");
    this->mensajeHTTP = mensajeHTTP;
    this->conversaciones = conversaciones;

    this->atenderMensajes();
}

ServicioMensajes::~ServicioMensajes(){
    //dtor
}


void ServicioMensajes::atenderMensajes(){
    string usuario1 = this->mensajeHTTP->getHeader("Usuario1");
    string tokenIngresado = this->mensajeHTTP->getHeader("Token");
    string usuario2 = this->mensajeHTTP->getHeader("Usuario2");
    string desde = this->mensajeHTTP->getHeader("Desde");
    string cantidad = this->mensajeHTTP->getHeader("Cantidad");

    Mensajes mensajes = this->conversaciones->obtenerCantidadMensajesDesdeEntre(StringUtil::str2int(cantidad),StringUtil::str2int(desde),usuario1,usuario2);

    RespuestaMensajes* respuestaMensajes = new RespuestaMensajes();
    respuestaMensajes->setMensajesComoRespuesta(mensajes);
    this->respuesta = respuestaMensajes;
            //this->respuesta = "HTTP/1.1 201 OK\r\n\r\n" + mensajesPedidos;
/*        }
        else{
            //this->respuesta = "HTTP/1.1 400 No hubo match\r\n\r\n";
        }
    }
    else{
        //this->respuesta = "HTTP/1.1 400 No tiene autorizacion\r\n\r\n";
    }
*/
}

