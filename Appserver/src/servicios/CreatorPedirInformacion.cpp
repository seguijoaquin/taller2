#include "CreatorPedirInformacion.h"

CreatorPedirInformacion::CreatorPedirInformacion(SharedDataBase* shared, MensajeHTTPRequest* mensaje, CredencialesDeUsuarios* credenciales, SesionesDeUsuarios* sesiones, AdministradorCandidatos* administrador){
    string headerUsuario = "Usuario";
    string headerUsuarioPedido = "UsuarioPedido";

    if ( (this->validarParametrosDeSesion(mensaje,sesiones))   &&
         (  (mensaje->getHeader(headerUsuario)  ==  mensaje->getHeader(headerUsuarioPedido))  || (this->validarMatch(mensaje,administrador,headerUsuario, headerUsuarioPedido)))){
        this->servicio = new ServicioPedirInformacion(shared, mensaje, credenciales);
    }
    else{
        this->servicio = new ServicioInexistente();
    }
}

CreatorPedirInformacion::~CreatorPedirInformacion()
{
    //dtor
}
