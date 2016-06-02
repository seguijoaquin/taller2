#include "RespuestaDelChat.h"

RespuestaDelChat::RespuestaDelChat()
{
    //ctor
}

RespuestaDelChat::~RespuestaDelChat()
{
    //dtor
}


void RespuestaDelChat::setRespuestaGCM(){
    //this->respuesta = GCMreply;
    this->respuesta.setCodigo(200);
    this->respuesta.setMensajeDeEstado("OK");
}
