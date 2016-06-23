#ifndef SERVICIOLOGOUT_H
#define SERVICIOLOGOUT_H

#include <Servicio.h>
#include "SesionesDeUsuarios.h"
#include "MensajeHTTPRequest.h"
#include "RespuestaServicioLogout.h"

class ServicioLogout : public Servicio
{
    public:
        ServicioLogout(MensajeHTTPRequest* mensaje, SesionesDeUsuarios* sesiones);
        virtual ~ServicioLogout();
    protected:
    private:
        MensajeHTTPRequest* mensaje;
        SesionesDeUsuarios* sesiones;

        void atenderLogout();
};

#endif // SERVICIOLOGOUT_H
