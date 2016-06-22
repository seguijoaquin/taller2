#ifndef JSONVALOR_H
#define JSONVALOR_H

#include "json/json.h"
#include <string>
#include "Logger.h"

using namespace std;

/*!
 * Clase que wrappea a la libreria de json utilizada.
 */
class JsonValor
{
    public:
        JsonValor();
        JsonValor(string jsonTexto);
        //CREO que deberia crearlo por referencia...CREO
        JsonValor(const Json::Value& jsonValor);
        Json::Value& getJsonValue();

        int size();/*!< Devuelve el tamanio del json valor*/

        virtual ~JsonValor();
        string toString(); /*!< Devuelvo el json valor en formato de string*/
    protected:
        Json::Value jsonValor;
    private:

};

#endif // JSONVALOR_H
