#include "CreatorEditarPerfil.h"

CreatorEditarPerfil::CreatorEditarPerfil(SharedDataBase* shared, MensajeHTTPRequest* mensaje, SesionesDeUsuarios* sesiones, CredencialesDeUsuarios* credenciales){

    if (this->validarParametrosDeSesion(mensaje,sesiones) ){
        this->servicio = new ServicioEditarPerfil(shared,mensaje,credenciales);
    }
    else{
        //Queda medio mal asi pero es una solucion rapida...
        if (this->servicio == nullptr){
            this->servicio = new ServicioInexistente();
        }
    }


}

CreatorEditarPerfil::~CreatorEditarPerfil()
{
    //dtor
}
