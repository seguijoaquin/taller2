#include "ServicioInexistente.h"

ServicioInexistente::ServicioInexistente(){
    Logger::Instance()->log(WARNING, "Se crea el Servicio Inexstente");
    this->respuesta = new RespuestaServicioInexistente();
}

ServicioInexistente::~ServicioInexistente()
{
    //dtor
}


void ServicioInexistente::setRespuestaTokenInvalido(){
    ((RespuestaServicioInexistente*) this->respuesta)->setRespuestaTokenInvalido();
}
