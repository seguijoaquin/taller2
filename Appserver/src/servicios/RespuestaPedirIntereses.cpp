#include "RespuestaPedirIntereses.h"

RespuestaPedirIntereses::RespuestaPedirIntereses()
{
    //ctor
}

RespuestaPedirIntereses::~RespuestaPedirIntereses()
{
    //dtor
}

void RespuestaPedirIntereses::setRespuestaInteresesPedidos(ListadoDeIntereses& iteresesPedidos){
    this->respuesta.setCodigo(200);
    this->respuesta.setMensajeDeEstado("OK");
    this->respuesta.setBody(iteresesPedidos.toString());
}
