#include "CreatorLogin.h"

CreatorLogin::CreatorLogin(SesionesDeUsuarios* sesionesDeUsuarios, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales, SharedDataBase* shared){

    if ( (this->validarUsuarioYPassword(&mensajeHTTP))  && ( mensajeHTTP.tieneHeader("TokenGCM") )){
        this->servicio = new servicioLogin(sesionesDeUsuarios, mensajeHTTP, credenciales, shared);
    }
    else{
        this->servicio = new ServicioInexistente();
    }

}

CreatorLogin::~CreatorLogin()
{
    //dtor
}
