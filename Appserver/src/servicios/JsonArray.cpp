#include "JsonArray.h"

JsonArray::JsonArray(){
    this->jsonValor = Json::arrayValue;
}

JsonValor JsonArray::operator[](int indice){
    return JsonValor(this->jsonValor[indice]);
}


void JsonArray::agregar(JsonValor& valor){
    this->jsonValor.append(valor.getValor());
}

void JsonArray::agregar(string& valor){
    this->jsonValor.append(valor);
}
void JsonArray::agregar(int& valor){
    this->jsonValor.append(valor);
}


JsonArray::~JsonArray()
{
    //dtor
}
