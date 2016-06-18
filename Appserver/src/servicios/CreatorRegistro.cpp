#include "CreatorRegistro.h"

CreatorRegistro::CreatorRegistro(SharedDataBase* shared, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales, AdministradorCandidatos* administradorCandidatos ){

    if (mensajeHTTP.tieneHeader("Usuario") &&  mensajeHTTP.tieneHeader("Password") ){
        this->servicio = new servicioRegistro(shared, mensajeHTTP, credenciales, administradorCandidatos);
    }
    else{
        this->servicio = new ServicioInexistente();
    }
}

CreatorRegistro::~CreatorRegistro()
{
    //dtor
}
