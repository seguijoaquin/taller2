#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <fstream>
#include <map>
#include <thread>
#include <queue>


#include "SesionesDeUsuarios.h"


#include "Servicio.h"
#include "FactoryServicios.h"

#include "ManejadorDeConexiones.h"




class Servidor
{
    public:
        Servidor(string puerto, string direccionShared);
        virtual ~Servidor();

        void iniciarServidor();

        string getRespuestaDelServicio(MensajeHTTPRequest mensajeHTTPRequest);

        //BORRAR ESTO
        ManejadorDeConexiones* getManejador(){ return &this->manejadorDeConexiones; }

    protected:
    private:

        //CredencialesDeUsuarios* credencialesDeUsuarios;
        //Conversaciones* conversaciones;
        //SesionesDeUsuarios sesionesDeUsuarios;

        ManejadorDeConexiones manejadorDeConexiones;
        //void iniciarServidor();
        void iniciarBaseDeDatos();

        string puerto;

        FactoryServicios factoryServicios = FactoryServicios(&manejadorDeConexiones);

        static void escucharComandos(Servidor* servidor);
        static queue<string>* leerComandos(string ruta);
        static void recorrerComandos(queue<string>* comandos,Servidor* servidor);
        void interpretar(string comando);
        bool estaActivo();
        bool activo;
};



#endif // SERVIDOR_H
