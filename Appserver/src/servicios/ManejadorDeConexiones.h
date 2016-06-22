#ifndef MANEJADORDECONEXIONES_H
#define MANEJADORDECONEXIONES_H


#include <iostream>
#include "mongoose.h"

#include "MensajeHTTPRequest.h"
#include "ClienteDelSharedServer.h"

//#include "Servidor.h"
class Servidor;



using namespace std;

/** Clase que se encarga de gestionar las conexiones al servidor.*/

class ManejadorDeConexiones
{
    public:
        ManejadorDeConexiones();
        virtual ~ManejadorDeConexiones();


        /** Inicia como servidor para permitir la recepcion de mensajes http*/
        void iniciarConexionComoServidor(string puerto, Servidor* servidor);

        /** Deja de escuchar y permitir la recepcion de mensajes.*/
        void terminarConexionComoServidor();
        //void iniciarConexionComoCliente(string metodo, string uri, string body, string puertoLocal, string host, servicioRegistro* servicio);

        //void iniciarConexionComoCliente(string metodo, string uri, string body, string puertoLocal, string host, ClienteDelSharedServer* cliente);
        //MensajeHTTPReply enviarMensajeHTTP(string metodo, string uri, string body, string puertoLocal, string host);

        /** Envia un mensaje HTTP al shared server y nos devuelve espera la respuesta
        * como un MensajeHTTPReply
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
