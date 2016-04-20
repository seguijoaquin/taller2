#include "AtendedorHTTP.h"

AtendedorHTTP::AtendedorHTTP(http_message* mensajeHTTP, rocksdb::DB* credencialesUsuarios, mg_mgr* manager){
    this->mensajeHTTP = mensajeHTTP;
    this->credencialesUsuarios = credencialesUsuarios;
    this->manager = manager;
    this->atenderMesajeHTTP();
}


string AtendedorHTTP::getRespuesta(){
    return this->respuesta;
}


void AtendedorHTTP::atenderMesajeHTTP(){
    if (compararMetodoHTTP(mensajeHTTP,"POST")){
        //respuesta = atenderPOST(mensajeHTTP);
    }
    else if (compararMetodoHTTP(mensajeHTTP,"GET")){
        if (compararUriHTTP(mensajeHTTP, "/login")){
            //servicioLogin logginer(mensajeHTTP, &listaUsuarios);
            servicioLogin logginer(mensajeHTTP, this->credencialesUsuarios);
            this->respuesta = logginer.getRespuesta();
            cout<<"RESPUESTA DEL SERVICIO LOGIN:\n"<<this->respuesta<<"\n";
        }
    }
    else if (compararMetodoHTTP(mensajeHTTP, "PUT")){
        if (compararUriHTTP(mensajeHTTP, "/registro")){
            //servicioRegistro registrador(&manager, mensajeHTTP, &listaUsuarios);
            servicioRegistro registrador(this->manager, mensajeHTTP, this->credencialesUsuarios);
            this->respuesta = registrador.getRespuesta();
            cout<<"RESPUESTA DEL SERVICIO REGISTRO:\n"<<this->respuesta<<"\n";
        }
    }
}



bool AtendedorHTTP::compararMetodoHTTP(http_message* mensajeHTTP, char* metodo){
    if (mg_vcmp(&(mensajeHTTP->method), metodo) == 0){
        return true;
    }
    else{
        return false;
    }
}

bool AtendedorHTTP::compararUriHTTP(http_message* mensajeHTTP, char* uri){
    if (mg_vcmp(&(mensajeHTTP->uri), uri) == 0){
        return true;
    }
    else{
        return false;
    }
}













AtendedorHTTP::~AtendedorHTTP()
{
    //dtor
}
