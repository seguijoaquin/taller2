#include "CreatorServicio.h"

CreatorServicio::CreatorServicio()
{
    //ctor
}

CreatorServicio::~CreatorServicio()
{
    //dtor
}

Servicio* CreatorServicio::getServicio(){
    return this->servicio;
}
