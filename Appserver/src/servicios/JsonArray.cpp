#include "JsonArray.h"

JsonArray::JsonArray(){
    this->indiceActual = 0;
    this->jsonValor = Json::arrayValue;
}

JsonArray::JsonArray(string jsonTexto):JsonValor(jsonTexto){

}

JsonArray::JsonArray(const Json::Value& jsonValor):JsonValor(jsonValor){

}

bool JsonArray::operator>>(string& valor){
    if (this->indiceActual < this->size()){
        valor = (this->jsonValor[this->indiceActual]).asString();
        this->indiceActual++;
        return true;
    }
    else{
        return false;
    }
}

JsonValor JsonArray::operator[](int indice){
    return JsonValor(this->jsonValor[indice]);
}


void JsonArray::agregar(JsonValor& valor){
    this->jsonValor.append(valor.getJsonValue());
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
