#include "CreatorModificarFoto.h"

CreatorModificarFoto::CreatorModificarFoto(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, CredencialesDeUsuarios* credenciales){
    //Puede mandar body vacio, significaria borrar la foto
    if ( this->validarParametrosDeSesion(mensajeHTTP,sesiones)){
        this->servicio = new ServicioModificarFoto(shared, mensajeHTTP, credenciales);
    }
    else{
        this->servicio = new ServicioInexistente();
    }
}

CreatorModificarFoto::~CreatorModificarFoto()
{
    //dtor
}
