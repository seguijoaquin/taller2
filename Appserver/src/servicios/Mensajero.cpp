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

    MensajeHTTPRequestGCM requestGCM;
    ////////////////////////////////REFACTORIZAR//////////////////////////////////////
    //Json::Value bodyJson = Json::objectValue;
    //Json::Value dataJson = Json::objectValue;
    JsonObject dataJson;
    //dataJson["Emisor"] = emisor;
    //dataJson["Mensaje"] = mensaje;
    dataJson.agregarClaveValor("Emisor",emisor);
    dataJson.agregarClaveValor("Mensaje",mensaje);

    JsonObject bodyJson;
    //string GCMToken= this->mensajeHTTP->getHeader("GChigihgMToken");
    //bodyJson["to"] = GCMToken;
    //Hardcodeado el cluente de mi comopu
    //Aca deberia sacar el token de las sesiones
    string tokenGCM = this->sesiones->getTokenGCMDe(receptor);
    //bodyJson.agregarClaveValor("to","APA91bFundy4qQCiRnhUbMOcsZEwUBpbuPjBm-wnyBv600MNetW5rp-5Cg32_UA0rY_gmqqQ8pf0Cn-nyqoYrAl6BQTPT3dXNYFuHeWYEIdLz0RwAhN2lGqdoiYnCM2V_O8MonYn3rL6hAtYaIz_b0Jl2xojcKIOqQ");
    bodyJson.agregarClaveValor("to",tokenGCM);
    bodyJson.agregarClaveValor("data",dataJson);
    //bodyJson["to"] = "APA91bFundy4qQCiRnhUbMOcsZEwUBpbuPjBm-wnyBv600MNetW5rp-5Cg32_UA0rY_gmqqQ8pf0Cn-nyqoYrAl6BQTPT3dXNYFuHeWYEIdLz0RwAhN2lGqdoiYnCM2V_O8MonYn3rL6hAtYaIz_b0Jl2xojcKIOqQ";
    //bodyJson["data"] = dataJson;
    //Json::FastWriter escritor;
    //requestGCM.setBody( escritor.write(bodyJson) );
    requestGCM.setBody( bodyJson.toString() );

    MensajeHTTPReply GCMreply = this->conexiones->enviarMensajeHTTP(&requestGCM,"80");


    cout<<"Mensaje de respuesta de GCM:\n"<<GCMreply.toString()<<"\n";

    //FALTARIA COMPARAR EL BODY QUE ES EL QUE DICE SI FUE SUCCES O FAIL
    return (GCMreply.getCodigo() == 200);

}
