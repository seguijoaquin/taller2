#include "ServicioPedirIntereses.h"

ServicioPedirIntereses::ServicioPedirIntereses(SharedDataBase* shared){
    ListadoDeIntereses intereses = shared->obtenerListadoDeIntereses();
    RespuestaPedirIntereses* respuestaIntereses = new RespuestaPedirIntereses();
    respuestaIntereses->setRespuestaInteresesPedidos(intereses);
    this->respuesta = respuestaIntereses;
}

ServicioPedirIntereses::~ServicioPedirIntereses()
{
    //dtor
}
