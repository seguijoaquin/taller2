#include "servicioLogin.h"

servicioLogin::servicioLogin(SesionesDeUsuarios* sesionesDeUsuarios, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales){
    this->mensajeHTTP = mensajeHTTP;
    this->credenciales = credenciales;
    this->sesionesDeUsuarios = sesionesDeUsuarios;
    this->atenderLogin();
}


void servicioLogin::atenderLogin(){
    if (this->validarCredenciales()){
        realizarLogin();
    }
    else{
        //SI ALGUNO DE LOS DOS DATOS ESTA INCORRECTO, SE LE MANDA UN MENSAJE GENERAL DE QUE HAY DATOS INCORRECTOS
        //Refactorizar: respuesta = MENSAJE_DATOS__LOGIN_ERRONEOS;
        RespuestaDelLogin* respuestaLogin = new RespuestaDelLogin();
        respuestaLogin->setRespuestaLoginIncorrecto();
        this->respuesta = respuestaLogin;
        //this->respuesta = "HTTP/1.1 400 No coinciden los datos\r\n\r\n";
    }
}

bool servicioLogin::validarCredenciales(){
    //Tengo que sacar las credenciales
    //Tengo que ver si son correctas
    //Devuelve T o F
    string usuarioIngresado = this->mensajeHTTP.getHeader("Usuario");
    string passwordIngresado = this->mensajeHTTP.getHeader("Password");
    return this->credenciales->validarCredenciales(usuarioIngresado,passwordIngresado);
}



void servicioLogin::realizarLogin(){
    string token;
    token = generarToken();
    string usuarioIngresado = this->mensajeHTTP.getHeader("Usuario");
    this->sesionesDeUsuarios->agregarSesionDe(usuarioIngresado, token);
    RespuestaDelLogin* respuestaLogin = new RespuestaDelLogin();
    respuestaLogin->setRespuestaLoginCorrecto(token);
    this->respuesta = respuestaLogin;
    //this->respuesta = "HTTP/1.1 200 Se logueo correctamente\r\nToken:" + token + "\r\n\r\nbody\0";
}

string servicioLogin::generarToken(){
    //Algo random
    return "123456abcdef";

}



/*string servicioLogin::getRespuesta(){
    return this->respuesta;
}
*/

servicioLogin::~servicioLogin(){
    //dtor
}
