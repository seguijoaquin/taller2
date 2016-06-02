#include "CreatorLogin.h"

CreatorLogin::CreatorLogin(SesionesDeUsuarios* sesionesDeUsuarios, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales){

    if (mensajeHTTP.tieneHeader("Usuario") && mensajeHTTP.tieneHeader("Password")){
        this->servicio = new servicioLogin(sesionesDeUsuarios, mensajeHTTP, credenciales);
    }
    else{
        this->servicio = new ServicioInexistente();
    }

}

CreatorLogin::~CreatorLogin()
{
    //dtor
}
