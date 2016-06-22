#include "Mensajero.h"

Mensajero::Mensajero(ManejadorDeConexiones* conexiones, SesionesDeUsuarios* sesiones){
    this->conexiones = conexiones;
    this->sesiones = sesiones;
    //Las sesiones van a servir para ver el GCM Token
}

Mensajero::~Mensajero()
{
    //dtor
}


bool Mensajero::enviarMensaje(string emisor, string receptor, string mensaje){
    Logger::Instance()->log(INFO, "Se va a enviar un mensaje de "+ emisor + " a " + receptor +":\n" + mensaje);
    MensajeHTTPRequestGCM requestGCM;
    JsonObject dataJson;
    dataJson.agregarClaveValor("Emisor",emisor);
    dataJson.agregarClaveValor("Mensaje",mensaje);


    string tokenGCM = this->sesiones->getTokenGCMDe(receptor);

    this->armarBodyDelMensaje(tokenGCM, requestGCM, dataJson);
    /*JsonObject bodyJson;
    bodyJson.agregarClaveValor("to",tokenGCM);
    bodyJson.agregarClaveValor("data",dataJson);
    requestGCM.setBody( bodyJson.toString() );
    */

    return this->enviarMensaje(requestGCM);
}

bool Mensajero::notificarUsuarioSobreMatchCon(string usuario, string match){
    Logger::Instance()->log(INFO, "Se va a notificar al usuario "+usuario+" sobre su match con "+match);
    MensajeHTTPRequestGCM requestGCM;
    string tokenGCM = this->sesiones->getTokenGCMDe(usuario);
    JsonObject dataJson;
    dataJson.agregarClaveValor("Email", match);
    dataJson.agregarClaveValor("Nombre","NOMBRE HARDCODEADO"+match);

    this->armarBodyDelMensaje(tokenGCM, requestGCM, dataJson);
    return this->enviarMensaje(requestGCM);
}

void Mensajero::armarBodyDelMensaje(string tokenGCM, MensajeHTTPRequestGCM& requestGCM, JsonObject& dataJson){
    JsonObject bodyJson;
    bodyJson.agregarClaveValor("to",tokenGCM);
    bodyJson.agregarClaveValor("data",dataJson);
    requestGCM.setBody( bodyJson.toString() );
}


bool Mensajero::enviarMensaje(MensajeHTTPRequestGCM& requestGCM){
    Logger::Instance()->log(DEBUG, "HTTP Request que se envia a GCM:\n" + requestGCM.toString());
    MensajeHTTPReply GCMreply = this->conexiones->enviarMensajeHTTP(&requestGCM,"80");
    Logger::Instance()->log(DEBUG, "HTTP Reply que viene de GCM:\n" + GCMreply.toString() );

    JsonObject bodyGCM(requestGCM.getBody());

    if (  (GCMreply.getCodigo() != 200)  || (bodyGCM.getInt("failure") == 1)  ){
        Logger::Instance()->log(ERROR, "Error en Google Cloud Messaging" + requestGCM.toString());
        return false;
    }
    else{
        return true;
    }
}
