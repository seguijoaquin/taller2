#include "servicioLogin.h"

/*servicioLogin::servicioLogin(http_message* mensajeHTTP, map<string,string>* listaUsuarios){
    this->mensajeHTTP = mensajeHTTP;
    this->listaUsuarios = listaUsuarios;
    this->atenderLogin();
}
*/

servicioLogin::servicioLogin(http_message* mensajeHTTP, rocksdb::DB* dbUsuarios ){
    this->mensajeHTTP = mensajeHTTP;
    this->dbUsuarios = dbUsuarios;
    this->atenderLogin();
}

void servicioLogin::atenderLogin(){
    //ESTO DEBERIA SER CON rocksDB
    if (usuarioExiste()){
        realizarLogin();
    }
    else{
        //SI ALGUNO DE LOS DOS DATOS ESTA INCORRECTO, SE LE MANDA UN MENSAJE GENERAL DE QUE HAY DATOS INCORRECTOS
        //Refactorizar: respuesta = MENSAJE_DATOS__LOGIN_ERRONEOS;
        this->respuesta = "HTTP/1.1 400 No coinciden los datos\r\n\r\n";
    }
}

bool servicioLogin::usuarioExiste(){
    //Tengo que sacar las credenciales
    //Tengo que ver si son correctas
    //Devuelve T o F
    //metodo getUsuarioYPassword(.....)
    mg_str* headerUsuario = mg_get_http_header(mensajeHTTP, "Usuario");
    mg_str* headerPassword = mg_get_http_header(mensajeHTTP, "Password");

    string usuarioIngresado(headerUsuario->p,headerUsuario->len);
    string passwordIngresado(headerPassword->p,headerPassword->len);

    //Refactorizar: buscarUsuario()
/*
    if (this->listaUsuarios->find(usuarioIngresado) == this->listaUsuarios->end()){
        return false;
    }
    else{
        if(this->listaUsuarios->find(usuarioIngresado)->second == passwordIngresado){
            return true;
        }
    }
*/
    string passwordGuardado;
    rocksdb::Status estado = this->dbUsuarios->Get(rocksdb::ReadOptions(), usuarioIngresado, &passwordGuardado );

    if (estado.IsNotFound()){
        return false;
    }
    else{
        if(passwordGuardado == passwordIngresado){
            return true;
        }
        else{
            return false;
        }
    }
}



void servicioLogin::realizarLogin(){
    string token;
    token = generarToken();
    //Refactorizar: TODO guardar el token en algun lugar token-usuario
    //Tengo que escribir la respuesta HTTP/1.1 200 Se logueo correctamente\r\n\Token:1ddfw4g\r\n\r\n\0
    this->respuesta = "HTTP/1.1 200 Se logueo correctamente\r\nToken:" + token + "\r\n\r\nbody\0";
    //cout<<"Respuesta del login:\n"<<this->respuesta<<"\n";

}

string servicioLogin::generarToken(){
    //Algo random
    return "123456abcdef";

}



string servicioLogin::getRespuesta(){
    return this->respuesta;
}

servicioLogin::~servicioLogin(){
    //dtor
}
