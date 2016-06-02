#include "RespuestaMensajes.h"

RespuestaMensajes::RespuestaMensajes()
{
    //ctor
}

RespuestaMensajes::~RespuestaMensajes()
{
    //dtor
}

void RespuestaMensajes::setMensajesComoRespuesta(Mensajes& mensajes){
    this->respuesta.setCodigo(201);
    this->respuesta.setMensajeDeEstado("OK");
    this->respuesta.setBody(mensajes.toString());
}
