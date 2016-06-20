#ifndef JSONARRAY_H
#define JSONARRAY_H

#include "JsonValor.h"

using namespace std;

    /*! 
     * Permite manejar jsonarrays
     */

class JsonArray: public JsonValor{
    public:
        //El jsonValue TIENE que ser un array
        JsonArray();
        JsonArray(string jsonTexto);
        JsonArray(const Json::Value& jsonValor);
        virtual ~JsonArray();


        bool operator>>(string& valor); /*!< Permite iterar el array de a un elemento por vez, copia en valor el elemento actual y devuelve true. Si se pasa del limite del array no se modifica el valor y devuelve false*/

        JsonValor operator[](int indice);/*!< Permite acceder de forma aleatoria al indice pasado por parametro*/

        void agregar(JsonValor& valor);/*!< Agrega el valor pasado por parametro al array*/
        void agregar(string& valor); /*!< Agrega un string al Array*/
        void agregar(int& valor); /*!< Agrega un numero entero al array*/

    protected:
    private:
        int indiceActual;

};

#endif // JSONARRAY_H
