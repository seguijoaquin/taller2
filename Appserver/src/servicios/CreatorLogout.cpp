#include "CreatorLogout.h"

CreatorLogout::CreatorLogout(MensajeHTTPRequest* mensaje, SesionesDeUsuarios* sesiones){

    if (this->validarParametrosDeSesion(mensaje,sesiones)){
        this->servicio = new ServicioLogout(mensaje,sesiones);
    }
    else{
        this->servicio = new ServicioInexistente();
    }

}

CreatorLogout::~CreatorLogout()
{
    //dtor
}
