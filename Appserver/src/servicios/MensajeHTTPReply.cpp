#include "MensajeHTTPReply.h"

MensajeHTTPReply::MensajeHTTPReply(){
    //Por ahora lo necesito
}

MensajeHTTPReply::MensajeHTTPReply(http_message* mensajeMG):MensajeHTTP(mensajeMG){
    this->codigo = mensajeMG->resp_code;
    this->mensajeDeEstado = this->mg_strToString(mensajeMG->resp_status_msg);
}

void MensajeHTTPReply::setCodigo(int codigo){
    this->codigo = codigo;
}

int MensajeHTTPReply::getCodigo(){
    return this->codigo;
}

string MensajeHTTPReply::getMensajeDeEstado(){
    return this->mensajeDeEstado;
}

void MensajeHTTPReply::setMensajeDeEstado(string mensaje){
    this->mensajeDeEstado = mensaje;
}


string MensajeHTTPReply::toString(){
    return ("HTTP/1.1 " + StringUtil::int2string(this->getCodigo()) + " " + this->getMensajeDeEstado() + "\r\n" + this->headersToString() + "\r\n" + this->getBody() );
}















MensajeHTTPReply::~MensajeHTTPReply()
{
    //dtor
}
