#include "ServicioVotacion.h"

ServicioVotacion::ServicioVotacion(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, AdministradorCandidatos* administradorCandidatos, Mensajero* mensajero){
    this->shared = shared;
    this->mensajeHTTP = mensajeHTTP;
    this->administradorCandidatos = administradorCandidatos;
    this->mensajero = mensajero;

    this->atenderVotacion();
}

ServicioVotacion::~ServicioVotacion()
{
    //dtor
}

void ServicioVotacion::atenderVotacion(){
    string usuario = this->mensajeHTTP->getHeader("Usuario");
    string candidato = this->mensajeHTTP->getHeader("Candidato");

    bool votoPositivo = ( this->mensajeHTTP->getHeader("Resultado") == "like" );

    this->administradorCandidatos->usuarioVotaAFavorDe(usuario, candidato, votoPositivo);

    if ( (votoPositivo) && (this->administradorCandidatos->hayMatchEntre(usuario,candidato)) ){
        this->mensajero->notificarUsuarioSobreMatchCon(usuario, candidato);
        this->mensajero->notificarUsuarioSobreMatchCon(candidato, usuario);
    }

    RespuestaDeLaVotacion* respuestaVotacion = new RespuestaDeLaVotacion();
    respuestaVotacion->setRespuestaSeRegistroVoto();
    this->respuesta = respuestaVotacion;
}
