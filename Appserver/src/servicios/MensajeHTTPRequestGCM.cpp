#include "MensajeHTTPRequestGCM.h"

MensajeHTTPRequestGCM::MensajeHTTPRequestGCM(){
    this->setMetodo("POST");
    this->setURI("/gcm/send");
    this->agregarHeader("Host", "gcm-http.googleapis.com");
    this->agregarHeader("Content-Type", "application/json");
    this->agregarHeader("Authorization", "key=AIzaSyBvSrS9WC9sJDz6ByDPr_bXTf-Y51ZEKa0");
}

MensajeHTTPRequestGCM::~MensajeHTTPRequestGCM()
{
    //dtor
}
