#ifndef JSONARRAY_H
#define JSONARRAY_H

#include "JsonValor.h"
using namespace std;


class JsonArray: public JsonValor{
    public:
        //El jsonValue TIENE que ser un array
        JsonArray();
        JsonArray(string jsonTexto);
        virtual ~JsonArray();


        bool operator>>(string& valor);
        JsonValor operator[](int indice);

        void agregar(JsonValor& valor);
        void agregar(string& valor);
        void agregar(int& valor);

    protected:
    private:
        int indiceActual;

};

#endif // JSONARRAY_H
