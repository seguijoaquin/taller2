#include "SharedDataBase.h"

SharedDataBase::SharedDataBase(ManejadorDeConexiones* conexiones, string direccion){
    this->conexiones = conexiones;
    this->direccionShared = direccion;
}

SharedDataBase::~SharedDataBase(){
    //dtor
}

void SharedDataBase::cambiarDireccion(string nuevaDireccion){
    this->direccionShared = nuevaDireccion;
}



MensajeHTTPRequest SharedDataBase::armarRequest(string metodo, string uri, string bodyJson){
    MensajeHTTPRequest request;
    request.setMetodo(metodo);
    request.setURI(uri);
    request.agregarHeader("Host", this->direccionShared);
    request.agregarHeader("Content-Type", "application/json");
    request.setBody(bodyJson);
    return request;
}


MensajeHTTPReply SharedDataBase::enviarHTTPRequest(string metodo, string uri, string bodyJson){
    MensajeHTTPRequest request = this->armarRequest(metodo, uri, bodyJson);
    Logger::Instance()->log(INFO, "Se envia un mensaje al Shared Server");
    return this->conexiones->enviarMensajeHTTP(&request,"80");
}



int SharedDataBase::registrarUsuario(Usuario& usuario){
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest("POST", "/users/",usuario.toString());


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

    /*int idCliente = 0;
    if (respuestaShared.getCodigo() == 201){
        JsonObject bodyRespuestaShared(respuestaShared.getBody());
        idCliente = (bodyRespuestaShared.getJsonObject("user")).getInt("id");
    }
    */

    return Usuario(respuestaShared.getBody());
}



ListadoDeUsuarios SharedDataBase::obtenerListadoDeUsuarios(){
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest("GET", "/users/" ,"");
    ListadoDeUsuarios usuarios;
    usuarios.agregarUsuarios( respuestaShared.getBody() );
    return usuarios;
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

ListadoDeIntereses SharedDataBase::obtenerListadoDeIntereses(){
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest("GET", "/interests","");
    this->listadoDeIntereses.agregarIntereses( respuestaShared.getBody() );
    return (this->listadoDeIntereses);
}


bool SharedDataBase::modificarFotoPerfil(int idUsuario, string fotoBase64){
    string uri = this->armarURIDeUsuario(idUsuario);
    uri = uri + "/photo";
    JsonObject jsonFoto;
    jsonFoto.agregarClaveValor("photo", fotoBase64);
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest("PUT", uri , jsonFoto.toString());

    return (respuestaShared.getCodigo() == 200);
}


bool SharedDataBase::modificarPerfilUsuario(Usuario& usuario){
    string uri = this->armarURIDeUsuario(usuario.getId());
    MensajeHTTPReply respuestaShared = this->enviarHTTPRequest("PUT", uri, usuario.toString());
    return (respuestaShared.getCodigo() == 200);
}



