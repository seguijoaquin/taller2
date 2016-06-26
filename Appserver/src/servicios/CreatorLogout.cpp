#include "CreatorLogout.h"

CreatorLogout::CreatorLogout(MensajeHTTPRequest* mensaje, SesionesDeUsuarios* sesiones){

    if (this->validarParametrosDeSesion(mensaje,sesiones)){
        this->servicio = new ServicioLogout(mensaje,sesiones);
    }
    else{
        //Queda medio mal asi pero es una solucion rapida...
        if (this->servicio == nullptr){
            this->servicio = new ServicioInexistente();
        }
    }

}

CreatorLogout::~CreatorLogout()
{
    //dtor
}
