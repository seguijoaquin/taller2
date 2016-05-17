#include "JsonValor.h"

JsonValor::JsonValor(){

}

JsonValor::JsonValor(const Json::Value& jsonValor){
    this->jsonValor = jsonValor;
}


Json::Value& JsonValor::getValor(){
    return this->jsonValor;
}

string JsonValor::toString(){
    Json::FastWriter writer;
    return writer.write(this->jsonValor);
}

JsonValor::~JsonValor()
{
    //dtor
}
