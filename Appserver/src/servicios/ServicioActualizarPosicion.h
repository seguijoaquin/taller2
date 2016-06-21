#ifndef SERVICIOACTUALIZARPOSICION_H
#define SERVICIOACTUALIZARPOSICION_H

#include <Servicio.h>
#include "SharedDataBase.h"
#include "CredencialesDeUsuarios.h"
#include "RespuestaActualizarPosicion.h"



class ServicioActualizarPosicion : public Servicio
{
    public:
        ServicioActualizarPosicion(SharedDataBase* shared, CredencialesDeUsuarios* credenciales, MensajeHTTPRequest* mensaje);
        virtual ~ServicioActualizarPosicion();
    protected:
    private:
        SharedDataBase* shared;
        CredencialesDeUsuarios* credenciales;
        MensajeHTTPRequest* mensajeHTTP;

        void atenderActualizacionPosicion();
};

#endif // SERVICIOACTUALIZARPOSICION_H
