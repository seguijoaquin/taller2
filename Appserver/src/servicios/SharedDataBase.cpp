#include "SharedDataBase.h"

SharedDataBase::SharedDataBase(ManejadorDeConexiones* conexiones){
    this->conexiones = conexiones;
}

SharedDataBase::~SharedDataBase(){
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


MensajeHTTPReply SharedDataBase::enviarHTTPRequest(string metodo, string uri, string bodyJson){
    MensajeHTTPRequest request = this->armarRequest(metodo, uri, bodyJson);
    return this->conexiones->enviarMensajeHTTP(&request,"80");
}





int SharedDataBase::registrarUsuario(string bodyJson){
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest("POST", "/users/",bodyJson);

    //Refactorizar: CODIGO_ALTA_CORRECTA.... etc
    int idCliente = -1;
    if (respuestaShared.getCodigo() == 201){
        JsonObject bodyRespuestaShared(respuestaShared.getBody());
        idCliente = (bodyRespuestaShared.getJsonObject("user")).getInt("id");
    }

    return idCliente;
}


Usuario SharedDataBase::obtenerPerfilDelUsuario(int idUsuario){
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest("GET", this->armarURIDeUsuario(idUsuario) ,"");

    //Refactorizar: CODIGO_ALTA_CORRECTA.... etc
    //if (respustaShared.getCodigo() == 201){ //POR ALGUNA RAZON LO CAMBIARON A 200 EN EL SHARED

    /*int idCliente = 0;
    if (respuestaShared.getCodigo() == 201){
        JsonObject bodyRespuestaShared(respuestaShared.getBody());
        idCliente = (bodyRespuestaShared.getJsonObject("user")).getInt("id");
    }
    */

    return Usuario(respuestaShared.getBody());
}



ListadoDeUsuarios* SharedDataBase::obtenerListadoDeUsuarios(){
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest("GET", "/users/" ,"");
    this->listadoDeUsuarios.agregarUsuarios( respuestaShared.getBody() );
    return &(this->listadoDeUsuarios);
}


bool SharedDataBase::eliminarUsuario(int idUsuario){
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest("DELETE", this->armarURIDeUsuario(idUsuario) ,"");
    return (respuestaShared.getCodigo() == 200);
}

string SharedDataBase::armarURIDeUsuario(int idUsuario){
    string uri = "/users/";
    uri = uri + StringUtil::int2string(idUsuario);
    return uri;
}

ListadoDeIntereses* SharedDataBase::obtenerListadoDeIntereses(){
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest("GET", "/interests","");

    this->listadoDeIntereses.agregarIntereses( respuestaShared.getBody() );
    return &(this->listadoDeIntereses);


}
