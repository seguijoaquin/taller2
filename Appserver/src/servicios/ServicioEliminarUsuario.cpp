#include "ServicioEliminarUsuario.h"

ServicioEliminarUsuario::ServicioEliminarUsuario(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, CredencialesDeUsuarios* credenciales, SesionesDeUsuarios* sesiones){
    this->shared = shared;
    this->mensajeHTTP = mensajeHTTP;
    this->credenciales = credenciales;
    this->sesiones = sesiones;

    this->atenderEliminacion();
}

ServicioEliminarUsuario::~ServicioEliminarUsuario(){
    //dtor
}

void ServicioEliminarUsuario::atenderEliminacion(){

    string usuario = this->mensajeHTTP->getHeader("Usuario");
    string password = this->mensajeHTTP->getHeader("Password");

    RespuestaEliminacion* respuestaEliminacion = new RespuestaEliminacion();
    if (this->credenciales->validarCredenciales(usuario,password) ){
        int idShared = this->credenciales->getIDSharedDe(usuario);
        this->shared->eliminarUsuario(idShared);

        this->credenciales->eliminiarUsuario(usuario);
        this->sesiones->eliminarUsuario(usuario);


        respuestaEliminacion->setRespuestaEliminacionCorrecta();
    }
    else{
        respuestaEliminacion->setRespuestaEliminacionIncorrecta();
    }
    this->respuesta = respuestaEliminacion;
}
