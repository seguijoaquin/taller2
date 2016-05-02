#include "MensajeHTTPRequest.h"
using namespace std;

//SOLO PARA PROBAR ALGO
MensajeHTTPRequest::MensajeHTTPRequest(){

}


MensajeHTTPRequest::MensajeHTTPRequest(http_message* mensajeMG, int dummy){
    this->metodo = this->mg_strToString(mensajeMG->method);
    this->uri = this->mg_strToString(mensajeMG->uri);
    this->cargarHeaders(mensajeMG);
}


string MensajeHTTPRequest::mg_strToString(mg_str& mgStr){
    return string(mgStr.p,mgStr.len);
}


void MensajeHTTPRequest::cargarHeaders(http_message* mensajeMG){

    //Si por ejemplo hay 2 headers, los header_names[2].len, header_names[3].len, etc van a ser = 0
    for (int i = 0; mensajeMG->header_names[i].len > 0; i++) {
        this->headers[this->mg_strToString(mensajeMG->header_names[i])] = this->mg_strToString(mensajeMG->header_values[i]);
    }
}



string MensajeHTTPRequest::getMetodo(){
    return this->metodo;
}

string MensajeHTTPRequest::getURI(){
    return this->uri;
}

bool MensajeHTTPRequest::tieneHeader(string header){
    if (this->headers.find(header) == this->headers.end()){
        //Si es == al end() es porque NO lo encontro, entonces NO tiene el header pasado
        return false;
    }
    else{
        //Si es != al end() es porque SI lo encontro, entonces SI tiene el header pasado
        return true;
    }
}

string MensajeHTTPRequest::getHeader(string header){
    if (this->tieneHeader(header)){
        return this->headers[header];
    }
    else{
        return "";
    }
}



MensajeHTTPRequest::~MensajeHTTPRequest()
{
    //dtor
}
