#include "RespuestaServicioInexistente.h"

RespuestaServicioInexistente::RespuestaServicioInexistente(){
    this->respuesta.setCodigo(404);
    this->respuesta.setMensajeDeEstado("Bad Request");
}

RespuestaServicioInexistente::~RespuestaServicioInexistente()
{
    //dtor
}
