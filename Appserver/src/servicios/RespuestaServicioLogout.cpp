#include "RespuestaServicioLogout.h"

RespuestaServicioLogout::RespuestaServicioLogout()
{
    //ctor
}

RespuestaServicioLogout::~RespuestaServicioLogout()
{
    //dtor
}

void RespuestaServicioLogout::setRespuestaLogoutCorrecto(){
    this->respuesta.setCodigo(200);
    this->respuesta.setMensajeDeEstado("Logout correcto");
}
