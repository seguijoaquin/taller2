#include "CreatorVotacion.h"

CreatorVotacion::CreatorVotacion(SharedDataBase* shared, Mensajero* mensajero, MensajeHTTPRequest* mensajeHTTP,SesionesDeUsuarios* sesiones,AdministradorCandidatos* administradorCandidatos){
    string usuario1 = mensajeHTTP->getHeader("Usuario");
    string candidato = mensajeHTTP->getHeader("Candidato");
    string tokenIngresado = mensajeHTTP->getHeader("Token");
    string cantidad = mensajeHTTP->getHeader("Resultado");

    //IMPORTANTE VERIFICAR QUE LE HAYA NOTIFICADO EL CANDIDATO AL USUARIO
    if ( (true /*sesiones->validarTokenConUsuario(usuarioEmisor,tokenIngresado)*/ ) && (true/*chequear match*/ ) ){
        this->servicio = new ServicioVotacion(shared,mensajeHTTP,administradorCandidatos, mensajero);
    }
    else{
        this->servicio = new ServicioInexistente();
    }
}

CreatorVotacion::~CreatorVotacion()
{
    //dtor
}
