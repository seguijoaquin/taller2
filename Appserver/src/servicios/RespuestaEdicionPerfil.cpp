#include "RespuestaEdicionPerfil.h"

RespuestaEdicionPerfil::RespuestaEdicionPerfil()
{
    //ctor
}

RespuestaEdicionPerfil::~RespuestaEdicionPerfil()
{
    //dtor
}
void RespuestaEdicionPerfil::setRespuestaEdicioncionCorrecta(){
    this->respuesta.setCodigo(200);
    this->respuesta.setMensajeDeEstado("Edicion correcta");
}

void RespuestaEdicionPerfil::setRespuestaEdicionEnServerIncorrecta(){
    this->respuesta.setCodigo(500);
    this->respuesta.setMensajeDeEstado("No se pudo modificar en el servidor");
}

void RespuestaEdicionPerfil::setRespuestaNoTienePermisoDeEdicion(){
    this->respuesta.setCodigo(400);
    this->respuesta.setMensajeDeEstado("Permiso denegado");
}
