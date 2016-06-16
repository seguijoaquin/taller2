#include "CreatorBusquedaCandidato.h"

CreatorBusquedaCandidato::CreatorBusquedaCandidato(AdministradorCandidatos* administradorCandidatos, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones){
    string usuarioEmisor = mensajeHTTP->getHeader("Usuario");
    string tokenIngresado = mensajeHTTP->getHeader("Token");
    //El resto de las validaciones

    if ( true /*sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado)*/ ){
        this->servicio = new ServicioBusquedaCandidatos(administradorCandidatos,mensajeHTTP);
    }
    else{
        this->servicio = new ServicioInexistente();
    }
}

CreatorBusquedaCandidato::~CreatorBusquedaCandidato()
{
    //dtor
}
