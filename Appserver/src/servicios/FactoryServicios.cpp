#include "FactoryServicios.h"

FactoryServicios::FactoryServicios(ManejadorDeConexiones* conexiones){
    this->conversaciones = new Conversaciones("./Conversaciones");
    this->sesiones = new SesionesDeUsuarios();
    this->credenciales = new CredencialesDeUsuarios("./usuariosRegistrados");
    this->conexiones = conexiones;

    this->shared = new SharedDataBase(this->conexiones, "t2shared.herokuapp.com");
    this->mensajero = new Mensajero(this->conexiones, this->sesiones);

    this->administradorCandidatos = new AdministradorCandidatos(this->shared);
}

FactoryServicios::~FactoryServicios(){
    delete this->conversaciones;
    delete this->sesiones;
    delete this->credenciales;
    delete this->shared;
    delete this->mensajero;
    delete this->administradorCandidatos;
}


Servicio* FactoryServicios::fabricarServicio(MensajeHTTPRequest httpRequest){

    Servicio* servicio;
    CreatorServicio* creator = nullptr;

    if (compararMetodoHTTP(httpRequest, "POST")){
        if (compararUriHTTP(httpRequest, "/chat")){

            creator = new CreatorChat(this->mensajero,&httpRequest,this->sesiones, this->conversaciones, this->administradorCandidatos);
        }
        else if (compararUriHTTP(httpRequest, "/matcheo")){
            creator = new CreatorVotacion(this->shared, this->mensajero, &httpRequest,this->sesiones, this->administradorCandidatos);
        }
    }
    else if (compararMetodoHTTP(httpRequest, "GET")){
        if (compararUriHTTP(httpRequest, "/login")){
            creator = new CreatorLogin(this->sesiones, httpRequest, this->credenciales);
        }
        else if (compararUriHTTP(httpRequest, "/mensajes")){
            creator = new CreatorServicioMensajes(&httpRequest, this->sesiones,this->conversaciones);
        }
        else if (compararUriHTTP(httpRequest, "/perfil")){
            creator = new CreatorBusquedaCandidato(this->administradorCandidatos, &httpRequest, this->sesiones);
        }
        else if (compararUriHTTP(httpRequest, "/intereses")){
            creator = new CreatorPedirIntereses(this->shared);
        }
        else if (compararUriHTTP(httpRequest, "/info")){
            creator = new CreatorPedirInformacion(this->shared, &httpRequest, this->credenciales, this->sesiones, this->administradorCandidatos);
        }
        else if (compararUriHTTP(httpRequest, "/test")){
            creator = nullptr;
        }
    }
    else if (compararMetodoHTTP(httpRequest, "PUT")){
        if (compararUriHTTP(httpRequest, "/registro")){
            creator = new CreatorRegistro(this->shared, httpRequest, this->credenciales, this->administradorCandidatos);
        }
        else if (compararUriHTTP(httpRequest, "/foto")){
            creator = new CreatorModificarFoto(this->shared, &httpRequest, this->sesiones, this->credenciales);
        }
        else if (compararUriHTTP(httpRequest, "/gps")){
            creator = new CreatorActualizarPosicion(this->shared, &httpRequest, this->sesiones, this->credenciales);
        }
        else if (compararUriHTTP(httpRequest, "/editar")){
            creator = new CreatorEditarPerfil(this->shared, &httpRequest, this->sesiones, this->credenciales);
        }
    }
    else if (compararMetodoHTTP(httpRequest, "DELETE")){
        if (compararUriHTTP(httpRequest, "/eliminar")){
            creator = new CreatorEliminacion(this->shared, &httpRequest, this->credenciales, this->sesiones);
        }
    }

    if (creator != nullptr){
        servicio = creator->getServicio();
        delete creator;
    }
    else{
        servicio = new ServicioInexistente();
    }
    return servicio;
}


bool FactoryServicios::compararMetodoHTTP(MensajeHTTPRequest& httpRequest, string metodo){
    return ( httpRequest.getMetodo() == metodo );
}


bool FactoryServicios::compararUriHTTP(MensajeHTTPRequest& httpRequest, string uri){
    return ( httpRequest.getURI() == uri );
}



void FactoryServicios::cambiarShared(string direccion){
    this->shared->cambiarDireccion(direccion);
}

