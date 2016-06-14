#include "Interes.h"

Interes::Interes(string jsonInteres){
    JsonObject datos(jsonInteres);

    this->categoria = datos.getString("category");
    this->valor = datos.getString("value");
}

Interes::~Interes()
{
    //dtor
}

string Interes::getCategoria(){
    return this->categoria;
}

string Interes::getValor(){
    return this->valor;
}
