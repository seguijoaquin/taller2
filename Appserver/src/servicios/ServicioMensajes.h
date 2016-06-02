#ifndef SERVICIOMENSAJES_H
#define SERVICIOMENSAJES_H

#include "MensajeHTTPRequest.h"
#include "SesionesDeUsuarios.h"
#include "Conversaciones.h"
#include "RespuestaMensajes.h"

#include "Servicio.h"

class ServicioMensajes : public Servicio
{
    public:
        ServicioMensajes(MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones);
        virtual ~ServicioMensajes();

        //string getRespuesta();
    protected:
    private:
        MensajeHTTPRequest* mensajeHTTP;
        SesionesDeUsuarios* sesiones;
        Conversaciones* conversaciones;

        void atenderMensajes();
};

#endif // SERVICIOMENSAJES_H
