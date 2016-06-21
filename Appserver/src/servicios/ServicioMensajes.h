#ifndef SERVICIOMENSAJES_H
#define SERVICIOMENSAJES_H

#include "MensajeHTTPRequest.h"
#include "SesionesDeUsuarios.h"
#include "Conversaciones.h"
#include "RespuestaMensajes.h"

#include "Servicio.h"

/** Clase encargada de gestionar el servicio de
 * mensajeria entre usuarios provisto por el servidor.
 * Actua ante la lleada de un mensaje http.
 */
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
