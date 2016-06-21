#include "CreatorPedirIntereses.h"

CreatorPedirIntereses::CreatorPedirIntereses(SharedDataBase* shared){
    this->servicio = new ServicioPedirIntereses(shared);
}

CreatorPedirIntereses::~CreatorPedirIntereses()
{
    //dtor
}
