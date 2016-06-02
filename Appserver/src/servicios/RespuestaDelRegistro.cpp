#include "RespuestaDelRegistro.h"

RespuestaDelRegistro::RespuestaDelRegistro()
{
    //ctor
}

RespuestaDelRegistro::~RespuestaDelRegistro()
{
    //dtor
}
void RespuestaDelRegistro::setRespuestaUsuarioExistente(){
    this->respuesta.setCodigo(400);
    this->respuesta.setMensajeDeEstado("Usuario existente");
}

void RespuestaDelRegistro::setRespuestaErrorDelSharedServer(){
    this->respuesta.setCodigo(503);
    this->respuesta.setMensajeDeEstado("Error del server");
}

void RespuestaDelRegistro::setRespuestaRegistroCorrecto(){
    this->respuesta.setCodigo(201);
    this->respuesta.setMensajeDeEstado("Se pudo registrar el usuario");
}
