#include "CreatorBusquedaCandidato.h"

CreatorBusquedaCandidato::CreatorBusquedaCandidato(AdministradorCandidatos* administradorCandidatos, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones){

    if ( this->validarParametrosDeSesion(mensajeHTTP, sesiones) ){
        this->servicio = new ServicioBusquedaCandidatos(administradorCandidatos,mensajeHTTP);
    }
    else{
        //Queda medio mal asi pero es una solucion rapida...
        if (this->servicio == nullptr){
            this->servicio = new ServicioInexistente();
        }
    }
}

CreatorBusquedaCandidato::~CreatorBusquedaCandidato()
{
    //dtor
}
