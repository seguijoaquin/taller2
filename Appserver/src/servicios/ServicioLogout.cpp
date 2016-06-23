#include "ServicioLogout.h"

ServicioLogout::ServicioLogout(MensajeHTTPRequest* mensaje, SesionesDeUsuarios* sesiones){
    this->mensaje = mensaje;
    this->sesiones = sesiones;

    this->atenderLogout();
}

ServicioLogout::~ServicioLogout()
{
    //dtor
}


void ServicioLogout::atenderLogout(){
    string usuario = this->mensaje->getHeader("Usuario");


    this->sesiones->terminarSesionDe(usuario);
    RespuestaServicioLogout* rta = new RespuestaServicioLogout();
    rta->setRespuestaLogoutCorrecto();
    this->respuesta = rta;

}
