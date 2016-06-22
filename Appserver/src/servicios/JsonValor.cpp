#include "JsonValor.h"

JsonValor::JsonValor(){

}

JsonValor::JsonValor(string jsonTexto){
    Json::Reader reader;
    reader.parse(jsonTexto,this->jsonValor);
}

JsonValor::JsonValor(const Json::Value& jsonValor){
    this->jsonValor = jsonValor;
}


Json::Value& JsonValor::getJsonValue(){
    return this->jsonValor;
}

int JsonValor::size(){
    return this->jsonValor.size();
}

string JsonValor::toString(){
    //Json::FastWriter writer;
    Json::StyledWriter writer;
    string jsonString = writer.write(this->jsonValor);
    Logger::Instance()->log(DEBUG, "Json String:\n" + jsonString);
    return jsonString;
}

JsonValor::~JsonValor()
{
    //dtor
}
