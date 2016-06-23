#include "CreatorVotacion.h"

CreatorVotacion::CreatorVotacion(SharedDataBase* shared, Mensajero* mensajero, MensajeHTTPRequest* mensajeHTTP,SesionesDeUsuarios* sesiones,AdministradorCandidatos* administradorCandidatos){
    if ( (this->validarParametrosDeSesion(mensajeHTTP, sesiones) ) && (this->validarNotificacion(mensajeHTTP, administradorCandidatos) )  && (mensajeHTTP->tieneHeader("Resultado")) ){
        this->servicio = new ServicioVotacion(shared,mensajeHTTP,administradorCandidatos, mensajero);
    }
    else{
        this->servicio = new ServicioInexistente();
    }
}

CreatorVotacion::~CreatorVotacion()
{
    //dtor
}

bool CreatorVotacion::validarNotificacion(MensajeHTTPRequest* mensajeHTTP,AdministradorCandidatos* administradorCandidatos){

    string headerUsuario = "Usuario";
    string headerCandidato = "Candidato";

    if ( (mensajeHTTP->tieneHeader(headerUsuario)) && (mensajeHTTP->tieneHeader(headerCandidato)) ){
        string usuario = mensajeHTTP->getHeader(headerUsuario);
        string candidato = mensajeHTTP->getHeader(headerCandidato);

        return administradorCandidatos->usuarioFueNotificadoSobreCandidato(usuario, candidato);
    }
    else{
        return false;
    }

}
