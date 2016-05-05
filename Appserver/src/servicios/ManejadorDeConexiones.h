#ifndef MANEJADORDECONEXIONES_H
#define MANEJADORDECONEXIONES_H


#include <iostream>
#include "mongoose.h"

#include "ClienteDelSharedServer.h"

//#include "Servidor.h"
class Servidor;



using namespace std;

class ManejadorDeConexiones
{
    public:
        ManejadorDeConexiones();
        virtual ~ManejadorDeConexiones();

        void iniciarConexionComoServidor(string puerto, Servidor* servidor);
        void terminarConexionComoServidor();
        //void iniciarConexionComoCliente(string metodo, string uri, string body, string puertoLocal, string host, servicioRegistro* servicio);

        void iniciarConexionComoCliente(string metodo, string uri, string body, string puertoLocal, string host, ClienteDelSharedServer* cliente);
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
