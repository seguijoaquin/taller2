#include "ServicioBusquedaCandidatos.h"

ServicioBusquedaCandidatos::ServicioBusquedaCandidatos(AdministradorCandidatos* administradorCandidatos, MensajeHTTPRequest* mensajeHTTP){
    this->administradorCandidatos = administradorCandidatos;
    this->mensajeHTTP = mensajeHTTP;

    this->atenderBusqueda();
}

ServicioBusquedaCandidatos::~ServicioBusquedaCandidatos()
{
    //dtor
}

void ServicioBusquedaCandidatos::atenderBusqueda(){
    string usuario = this->mensajeHTTP->getHeader("Usuario");
    Usuario* candidato = this->administradorCandidatos->buscarCandidatoPara(usuario);

    RespuestaDeLaBusqueda* respuestaBusqueda = new RespuestaDeLaBusqueda();
    if (candidato != nullptr){
        respuestaBusqueda->setRespuestaCandidatoEncontrado(candidato);
        delete candidato;
    }
    else{
        respuestaBusqueda->setRespuestaCandidatoNoEncontrado();
    }
    this->respuesta = respuestaBusqueda;
}
