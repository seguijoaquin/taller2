#include "Mensajes.h"

using namespace std;

Mensajes::Mensajes(){
    /*
    [
        {
            "emisor" : "usuarioY"
            "mensaje": "la puerca esta en la posilga"
        },
        {
            "emisor" : "usuarioX"
            "mensaje": "sabes, no me agrada ese nombre clave"
        }
    ]
    */
}

Mensajes::Mensajes(string jsonTexto){
    this->jArray = JsonArray(jsonTexto);
}

Mensajes::~Mensajes(){
//    delete this->jArray;
}


bool Mensajes::indiceValido(int indice){
    return ( (indice >= 0) && (indice< this->jArray.size()) );
}

string Mensajes::getEmisor(int nroMensaje){
    int indice = nroMensaje - 1;
    if (this->indiceValido(indice)){
        JsonValor aux = (this->jArray)[indice];
        JsonObject* mensaje = (JsonObject*) &aux;
        string emisor = mensaje->getString("emisor");
        return emisor;

    }
    else{
        return "";
    }
}

string Mensajes::getMensaje(int nroMensaje){
    int indice = nroMensaje - 1;
    if (this->indiceValido(indice)){
        JsonValor aux = (this->jArray)[indice];
        JsonObject* mensajeJson = (JsonObject*) &aux;
        string mensaje = mensajeJson->getString("mensaje");
        return mensaje;



    }
    else{
        return "";
    }

}

string Mensajes::toString(){
    Logger::Instance()->log(DEBUG, "Mensaje toString()");
    return this->jArray.toString();
}

int Mensajes::getTamanio(){
    return this->jArray.size();
}

void Mensajes::agregarMensaje(string emisor, string mensaje){
    JsonObject objetoMensaje;
    objetoMensaje.agregarClaveValor("emisor",emisor);
    objetoMensaje.agregarClaveValor("mensaje",mensaje);
    this->jArray.agregar(objetoMensaje);
}
