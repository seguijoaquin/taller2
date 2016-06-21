#include "RespuestaDeLaBusqueda.h"

RespuestaDeLaBusqueda::RespuestaDeLaBusqueda()
{
    //ctor
}

RespuestaDeLaBusqueda::~RespuestaDeLaBusqueda()
{
    //dtor
}

void RespuestaDeLaBusqueda::setRespuestaCandidatoEncontrado(Usuario* usuario){
    this->respuesta.setCodigo(200);
    this->respuesta.setMensajeDeEstado("Candidato encontrado");
    this->respuesta.agregarHeader("Content-Type", "application/json");
    this->respuesta.setBody(usuario->toString());
}

void RespuestaDeLaBusqueda::setRespuestaCandidatoNoEncontrado(){
    this->respuesta.setCodigo(201);
    this->respuesta.setMensajeDeEstado("Candidato no encontrado");
}
