#include "CreatorActualizarPosicion.h"

CreatorActualizarPosicion::CreatorActualizarPosicion(SharedDataBase* shared, MensajeHTTPRequest* mensaje, SesionesDeUsuarios* sesiones, CredencialesDeUsuarios* credenciales){

    if ( (true /*sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado)*/ ) ){
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
