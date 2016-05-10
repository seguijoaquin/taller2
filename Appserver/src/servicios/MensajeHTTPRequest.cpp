#include "MensajeHTTPRequest.h"
using namespace std;

//SOLO PARA PROBAR ALGO
MensajeHTTPRequest::MensajeHTTPRequest(){

}


MensajeHTTPRequest::MensajeHTTPRequest(http_message* mensajeMG):MensajeHTTP(mensajeMG){
    this->metodo = this->mg_strToString(mensajeMG->method);
    this->uri = this->mg_strToString(mensajeMG->uri);
}



string MensajeHTTPRequest::getMetodo(){
    return this->metodo;
}

string MensajeHTTPRequest::getURI(){
    return this->uri;
}


void MensajeHTTPRequest::setMetodo(string metodo){
    this->metodo = metodo;
}

void MensajeHTTPRequest::setURI(string uri){
    this->uri = uri;
}





string MensajeHTTPRequest::toString(){
    return (this->getMetodo() + " " + this->getURI() + " HTTP/1.1\r\n" + this->headersToString() + "\r\n" + this->getBody());
}




MensajeHTTPRequest::~MensajeHTTPRequest()
{
    //dtor
}
