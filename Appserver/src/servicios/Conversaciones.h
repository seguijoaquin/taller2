#ifndef CONVERSACIONES_H
#define CONVERSACIONES_H

#include "BaseDeDatos.h"
#include <iostream>
#include "Mensajes.h"

using namespace std;

/** Clase que abstrae la base de datos de conversaciones y su gestion. */

class Conversaciones
{
    public:
        Conversaciones(string ruta);
        virtual ~Conversaciones();
    
        /** Devuelve la cantidad de mensajes desde el ultimo mas nuevo hacia arriba. Es decir:
         *  User1- Hola
         *  User2- Hey
         *  User1- como estas?
         *  User2- Muy bien gracias!
         *  Con cantidad 2 desde 3 (Hey) devuelve:
         *  1) Hey
         *  2) Hola
         *  Los devuelve en orden cronologico.
         *  Precondicion: Desde comienza en 1 y representa al ultimo mensaje.
         */
        Mensajes obtenerCantidadMensajesDesdeEntre(int cantidad, int desde, string usuario1, string usuario2);
    
        /** Agrega un mensaje a la conversacion correspondiente a los usuarios pasados como parametro*/
        void agregarMensajeDePara(string& emisor,string& receptor, string& mensaje);
    protected:
    private:
        BaseDeDatos* conversaciones;
        void armarClaveDeLaConversacion(string& usuario1, string& usuario2, string& claveConversacion);
        void guardarConversacion(string& usuario1, string&usuario2, Mensajes& conversacion);

        string obtenerTodosLosMensajesEntre(string usuario1, string usuario2);
};

#endif // CONVERSACIONES_H
