#include "JsonObject.h"

JsonObject::JsonObject(){
    this->jsonValor = Json::objectValue;
}

JsonObject::JsonObject(string jsonTexto):JsonValor(jsonTexto){

}

JsonObject::JsonObject(const Json::Value& jsonValor):JsonValor(jsonValor){

}


JsonValor JsonObject::operator[](string clave){
    return JsonValor(this->jsonValor[clave]);
}


JsonObject JsonObject::getJsonObject(string clave){
    return JsonObject(this->jsonValor[clave]);
}

int JsonObject::getInt(string clave){
    return (this->jsonValor[clave]).asInt();
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
