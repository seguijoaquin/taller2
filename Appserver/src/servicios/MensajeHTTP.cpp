#include "MensajeHTTP.h"


MensajeHTTP::MensajeHTTP(){

}

MensajeHTTP::MensajeHTTP(http_message* mensajeMG){
    this->cargarHeaders(mensajeMG);
    this->body = mg_strToString(mensajeMG->body);
}




string MensajeHTTP::mg_strToString(mg_str& mgStr){
    return string(mgStr.p,mgStr.len);
}


void MensajeHTTP::cargarHeaders(http_message* mensajeMG){

    //Si por ejemplo hay 2 headers, los header_names[2].len, header_names[3].len, etc van a ser = 0
    for (int i = 0; mensajeMG->header_names[i].len > 0; i++) {
        //this->headers[this->mg_strToString(mensajeMG->header_names[i])] = this->mg_strToString(mensajeMG->header_values[i]);
        this->agregarHeader(this->mg_strToString(mensajeMG->header_names[i]), this->mg_strToString(mensajeMG->header_values[i]));
    }
}

void MensajeHTTP::agregarHeader(string header, string valor){
    this->headers[header] = valor;
}



bool MensajeHTTP::tieneHeader(string header){
    return (this->headers.find(header) != this->headers.end());
}

string MensajeHTTP::getHeader(string header){
    if (this->tieneHeader(header)){
        return this->headers[header];
    }
    else{
        return "";
    }
}


string MensajeHTTP::headersToString(){
    string resultado = "";
	for( map<string,string>::iterator it = this->headers.begin() ; it != this->headers.end(); ++it){
	    string nombre = (*it).first;
        string contenido = (*it).second;
        resultado = resultado + nombre + ": " + contenido + "\r\n";
	}
	return resultado;
}



void MensajeHTTP::setBody(string body){
    this->agregarHeader("Content-Length", StringUtil::int2string(body.length()));
    this->body = body;
}

string MensajeHTTP::getBody(){
    return this->body;
}






MensajeHTTP::~MensajeHTTP()
{
    //dtor
}
