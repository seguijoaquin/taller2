#ifndef SERVICIOLOGIN_H
#define SERVICIOLOGIN_H
//#include "mongoose.h"
#include <iostream>
#include <map>
#include "MensajeHTTPRequest.h"
#include "SesionesDeUsuarios.h"
#include "CredencialesDeUsuarios.h"
#include "RespuestaDelLogin.h"

#include "Servicio.h"

using namespace std;

/** Clase que contiene la logica
 * correspondiente al servicio de
 * log in de usuarios provisto por
 * el servidor. Actua ante la llegada
 * del mensaje http correspondiente.
 */


class servicioLogin : public Servicio
{
    public:
    
        servicioLogin(SesionesDeUsuarios* sesionesDeUsuarios, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales);
        virtual ~servicioLogin();

        //string getRespuesta();
    protected:
    private:
        MensajeHTTPRequest mensajeHTTP;


        CredencialesDeUsuarios* credenciales;

        SesionesDeUsuarios* sesionesDeUsuarios;

        bool validarCredenciales();
        void realizarLogin();
        string generarToken();

        void atenderLogin();
};

#endif // SERVICIOLOGIN_H
