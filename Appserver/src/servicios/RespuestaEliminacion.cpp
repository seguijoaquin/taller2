#include "RespuestaEliminacion.h"

RespuestaEliminacion::RespuestaEliminacion()
{
    //ctor
}

RespuestaEliminacion::~RespuestaEliminacion()
{
    //dtor
}

void RespuestaEliminacion::setRespuestaEliminacionCorrecta(){
    this->respuesta.setCodigo(200);
    this->respuesta.setMensajeDeEstado("Usuario eliminado correctamente");
}



void RespuestaEliminacion::setRespuestaEliminacionIncorrecta(){
    this->respuesta.setCodigo(400);
    this->respuesta.setMensajeDeEstado("No se pudo eliminar usuario");
}
