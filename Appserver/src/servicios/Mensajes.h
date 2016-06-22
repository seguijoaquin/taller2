#ifndef MENSAJES_H
#define MENSAJES_H

#include "JsonArray.h"
#include "JsonObject.h"
#include <string>

using namespace std;

/** Esta clase abstrae el formato de los mensajes, ahora se usa Json,
* pero si se cambiara a algo como XML, por decir un ejemplo,
* se mantendria la interfaz
*/
//Esta clase ademas facilita las pruebas
class Mensajes
{
    public:


        Mensajes();

        /** Es responsabilidad del que llama que el jsonTexto este bien formateado
        * (el formato de cada mensaje)
        */
        Mensajes(string jsonTexto);
        virtual ~Mensajes();


        string getEmisor(int nroMensaje);
        string getMensaje(int nroMensaje);

        string toString();
        int getTamanio();

        /** Agrega el mensaje a la estructura que los contiene.*/
        void agregarMensaje(string emisor, string mensaje);
    protected:
    private:
        bool indiceValido(int indice);
        JsonArray jArray;
};

#endif // MENSAJES_H
