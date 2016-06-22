#include "CreatorEditarPerfil.h"

CreatorEditarPerfil::CreatorEditarPerfil(SharedDataBase* shared, MensajeHTTPRequest* mensaje, SesionesDeUsuarios* sesiones, CredencialesDeUsuarios* credenciales){

    if (true /*VERIFICAR TOKEN Y HEADERS*/){
        this->servicio = new ServicioEditarPerfil(shared,mensaje,credenciales);
    }
    else{
        this->servicio = new ServicioInexistente();
    }


}

CreatorEditarPerfil::~CreatorEditarPerfil()
{
    //dtor
}