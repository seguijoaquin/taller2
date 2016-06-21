#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "JsonValor.h"
#include "JsonArray.h"

/*!
 * Esta clase permite manejar json objects
 */

class JsonObject: public JsonValor{
    public:
        JsonObject();
        JsonObject(string jsonTexto);
        JsonObject(const Json::Value& jsonValor);
        virtual ~JsonObject();

        JsonValor operator[](string clave);/*!< Permite acceder a la clave pasada como parametro*/
        JsonObject getJsonObject(string clave);/*!< Devuelve el valor de la clave interpretado como JsonObject*/
        JsonArray getJsonArray(string clave);/*!< Devuelve el valor de la clave interpretado como JsonArray*/

        int getInt(string clave);/*!< Devuelve el valor de la clave interpretado como int*/
        double getDouble(string clave);/*!< Devuelve el valor de la clave interpretado como double*/
        string getString(string clave);/*!<Devuelve el valor de la clave interpretado como string*/


        void agregarClaveValor(string clave, string valor);/*!< Permite agregar un par clave valor al JsonObject donde el valor es un string*/
        void agregarClaveValor(string clave, int valor);/*!< Permite agregar un par clave valor al JsonObject donde el valor es un int*/
        void agregarClaveValor(string clave, double valor);/*!< Permite agregar un par clave valor al JsonObject donde el valor es un double*/
        void agregarClaveValor(string clave, JsonValor& valor);/*!< Permite agregar un par clave valor al JsonObject donde el valor es un JsonValor*/




    protected:
    private:

};

#endif // JSONOBJECT_H
