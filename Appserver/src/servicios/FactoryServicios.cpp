#include "FactoryServicios.h"

FactoryServicios::FactoryServicios(ManejadorDeConexiones* conexiones){
    this->conexiones = conexiones;
}

FactoryServicios::~FactoryServicios(){
    //dtor
}


Servicio* FactoryServicios::fabricarServicio(MensajeHTTPRequest httpRequest){

    Servicio* servicio;

    if (compararMetodoHTTP(httpRequest, "POST")){
        if (compararUriHTTP(httpRequest, "/chat")){
            servicio = new ServicioChat(this->conexiones,&httpRequest,&this->sesiones, &this->conversaciones);
        }
    }
    else if (compararMetodoHTTP(httpRequest, "GET")){
        if (compararUriHTTP(httpRequest, "/login")){
            servicio = new servicioLogin(&this->sesiones, httpRequest, &this->credenciales);
        }
        else if (compararUriHTTP(httpRequest, "/mensajes")){
            servicio = new ServicioMensajes (&httpRequest, &this->sesiones,&this->conversaciones);
        }
        else if (compararUriHTTP(httpRequest, "/test")){
            servicio = nullptr;
        }
    }
    else if (compararMetodoHTTP(httpRequest, "PUT")){
        if (compararUriHTTP(httpRequest, "/registro")){
            servicio = new servicioRegistro((this->conexiones), httpRequest, &this->credenciales);
        }
    }
    else if (compararMetodoHTTP(httpRequest, "DELETE")){
        servicio = nullptr;
    }

    return servicio;
}


bool FactoryServicios::compararMetodoHTTP(MensajeHTTPRequest& httpRequest, string metodo){
    return ( httpRequest.getMetodo() == metodo );
}


bool FactoryServicios::compararUriHTTP(MensajeHTTPRequest& httpRequest, string uri){
    return ( httpRequest.getURI() == uri );
}




