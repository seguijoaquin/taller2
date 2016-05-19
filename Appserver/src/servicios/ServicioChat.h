#ifndef SERVICIOCHAT_H
#define SERVICIOCHAT_H

#include "ManejadorDeConexiones.h"
#include "MensajeHTTPRequestGCM.h"
#include "SesionesDeUsuarios.h"
#include "json/json.h"
#include "json/json-forwards.h"

class ServicioChat
{
    public:
        ServicioChat(ManejadorDeConexiones* manejadorDeConexiones, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones);
        virtual ~ServicioChat();

        string getRespuesta();
    protected:
    private:
        ManejadorDeConexiones* manejadorDeConexiones;
        MensajeHTTPRequest* mensajeHTTP;
        SesionesDeUsuarios* sesiones;

        string respuesta;
        void atenderChat();
};

#endif // SERVICIOCHAT_H