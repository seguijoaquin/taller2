#include "RespuestaServicioInexistente.h"

RespuestaServicioInexistente::RespuestaServicioInexistente(){
    this->respuesta.setCodigo(404);
    this->respuesta.setMensajeDeEstado("Bad Request");
}

RespuestaServicioInexistente::~RespuestaServicioInexistente(){
    //dtor
}

void RespuestaServicioInexistente::setRespuestaTokenInvalido(){
    this->respuesta.setCodigo(401);
    this->respuesta.setMensajeDeEstado("Token no coincide con usuario");
}
