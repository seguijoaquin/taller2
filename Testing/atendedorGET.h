#ifndef ATENDEDORGET_INCLUDED.h
#define ATENDEDORGET_INCLUDED.h

#include <iostream>
#include "mongoose.h"
using namespace std;


const char* PATHLOGIN = "/login";
extern map<string,string> listaUsuarios;

string generarToken(){
    //Algo random
    return "123456abcdef";
}

char* realizarLogin(){

    const char* respuestaParcial;
    char* respuesta;
    string token;
    string respuestaCompleta;

    token = generarToken();


    //Tengo que escribir la respuesta HTTP/1.1 200 Se logueo correctamente\r\n\Token:1ddfw4g\r\n\r\n\0
    respuestaCompleta = "HTTP/1.1 200 Se logueo correctamente\r\n\Token:" + token + "\r\n\r\nbody\0";
    respuestaParcial = respuestaCompleta.c_str();

    respuestaCompleta.copy(respuesta,respuestaCompleta.size(), 0);

    cout<<"Respuesta del login:\n"<<respuesta<<"\n";

    return respuesta;
}

bool usuarioExiste(struct http_message* mensajeHTTP){
    //Ahora se estan mandando com headers, habria que pasarlo por el body, y refactorzar estas funciones
    //Tengo que sacar las credenciales
    //Tengo que ver si son correctas
    //Devuelve T o F
    //metodo getUsuarioYPassword(.....)
    mg_str* headerUsuario = mg_get_http_header(mensajeHTTP, "Usuario");
    mg_str* headerPassword = mg_get_http_header(mensajeHTTP, "Password");

    printf("Usuario:%.*s\n", headerUsuario->len,headerUsuario->p);
    printf("Password:%.*s\n", headerPassword->len,headerPassword->p);

    string usuarioIngresado(headerUsuario->p,headerUsuario->len);
    string passwordIngresado(headerPassword->p,headerPassword->len);

    //Refactorizar: buscarUsuario()
    if (listaUsuarios.find(usuarioIngresado) == listaUsuarios.end()){
        return false;
    }
    else{
        if(listaUsuarios.find(usuarioIngresado)->second == passwordIngresado){
            return true;
        }
    }
}

char* atenderLogin(struct http_message* mensajeHTTP){
    char* respuesta;
    //ESTO DEBERIA SER CON rocksDB
    //Refactorizar: metodo getUsuarioYPassword(.....)
    /*
        if(usuarioSeLogueaCorrectamente(...){ //ESTO SERIA QUE EL USUARIO Y CONTRASENIA SON CORRECTAS Y EVITO TENER ESOS DOS NIVELES QUE ESTAN AHORA
            respuesta = realizarLogin() /
        }
        else{
            respuesta = "HTTP/1.1 400 No coinciden los datos";
        }
    */
    if (usuarioExiste(mensajeHTTP)){
        respuesta = realizarLogin();
    }
    else{
        //SI ALGUNO DE LOS DOS DATOS ESTA INCORRECTO, SE LE MANDA UN MENSAJE GENERAL DE QUE HAY DATOS INCORRECTOS
        //Refactorizar: respuesta = MENSAJE_DATOS__LOGIN_ERRONEOS;
        respuesta = "HTTP/1.1 400 No coinciden los datos";
    }
    return respuesta;
}


char* atenderGET(struct http_message* mensajeHTTP){
    char* respuesta;
    //Podria hacer una funcion "compararURI(mensajeHttP,PATHLOGIN)"
    if (mg_vcmp(&(mensajeHTTP->uri), PATHLOGIN) == 0){
        respuesta = atenderLogin(mensajeHTTP);
    }

    return respuesta;
}

#endif // ATENDEDORGET_INCLUDED.h
