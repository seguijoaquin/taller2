#include "RespuestaModificarFoto.h"

RespuestaModificarFoto::RespuestaModificarFoto()
{
    //ctor
}

RespuestaModificarFoto::~RespuestaModificarFoto()
{
    //dtor
}

void RespuestaModificarFoto::setRespuestaModificacionCorrecta(){
    this->respuesta.setCodigo(200);
    this->respuesta.setMensajeDeEstado("Se pudo modificar la foto");
}

void RespuestaModificarFoto::setRespuestaModificacionIncorrecta(){
    this->respuesta.setCodigo(500);
    this->respuesta.setMensajeDeEstado("No se pudo modificar la foto");
}
