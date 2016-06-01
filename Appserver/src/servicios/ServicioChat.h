#ifndef SERVICIOCHAT_H
#define SERVICIOCHAT_H

#include "ManejadorDeConexiones.h"
#include "MensajeHTTPRequestGCM.h"
#include "SesionesDeUsuarios.h"
#include "json/json.h"
#include "json/json-forwards.h"
#include "Conversaciones.h"
#include "RespuestaDelChat.h"

class ServicioChat
{
    public:
        ServicioChat(ManejadorDeConexiones* manejadorDeConexiones, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones);
        virtual ~ServicioChat();

        //string getRespuesta();
        RespuestaDelServicio* getRespuesta();
    protected:
    private:
        ManejadorDeConexiones* manejadorDeConexiones;
        MensajeHTTPRequest* mensajeHTTP;
        SesionesDeUsuarios* sesiones;
        Conversaciones* conversaciones;

        //string respuesta;
        RespuestaDelServicio*respuesta;
        void atenderChat();
};

#endif // SERVICIOCHAT_H
