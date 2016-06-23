#include "ServicioVotacion.h"

ServicioVotacion::ServicioVotacion(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, AdministradorCandidatos* administradorCandidatos, Mensajero* mensajero, CredencialesDeUsuarios* credenciales){
    Logger::Instance()->log(INFO, "Se crea el Servicio de Votacion");
    this->shared = shared;
    this->mensajeHTTP = mensajeHTTP;
    this->administradorCandidatos = administradorCandidatos;
    this->mensajero = mensajero;
    this->credenciales = credenciales;

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

        Usuario perfilUsuario = this->shared->obtenerPerfilDelUsuario( this->credenciales->getIDSharedDe(usuario)  );
        Usuario perfilCandidato = this->shared->obtenerPerfilDelUsuario( this->credenciales->getIDSharedDe(candidato) );

        this->mensajero->notificarUsuarioSobreMatchCon(usuario, candidato, perfilCandidato.getNombre());
        this->mensajero->notificarUsuarioSobreMatchCon(candidato, usuario, perfilUsuario.getNombre());
    }

    RespuestaDeLaVotacion* respuestaVotacion = new RespuestaDeLaVotacion();
    respuestaVotacion->setRespuestaSeRegistroVoto();
    this->respuesta = respuestaVotacion;
}
