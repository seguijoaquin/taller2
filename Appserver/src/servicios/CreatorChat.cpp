#include "CreatorChat.h"

CreatorChat::CreatorChat(Mensajero* mensajero, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones, AdministradorCandidatos* administrador){

    if ( (this->validarParametrosDeSesion(mensajeHTTP,sesiones)) && (this->validarMatch(mensajeHTTP,administrador, "Usuario", "Receptor")) ){
        this->servicio = new ServicioChat(mensajero,mensajeHTTP,sesiones, conversaciones);
    }
    else{
        this->servicio = new ServicioInexistente();
    }
}

CreatorChat::~CreatorChat()
{
    //dtor
}



