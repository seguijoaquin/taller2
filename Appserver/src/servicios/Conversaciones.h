#ifndef CONVERSACIONES_H
#define CONVERSACIONES_H

#include "BaseDeDatos.h"
#include <iostream>
#include "Mensajes.h"

using namespace std;

class Conversaciones
{
    public:
        Conversaciones(string ruta);
        virtual ~Conversaciones();
        Mensajes obtenerCantidadMensajesDesdeEntre(int cantidad, int desde, string usuario1, string usuario2);
        void agregarMensajeDePara(string& emisor,string& receptor, string& mensaje);
    protected:
    private:
        BaseDeDatos* conversaciones;
        void armarClaveDeLaConversacion(string& usuario1, string& usuario2, string& claveConversacion);
        void guardarConversacion(string& usuario1, string&usuario2, Mensajes& conversacion);

        string obtenerTodosLosMensajesEntre(string usuario1, string usuario2);
};

#endif // CONVERSACIONES_H
