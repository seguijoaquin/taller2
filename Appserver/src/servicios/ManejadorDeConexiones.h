#ifndef MANEJADORDECONEXIONES_H
#define MANEJADORDECONEXIONES_H


#include <iostream>
#include "mongoose.h"

#include "MensajeHTTPRequest.h"
#include "ClienteDelSharedServer.h"

#include "Logger.h"

//#include "Servidor.h"
class Servidor;



using namespace std;

/** Clase que se encarga de gestionar las conexiones como servidor y conexiones externas.*/

class ManejadorDeConexiones
{
    public:
        ManejadorDeConexiones();
        virtual ~ManejadorDeConexiones();


        /** Inicia como servidor para permitir la recepcion de mensajes HTTP*/
        void iniciarConexionComoServidor(string puerto, Servidor* servidor);

        /** Deja de escuchar y permitir la recepcion de mensajes.*/
        void terminarConexionComoServidor();


        /** Envia un mensaje HTTP al host indicado en el request y devuelve la respuesta
        *  al mensaje enviado
        */
        MensajeHTTPReply enviarMensajeHTTP(MensajeHTTPRequest* request, string puertoLocal);


    protected:
    private:
        mg_mgr manager;
        static void handlerServer(struct mg_connection* conexion, int evento, void* ev_data);
        static void handlerCliente(struct mg_connection* conexion, int evento, void* ev_data);
        static int tiempo; //SOLO PARA PROBAR SI ERA UNO O DOS THREADS

        bool escuchar;
        void escucharMensajes();

};

#endif // MANEJADORDECONEXIONES_H
