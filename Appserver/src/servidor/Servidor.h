#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "mongoose.h"
#include <iostream>
#include <fstream>
#include <map>
#include <thread>
#include "AtendedorHTTP.h"
#include "ConstantesEventosServicios.h"
#include "SesionesDeUsuarios.h"

#include "servicioRegistro.h"
#include "servicioLogin.h"

#include "ManejadorDeConexiones.h"


/*  CON ESTO ESTUVE PROBANDO SI HAY MULTITHREADING EN LAS CONEXIONES OUTBOUND
int tiempo;
*/

//const char* PATHLOGIN = "/login";

class Servidor
{
    public:
        Servidor();
        virtual ~Servidor();

        void iniciar();

        string getRespuestaDelServicio(MensajeHTTPRequest mensajeHTTPRequest);

    protected:
    private:

        CredencialesDeUsuarios* credencialesDeUsuarios;
        SesionesDeUsuarios sesionesDeUsuarios;

   //     mg_connection* conexionListening;
   //     mg_mgr manager;
   //     static void handlerServer(struct mg_connection* conexion, int evento, void* ev_data);
   //     void iniciarManager();
        void escucharMensajes();
        //Si es true escucha, si es false no y se cierra el server
   //     bool escuchar;

        ManejadorDeConexiones manejadorDeConexiones;

        void iniciarBaseDeDatos();



};



#endif // SERVIDOR_H
