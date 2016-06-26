#include "CreatorServicio.h"

CreatorServicio::CreatorServicio(){
    this->servicio = nullptr;
}

CreatorServicio::~CreatorServicio()
{
    //dtor
}

Servicio* CreatorServicio::getServicio(){
    return this->servicio;
}

bool CreatorServicio::validarParametrosDeSesion(MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones){
    if( mensajeHTTP->tieneHeader("Usuario") && mensajeHTTP->tieneHeader("Token") ){
        string usuarioEmisor = mensajeHTTP->getHeader("Usuario");
        string tokenIngresado = mensajeHTTP->getHeader("Token");
        if ( !( sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado) ) ){
            //Queda mal modelurizado pero es una forma rapida de cubrir la respuesta
            ServicioInexistente* tokenInvalido = new ServicioInexistente();
            tokenInvalido->setRespuestaTokenInvalido();
            this->servicio = tokenInvalido;
            return false;
        }
        else{
            return true;
        }
    }
    else{
        return false;
    }
}


bool CreatorServicio::validarMatch(MensajeHTTPRequest* mensajeHTTP, AdministradorCandidatos* administrador, string headerUsuario1, string headerUsuario2){
    if (mensajeHTTP->tieneHeader(headerUsuario1) && mensajeHTTP->tieneHeader(headerUsuario2)){
        string usuario1 = mensajeHTTP->getHeader(headerUsuario1);
        string usuario2 = mensajeHTTP->getHeader(headerUsuario2);
        return (administrador->hayMatchEntre(usuario1,usuario2));
    }
    else{
        return false;
    }
}


bool CreatorServicio::validarUsuarioYPassword(MensajeHTTPRequest* mensajeHTTP){
return ( mensajeHTTP->tieneHeader("Usuario") ) && ( mensajeHTTP->tieneHeader("Password"));
}
