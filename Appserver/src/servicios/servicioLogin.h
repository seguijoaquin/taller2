#ifndef SERVICIOLOGIN_H
#define SERVICIOLOGIN_H
//#include "mongoose.h"
#include <iostream>
#include <map>
#include "MensajeHTTPRequest.h"
#include "SesionesDeUsuarios.h"
#include "CredencialesDeUsuarios.h"
#include "RespuestaDelLogin.h"
#include "SharedDataBase.h"

#include "Servicio.h"
#include <functional>

using namespace std;

class servicioLogin : public Servicio
{
    public:
        servicioLogin(SesionesDeUsuarios* sesionesDeUsuarios, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales, SharedDataBase* shared);
        virtual ~servicioLogin();

        //string getRespuesta();
    protected:
    private:
        MensajeHTTPRequest mensajeHTTP;


        CredencialesDeUsuarios* credenciales;

        SesionesDeUsuarios* sesionesDeUsuarios;

        SharedDataBase* shared;

        bool validarCredenciales();
        void realizarLogin();
        string generarToken(string usuario);

        void atenderLogin();
};

#endif // SERVICIOLOGIN_H
