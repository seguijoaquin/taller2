#include "ServicioModificarFoto.h"

ServicioModificarFoto::ServicioModificarFoto(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, CredencialesDeUsuarios* credenciales){
    this->shared = shared;
    this->mensajeHTTP = mensajeHTTP;
    this->credenciales = credenciales;

    this->atenderModificacionFoto();
}

ServicioModificarFoto::~ServicioModificarFoto()
{
    //dtor
}

void ServicioModificarFoto::atenderModificacionFoto(){
    string usuario = this->mensajeHTTP->getHeader("Usuario");
    RespuestaModificarFoto* respuestaModificacion = new RespuestaModificarFoto();
    if (this->shared->modificarFotoPerfil(this->credenciales->getIDSharedDe(usuario), this->mensajeHTTP->getBody())){
        respuestaModificacion->setRespuestaModificacionCorrecta();
    }
    else{
        respuestaModificacion->setRespuestaModificacionIncorrecta();
    }
    this->respuesta = respuestaModificacion;
}
