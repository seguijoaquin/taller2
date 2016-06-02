#ifndef SERVICIOCHAT_H
#define SERVICIOCHAT_H

#include "ManejadorDeConexiones.h"
#include "MensajeHTTPRequestGCM.h"
#include "SesionesDeUsuarios.h"
#include "Conversaciones.h"
#include "RespuestaDelChat.h"
#include "Servicio.h"

class ServicioChat : public Servicio
{
    public:
        ServicioChat(ManejadorDeConexiones* manejadorDeConexiones, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones);
        virtual ~ServicioChat();

        //string getRespuesta();
    protected:
    private:
        ManejadorDeConexiones* manejadorDeConexiones;
        MensajeHTTPRequest* mensajeHTTP;
        SesionesDeUsuarios* sesiones;
        Conversaciones* conversaciones;

        //string respuesta;

        void atenderChat();
};

#endif // SERVICIOCHAT_H
