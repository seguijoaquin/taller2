#include "ServicioPedirIntereses.h"

ServicioPedirIntereses::ServicioPedirIntereses(SharedDataBase* shared){
    Logger::Instance()->log(INFO, "Se crea el Servicio para Pedir Intereses");
    ListadoDeIntereses intereses = shared->obtenerListadoDeIntereses();
    RespuestaPedirIntereses* respuestaIntereses = new RespuestaPedirIntereses();
    respuestaIntereses->setRespuestaInteresesPedidos(intereses);
    this->respuesta = respuestaIntereses;
}

ServicioPedirIntereses::~ServicioPedirIntereses()
{
    //dtor
}
