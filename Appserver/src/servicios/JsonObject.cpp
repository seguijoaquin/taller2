#include "JsonObject.h"

JsonObject::JsonObject(){
    this->jsonValor = Json::objectValue;
}

JsonValor JsonObject::operator[](string clave){
    return JsonValor(this->jsonValor[clave]);
}

void JsonObject::agregarClaveValor(string clave, string valor){
    this->jsonValor[clave] = valor;
}

JsonObject::~JsonObject()
{
    //dtor
}
