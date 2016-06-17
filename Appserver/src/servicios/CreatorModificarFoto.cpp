#include "CreatorModificarFoto.h"

CreatorModificarFoto::CreatorModificarFoto(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, CredencialesDeUsuarios* credenciales){
    string usuarioEmisor = mensajeHTTP->getHeader("Usuario");
    string tokenIngresado = mensajeHTTP->getHeader("Token");

    if ( true /*sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado)*/ ){
        this->servicio = new ServicioModificarFoto(shared, mensajeHTTP, credenciales);
    }
    else{
        this->servicio = new ServicioInexistente();
        //this->respuesta = "HTTP/1.1 400 No tiene autorizacion\r\n\r\n";
    }
}

CreatorModificarFoto::~CreatorModificarFoto()
{
    //dtor
}
