#include "servicioLogin.h"

servicioLogin::servicioLogin(http_message* mensajeHTTP, rocksdb::DB* dbUsuarios,  map<string,string>* tokensDeUsuarios ){
    this->mensajeHTTP = mensajeHTTP;
    this->dbUsuarios = dbUsuarios;
    this->tokensDeUsuarios = tokensDeUsuarios;
    this->atenderLogin();
}

void servicioLogin::atenderLogin(){
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
    //Refactorizar: esto esta copiado de arriba, ¿archivo Utilities"?

    mg_str* headerUsuario = mg_get_http_header(mensajeHTTP, "Usuario");
    string usuarioIngresado(headerUsuario->p,headerUsuario->len);

    (*(this->tokensDeUsuarios))[usuarioIngresado] = token;

    this->respuesta = "HTTP/1.1 200 Se logueo correctamente\r\nToken:" + token + "\r\n\r\nbody\0";
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
