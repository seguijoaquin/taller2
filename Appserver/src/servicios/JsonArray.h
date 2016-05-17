#ifndef JSONARRAY_H
#define JSONARRAY_H

#include "JsonValor.h"
using namespace std;


class JsonArray: public JsonValor{
    public:
        //El jsonValue TIENE que ser un array
        JsonArray();
        virtual ~JsonArray();

        JsonValor operator[](int indice);
        void agregar(JsonValor& valor);
        void agregar(string& valor);
        void agregar(int& valor);

    protected:
    private:

};

#endif // JSONARRAY_H
