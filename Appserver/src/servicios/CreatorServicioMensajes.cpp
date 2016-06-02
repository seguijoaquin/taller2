#include "CreatorServicioMensajes.h"

CreatorServicioMensajes::CreatorServicioMensajes(MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones){
    //Validar que existan estos headers
    string usuario1 = mensajeHTTP->getHeader("Usuario1");
    string tokenIngresado = mensajeHTTP->getHeader("Token");
    string usuario2 = mensajeHTTP->getHeader("Usuario2");
    string desde = mensajeHTTP->getHeader("Desde");
    string cantidad = mensajeHTTP->getHeader("Cantidad");

    //if ( (sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado) ) && (true/*chequear match*/ ) ){
    if ( (true /*sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado)*/ ) && (true/*chequear match*/ ) ){
        this->servicio = new ServicioMensajes(mensajeHTTP, sesiones,conversaciones);
    }
    else{
        this->servicio = new ServicioInexistente();
        //this->respuesta = "HTTP/1.1 400 No tiene autorizacion\r\n\r\n";
    }

}

CreatorServicioMensajes::~CreatorServicioMensajes()
{
    //dtor
}
