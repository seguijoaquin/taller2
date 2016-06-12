#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "JsonValor.h"
#include "JsonArray.h"

class JsonObject: public JsonValor{
    public:
        JsonObject();
        JsonObject(string jsonTexto);
        JsonObject(const Json::Value& jsonValor);
        virtual ~JsonObject();

        JsonValor operator[](string clave);
        JsonObject getJsonObject(string clave);
        JsonArray getJsonArray(string clave);

        int getInt(string clave);

        void agregarClaveValor(string clave, string valor);
        void agregarClaveValor(string clave, JsonValor& valor);




    protected:
    private:

};

#endif // JSONOBJECT_H
