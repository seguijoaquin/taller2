#include "ServicioActualizarPosicion.h"

ServicioActualizarPosicion::ServicioActualizarPosicion(SharedDataBase* shared, CredencialesDeUsuarios* credenciales, MensajeHTTPRequest* mensaje){
    Logger::Instance()->log(INFO, "Se crea el Servicio Actualizar Posicion");
    this->shared = shared;
    this->credenciales = credenciales;
    this->mensajeHTTP = mensaje;

    this->atenderActualizacionPosicion();
}


ServicioActualizarPosicion::~ServicioActualizarPosicion()
{
    //dtor
}

void ServicioActualizarPosicion::atenderActualizacionPosicion(){
    string usuario = this->mensajeHTTP->getHeader("Usuario");
    int idShared = this->credenciales->getIDSharedDe(usuario);

    Usuario usuarioInicial = this->shared->obtenerPerfilDelUsuario(idShared);

    Localizacion nuevaLocalizacion(this->mensajeHTTP->getBody());
    usuarioInicial.actualizarLocalizacion(nuevaLocalizacion);

    RespuestaActualizarPosicion* respuestaActualizar = new RespuestaActualizarPosicion();
    if (shared->modificarPerfilUsuario(usuarioInicial)){
        respuestaActualizar->setRespuestaActualizacionCorrecta();
    }
    else{
        respuestaActualizar->setRespuestaActualizacionIncorrecta();
    }
    this->respuesta = respuestaActualizar;
}
