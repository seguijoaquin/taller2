#include "CreatorEliminacion.h"

CreatorEliminacion::CreatorEliminacion(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, CredencialesDeUsuarios* credenciales, SesionesDeUsuarios* sesiones){
    //Usuario existe
    //Password existe
    if ( (true /*sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado)*/ ) && (true/*chequear match*/ ) ){
        this->servicio = new ServicioEliminarUsuario(shared,mensajeHTTP,credenciales, sesiones);
    }
    else{
        this->servicio = new ServicioInexistente();
    }
}

CreatorEliminacion::~CreatorEliminacion()
{
    //dtor
}
