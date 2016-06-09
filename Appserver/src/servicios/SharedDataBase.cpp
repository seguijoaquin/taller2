#include "SharedDataBase.h"

SharedDataBase::SharedDataBase(ManejadorDeConexiones* conexiones){
    this->conexiones = conexiones;
}

SharedDataBase::~SharedDataBase()
{
    //dtor
}

MensajeHTTPRequest SharedDataBase::armarRequest(string metodo, string uri, string bodyJson){
    MensajeHTTPRequest request;
    request.setMetodo(metodo);
    request.setURI(uri);
    request.agregarHeader("Host", "t2shared.herokuapp.com");
    request.agregarHeader("Content-Type", "application/json");
    request.setBody(bodyJson);
    return request;
}


MensajeHTTPReply SharedDataBase::enviarHTTPRequest(MensajeHTTPRequest& request){
    return this->conexiones->enviarMensajeHTTP(&request,"80");
}

int SharedDataBase::registrarUsuario(string bodyJson){

    MensajeHTTPRequest request = this->armarRequest("POST", "/users/",bodyJson);
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest(request);

    //Refactorizar: CODIGO_ALTA_CORRECTA.... etc
    int idCliente = -1;
    if (respuestaShared.getCodigo() == 201){
        JsonObject bodyRespuestaShared(respuestaShared.getBody());
        idCliente = (bodyRespuestaShared.getJsonObject("user")).getInt("id");
    }

    return idCliente;
}


string SharedDataBase::obtenerPerfilDelUsuario(int idUsuario){

    MensajeHTTPRequest request = this->armarRequest("GET", this->armarURIDeUsuario(idUsuario) ,"");

    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest(request);

    //Refactorizar: CODIGO_ALTA_CORRECTA.... etc
    //if (respustaShared.getCodigo() == 201){ //POR ALGUNA RAZON LO CAMBIARON A 200 EN EL SHARED

    /*int idCliente = 0;
    if (respuestaShared.getCodigo() == 201){
        JsonObject bodyRespuestaShared(respuestaShared.getBody());
        idCliente = (bodyRespuestaShared.getJsonObject("user")).getInt("id");
    }
    */

    return respuestaShared.getBody();
}



string SharedDataBase::obtenerListadoDeUsuarios(){
    MensajeHTTPRequest request = this->armarRequest("GET", "/users/" ,"");
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest(request);
    return respuestaShared.getBody();
}


bool SharedDataBase::eliminarUsuario(int idUsuario){
    MensajeHTTPRequest request = this->armarRequest("DELETE", this->armarURIDeUsuario(idUsuario) ,"");
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest(request);

    return (respuestaShared.getCodigo() == 200);
}





string SharedDataBase::armarURIDeUsuario(int idUsuario){
    string uri = "/users/";
    uri = uri + StringUtil::int2string(idUsuario);
    return uri;
}
