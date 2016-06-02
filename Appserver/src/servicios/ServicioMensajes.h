#ifndef SERVICIOMENSAJES_H
#define SERVICIOMENSAJES_H

#include "MensajeHTTPRequest.h"
#include "SesionesDeUsuarios.h"
#include "Conversaciones.h"
#include "RespuestaMensajes.h"

class ServicioMensajes
{
    public:
        ServicioMensajes(MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones);
        virtual ~ServicioMensajes();

        //string getRespuesta();
        RespuestaDelServicio* getRespuesta();
    protected:
    private:
        MensajeHTTPRequest* mensajeHTTP;
        SesionesDeUsuarios* sesiones;
        Conversaciones* conversaciones;

        //string respuesta;
        RespuestaDelServicio* respuesta;
        void atenderMensajes();
};

#endif // SERVICIOMENSAJES_H
