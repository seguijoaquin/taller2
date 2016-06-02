#include "CreatorRegistro.h"

CreatorRegistro::CreatorRegistro(SharedDataBase* shared, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales ){

    if (mensajeHTTP.tieneHeader("Usuario") &&  mensajeHTTP.tieneHeader("Password") ){
        this->servicio = new servicioRegistro(shared, mensajeHTTP, credenciales);
    }
    else{
        this->servicio = new ServicioInexistente();
    }
}

CreatorRegistro::~CreatorRegistro()
{
    //dtor
}
