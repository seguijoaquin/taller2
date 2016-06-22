#include "ServicioEditarPerfil.h"

ServicioEditarPerfil::ServicioEditarPerfil(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, CredencialesDeUsuarios* credenciales){
    this->shared = shared;
    this->mensajeHTTP = mensajeHTTP;
    this->credenciales = credenciales;

    this->atenderEdicion();
}

ServicioEditarPerfil::~ServicioEditarPerfil()
{
    //dtor
}

void ServicioEditarPerfil::atenderEdicion(){
    //VERIFICAR QUE EL MAIL SEA EL MISMO ANTES
    int idShared = this->credenciales->getIDSharedDe( this->mensajeHTTP->getHeader("Usuario") );
    Usuario usuarioModificado(this->mensajeHTTP->getBody());

    RespuestaEdicionPerfil* respuestaEdicion = new RespuestaEdicionPerfil();
    if (idShared == usuarioModificado.getId()){
        if (this->shared->modificarPerfilUsuario(usuarioModificado)){
            respuestaEdicion->setRespuestaEdicioncionCorrecta();
        }
        else{
            respuestaEdicion->setRespuestaEdicionEnServerIncorrecta();
        }
    }
    else{
        //LOGGUEAR ALGO O ARREGLARLO PONIENDO EL ID CORRECTO
        respuestaEdicion->setRespuestaNoTienePermisoDeEdicion();
    }
    this->respuesta = respuestaEdicion;
}
