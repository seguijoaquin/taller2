#ifndef SERVICIOEDITARPERFIL_H
#define SERVICIOEDITARPERFIL_H

#include <Servicio.h>
#include "SharedDataBase.h"
#include "CredencialesDeUsuarios.h"
#include "RespuestaEdicionPerfil.h"

class ServicioEditarPerfil : public Servicio
{
    public:
        ServicioEditarPerfil(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, CredencialesDeUsuarios* credenciales);
        virtual ~ServicioEditarPerfil();
    protected:
    private:
        SharedDataBase* shared;
        MensajeHTTPRequest* mensajeHTTP;
        CredencialesDeUsuarios* credenciales;

        void atenderEdicion();

};

#endif // SERVICIOEDITARPERFIL_H
