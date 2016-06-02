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

void JsonObject::agregarClaveValor(string clave, JsonValor& valor){
    this->jsonValor[clave] = valor.getJsonValue();
}



JsonObject::~JsonObject()
{
    //dtor
}
