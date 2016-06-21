#include "RespuestaActualizarPosicion.h"

RespuestaActualizarPosicion::RespuestaActualizarPosicion()
{
    //ctor
}

RespuestaActualizarPosicion::~RespuestaActualizarPosicion()
{
    //dtor
}

void RespuestaActualizarPosicion::setRespuestaActualizacionCorrecta(){
    this->respuesta.setCodigo(200);
    this->respuesta.setMensajeDeEstado("Actualizacion correcta");
}

void RespuestaActualizarPosicion::setRespuestaActualizacionIncorrecta(){
    this->respuesta.setCodigo(500);
    this->respuesta.setMensajeDeEstado("Actualizacion incorrecta");
}
