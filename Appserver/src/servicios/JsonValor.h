#ifndef JSONVALOR_H
#define JSONVALOR_H

#include "json/json.h"
#include <string>

using namespace std;

//Clase con la que intento wrappear a jsoncpp
class JsonValor
{
    public:
        JsonValor();
        //CREO que deberia crearlo por referencia...CREO
        JsonValor(const Json::Value& jsonValor);
        Json::Value& getValor();
        virtual ~JsonValor();
        string toString();
    protected:
        Json::Value jsonValor;
    private:

};

#endif // JSONVALOR_H
