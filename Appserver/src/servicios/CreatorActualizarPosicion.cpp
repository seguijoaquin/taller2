#include "CreatorActualizarPosicion.h"

CreatorActualizarPosicion::CreatorActualizarPosicion(SharedDataBase* shared, MensajeHTTPRequest* mensaje, SesionesDeUsuarios* sesiones, CredencialesDeUsuarios* credenciales){


    if (this->validarParametrosDeSesion(mensaje, sesiones)){
        this->servicio = new ServicioActualizarPosicion(shared,credenciales,mensaje);
    }
    else{
        this->servicio = new ServicioInexistente();
    }
}

CreatorActualizarPosicion::~CreatorActualizarPosicion()
{
    //dtor
}
