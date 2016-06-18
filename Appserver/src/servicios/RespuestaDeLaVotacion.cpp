#include "RespuestaDeLaVotacion.h"

RespuestaDeLaVotacion::RespuestaDeLaVotacion()
{
    //ctor
}

RespuestaDeLaVotacion::~RespuestaDeLaVotacion()
{
    //dtor
}

void RespuestaDeLaVotacion::setRespuestaSeRegistroVoto(){
    this->respuesta.setCodigo(200);
    this->respuesta.setMensajeDeEstado("El voto se registro correctamente");
}
