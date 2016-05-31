#ifndef SERVICIOMENSAJES_H
#define SERVICIOMENSAJES_H

#include "MensajeHTTPRequest.h"
#include "SesionesDeUsuarios.h"
#include "Conversaciones.h"

class ServicioMensajes
{
    public:
        ServicioMensajes(MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones);
        virtual ~ServicioMensajes();

        string getRespuesta();
    protected:
    private:
        MensajeHTTPRequest* mensajeHTTP;
        SesionesDeUsuarios* sesiones;
        Conversaciones* conversaciones;

        string respuesta;
        void atenderMensajes();
};

#endif // SERVICIOMENSAJES_H
