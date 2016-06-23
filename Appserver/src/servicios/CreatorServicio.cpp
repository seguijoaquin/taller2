#include "CreatorServicio.h"

CreatorServicio::CreatorServicio()
{
    //ctor
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
        return ( sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado) );
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
