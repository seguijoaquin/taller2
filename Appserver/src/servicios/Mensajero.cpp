#include "Mensajero.h"

Mensajero::Mensajero(ManejadorDeConexiones* conexiones, SesionesDeUsuarios* sesiones){
    this->conexiones = conexiones;
}

Mensajero::~Mensajero()
{
    //dtor
}


bool Mensajero::enviarMensaje(string emisor, string receptor, string mensaje){

    MensajeHTTPRequestGCM requestGCM;
    ////////////////////////////////REFACTORIZAR//////////////////////////////////////
    Json::Value bodyJson = Json::objectValue;
    Json::Value dataJson = Json::objectValue;
    //Hardcodeado el cluente de mi comopu

    //Aca deberia sacar el token de las sesiones
    bodyJson["to"] = "APA91bFundy4qQCiRnhUbMOcsZEwUBpbuPjBm-wnyBv600MNetW5rp-5Cg32_UA0rY_gmqqQ8pf0Cn-nyqoYrAl6BQTPT3dXNYFuHeWYEIdLz0RwAhN2lGqdoiYnCM2V_O8MonYn3rL6hAtYaIz_b0Jl2xojcKIOqQ";
    //string GCMToken= this->mensajeHTTP->getHeader("GChigihgMToken");
    //bodyJson["to"] = "APA91bFundy4qQCiRnhUbMOcsZEwUBpbuPjBm-wnyBv600MNetW5rp-5Cg32_UA0rY_gmqqQ8pf0Cn-nyqoYrAl6BQTPT3dXNYFuHeWYEIdLz0RwAhN2lGqdoiYnCM2V_O8MonYn3rL6hAtYaIz_b0Jl2xojcKIOqQ";
    //bodyJson["to"] = GCMToken;
    dataJson["Emisor"] = emisor;
    dataJson["Mensaje"] = mensaje;
    bodyJson["data"] = dataJson;
    Json::FastWriter escritor;
    requestGCM.setBody( escritor.write(bodyJson) );
    MensajeHTTPReply GCMreply = this->conexiones->enviarMensajeHTTP(&requestGCM,"80");


    cout<<"Mensaje de respuesta de GCM:\n"<<GCMreply.toString()<<"\n";

    //FALTARIA COMPARAR EL BODY QUE ES EL QUE DICE SI FUE SUCCES O FAIL
    return (GCMreply.getCodigo() == 200);

}
