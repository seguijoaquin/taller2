#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "JsonValor.h"

class JsonObject: public JsonValor{
    public:
        JsonObject();
        JsonObject(string jsonTexto);
        JsonObject(const Json::Value& jsonValor);
        virtual ~JsonObject();

        JsonValor operator[](string clave);
        JsonObject getJsonObject(string clave);
        int getInt(string clave);

        void agregarClaveValor(string clave, string valor);
        void agregarClaveValor(string clave, JsonValor& valor);




    protected:
    private:

};

#endif // JSONOBJECT_H
