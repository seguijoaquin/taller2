#include "MensajeHTTPReply.h"

MensajeHTTPReply::MensajeHTTPReply(http_message* mensajeMG):MensajeHTTP(mensajeMG){
    this->codigo = mensajeMG->resp_code;
    this->mensajeDeEstado = this->mg_strToString(mensajeMG->resp_status_msg);
}


int MensajeHTTPReply::getCodigo(){
    return this->codigo;
}

string MensajeHTTPReply::getMensajeDeEstado(){
    return this->mensajeDeEstado;
}

string MensajeHTTPReply::toString(){
    return ("HTTP/1.1 " + StringUtil::int2string(this->getCodigo()) + " " + this->getMensajeDeEstado() + "\r\n" + this->headersToString() + "\r\n"); // + this->getBody()
}















MensajeHTTPReply::~MensajeHTTPReply()
{
    //dtor
}
