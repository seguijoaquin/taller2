#include "CreatorBusquedaCandidato.h"

CreatorBusquedaCandidato::CreatorBusquedaCandidato(AdministradorCandidatos* administradorCandidatos, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones){

    //if ( true /*sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado)*/ ){
    if ( this->validarParametros(mensajeHTTP, sesiones) ){
        this->servicio = new ServicioBusquedaCandidatos(administradorCandidatos,mensajeHTTP);
    }
    else{
        this->servicio = new ServicioInexistente();
    }
}


bool CreatorBusquedaCandidato::validarParametros(MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones){

    if( mensajeHTTP->tieneHeader("Usuario") && mensajeHTTP->tieneHeader("Token") ){
        string usuarioEmisor = mensajeHTTP->getHeader("Usuario");
        string tokenIngresado = mensajeHTTP->getHeader("Token");
        return ( sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado) );
    }
    else{
        return false;
    }

}

CreatorBusquedaCandidato::~CreatorBusquedaCandidato()
{
    //dtor
}
