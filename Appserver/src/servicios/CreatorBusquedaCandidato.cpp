#include "CreatorBusquedaCandidato.h"

CreatorBusquedaCandidato::CreatorBusquedaCandidato(AdministradorCandidatos* administradorCandidatos, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones){

    if ( this->validarParametrosDeSesion(mensajeHTTP, sesiones) ){
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
