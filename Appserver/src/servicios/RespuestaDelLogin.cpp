#include "RespuestaDelLogin.h"

RespuestaDelLogin::RespuestaDelLogin(){
    //ctor
}

RespuestaDelLogin::~RespuestaDelLogin(){
    //dtor
}


void RespuestaDelLogin::setRespuestaLoginCorrecto(string token){
    this->respuesta.setCodigo(200);
    this->respuesta.setMensajeDeEstado("Se logueo correctamente");
    this->respuesta.agregarHeader("Token", token);
}

void RespuestaDelLogin::setRespuestaLoginIncorrecto(){
    this->respuesta.setCodigo(400);
    this->respuesta.setMensajeDeEstado("No coinciden los datos");
}

