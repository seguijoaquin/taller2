#ifndef CONVERSACIONES_H
#define CONVERSACIONES_H

#include "BaseDeDatos.h"
//#include "json/json.h"
//#include "json/json-forwards.h"
#include <iostream>
//#include "Conversacion.h"
#include "Mensajes.h"
#include "JsonArray.h"
#include "JsonObject.h"

using namespace std;

class Conversaciones
{
    public:
        Conversaciones(string ruta);
        virtual ~Conversaciones();

        //Precondicion: que los nombres para identificar a los usuarios no tengan espacios
        //void iniciarConversacionEntre(string& usuario1, string& usuario2);
        //Json::Value* obtenerCoversacionEntre(string& usuario1,string& usuario2);
        //Conversacion* obtenerCoversacionEntre(string& usuario1,string& usuario2, int dummy);
        Mensajes obtenerCantidadMensajesDesdeEntre(int cantidad, int desde, string usuario1, string usuario2);
        void agregarMensajeDePara(string& emisor,string& receptor, string& mensaje);
    protected:
    private:
        BaseDeDatos* conversaciones;
        //void armarConversacionVacia(string& conversacion);
        //Probablemente convenga tener una clase que se llame Conversacion
        //Idem clase JSONObjeto y JSONArray
        //Json::Value* armarConversacionVacia(/*string& conversacion*/);
        //bool noExisteConversacionEntre(string& usuario1, string& usuario2);
        void armarClaveDeLaConversacion(string& usuario1, string& usuario2, string& claveConversacion);
        //void guardarConversacion(string& claveConversacion, string& conversacion);
        //No me gusta estar pasando Json::Values
        //void guardarConversacion(string& usuario1, string& usuario2, Json::Value* conversacion);
        void guardarConversacion(string& usuario1, string&usuario2, JsonArray& conversacion);

        string obtenerTodosLosMensajesEntre(string usuario1, string usuario2);
};

#endif // CONVERSACIONES_H
