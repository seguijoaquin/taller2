#include "SharedDataBase.h"

SharedDataBase::SharedDataBase(ManejadorDeConexiones* conexiones){
    this->conexiones = conexiones;
}

SharedDataBase::~SharedDataBase()
{
    //dtor
}

bool SharedDataBase::registrarUsuario(string bodyJson){
    MensajeHTTPRequest request;
    request.setMetodo("POST");
    request.setURI("/users/");
    request.agregarHeader("Host", "t2shared.herokuapp.com");
    request.agregarHeader("Content-Type", "application/json");
    request.setBody(bodyJson);

    MensajeHTTPReply respustaShared = this->conexiones->enviarMensajeHTTP(&request,"80");

    //Refactorizar: CODIGO_ALTA_CORRECTA.... etc
    //if (respustaShared.getCodigo() == 201){ //POR ALGUNA RAZON LO CAMBIARON A 200 EN EL SHARED

    return (respustaShared.getCodigo() == 201);

    /*if (respustaShared.getCodigo() == 200){
        return true;
    }
    else{
        return false;
    }*/

}



