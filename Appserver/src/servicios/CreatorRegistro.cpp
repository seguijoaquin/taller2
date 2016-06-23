#include "CreatorRegistro.h"

CreatorRegistro::CreatorRegistro(SharedDataBase* shared, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales, AdministradorCandidatos* administradorCandidatos ){

    if (  (this->verificarJsonUsuario(mensajeHTTP)) && (mensajeHTTP.tieneHeader("Password") )) {
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


bool CreatorRegistro::verificarJsonUsuario(MensajeHTTPRequest& mensajeHTTP){
    Usuario usuarioIngresado(mensajeHTTP.getBody());

    return (usuarioIngresado.getEmail() != "");
}
