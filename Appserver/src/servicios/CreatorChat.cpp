#include "CreatorChat.h"

CreatorChat::CreatorChat(Mensajero* mensajero, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones){

    string usuarioEmisor = mensajeHTTP->getHeader("Usuario");
    string tokenIngresado = mensajeHTTP->getHeader("Token");
    string usuarioReceptor = mensajeHTTP->getHeader("Receptor");


    //if ( (sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado) ) && (true/*chequear match*/ ) ){
    if ( (true /*sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado)*/ ) && (true/*chequear match*/ ) ){
        this->servicio = new ServicioChat(mensajero,mensajeHTTP,sesiones, conversaciones);
    }
    else{
        this->servicio = new ServicioInexistente();
        //this->respuesta = "HTTP/1.1 400 No tiene autorizacion\r\n\r\n";
    }
}

CreatorChat::~CreatorChat()
{
    //dtor
}



