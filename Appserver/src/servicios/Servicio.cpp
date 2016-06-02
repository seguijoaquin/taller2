#include "Servicio.h"

Servicio::Servicio()
{
    //ctor
}

Servicio::~Servicio()
{
    //dtor
}

RespuestaDelServicio* Servicio::getRespuesta(){
    return this->respuesta;
}
