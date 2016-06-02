#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "JsonValor.h"

class JsonObject: public JsonValor{
    public:
        JsonObject();
        virtual ~JsonObject();

        JsonValor operator[](string clave);
        JsonValor getValor(string clave);
        void agregarClaveValor(string clave, string valor);
        void agregarClaveValor(string clave, JsonValor& valor);
        //Por ahora no necesito agregar nada
    protected:
    private:

};

#endif // JSONOBJECT_H
