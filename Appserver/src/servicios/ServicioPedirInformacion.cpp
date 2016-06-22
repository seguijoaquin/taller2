#include "ServicioPedirInformacion.h"

ServicioPedirInformacion::ServicioPedirInformacion(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, CredencialesDeUsuarios* credenciales){
    Logger::Instance()->log(INFO, "Se crea el Servicio para Pedir Informacion sobre un Usuario");
    this->shared = shared;
    this->mensajeHTTP = mensajeHTTP;
    this->credenciales = credenciales;

    this->atenderPedidoDeInformacion();
}

ServicioPedirInformacion::~ServicioPedirInformacion()
{
    //dtor
}


void ServicioPedirInformacion::atenderPedidoDeInformacion(){
    int idSharedUsuarioPedido = this->credenciales->getIDSharedDe(  this->mensajeHTTP->getHeader("UsuarioPedido")  );
    Usuario usuario = this->shared->obtenerPerfilDelUsuario(idSharedUsuarioPedido );
    RespuestaInformacionPedida* respuestaInformacion = new RespuestaInformacionPedida();
    respuestaInformacion->setRespuestaInformacionPedida(usuario);
    this->respuesta = respuestaInformacion;
}
