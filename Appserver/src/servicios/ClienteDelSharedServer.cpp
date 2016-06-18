#include "ClienteDelSharedServer.h"


ClienteDelSharedServer::ClienteDelSharedServer(){
   // this->recibioRespuesta = false;
    this->conexionActiva = true;
}

ClienteDelSharedServer::~ClienteDelSharedServer()
{
    //dtor
}

void ClienteDelSharedServer::esperarRespuesta(){
    //this->esperandoRespuesta = true;
    //while ( !this->recibioRespuesta){
    while ( this->conexionActiva){
        sleep(1);
    }
}

void ClienteDelSharedServer::setRespuesta(MensajeHTTPReply respuesta){
    this->respuesta = respuesta;
    //this->recibioRespuesta = true;
}

void ClienteDelSharedServer::terminarConexion(){
    this->conexionActiva = false;
}

/*
void ClienteDelSharedServer::dejarDeEsperar(){
    this->esperandoRespuesta = false;
}
*/
MensajeHTTPReply ClienteDelSharedServer::getRespuesta(){
    return this->respuesta;
}

