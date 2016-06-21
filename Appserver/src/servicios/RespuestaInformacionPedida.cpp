#include "RespuestaInformacionPedida.h"

RespuestaInformacionPedida::RespuestaInformacionPedida()
{
    //ctor
}

RespuestaInformacionPedida::~RespuestaInformacionPedida()
{
    //dtor
}

void RespuestaInformacionPedida::setRespuestaInformacionPedida(Usuario& usuario){
    this->respuesta.setCodigo(200);
    this->respuesta.setMensajeDeEstado("Informacion del usuario pedido");
    this->respuesta.setBody(usuario.toString());
}
