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
#include "ServicioChat.h"

#include "ManejadorDeConexiones.h"


//const char* PATHLOGIN = "/login";

class Servidor
{
    public:
        Servidor();
        virtual ~Servidor();

        void iniciarServidor();

        string getRespuestaDelServicio(MensajeHTTPRequest mensajeHTTPRequest);

    protected:
    private:

        CredencialesDeUsuarios* credencialesDeUsuarios;
        SesionesDeUsuarios sesionesDeUsuarios;

        ManejadorDeConexiones manejadorDeConexiones;
        //void iniciarServidor();
        void iniciarBaseDeDatos();
};



#endif // SERVIDOR_H
