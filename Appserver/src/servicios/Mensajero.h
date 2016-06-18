#ifndef MENSAJERO_H
#define MENSAJERO_H

#include "ManejadorDeConexiones.h"
#include "SesionesDeUsuarios.h"
#include "MensajeHTTPRequestGCM.h"
#include "MensajeHTTPReply.h"
//#include "json/json.h"
#include "JsonObject.h"


class Mensajero
{
    public:
        Mensajero(ManejadorDeConexiones* conexiones, SesionesDeUsuarios* sesiones);
        virtual ~Mensajero();

        bool enviarMensaje(string emisor, string receptor, string mensaje);
        bool notificarUsuarioSobreMatchCon(string usuario, string match);

    protected:
    private:
        ManejadorDeConexiones* conexiones;
        SesionesDeUsuarios* sesiones;
        bool enviarMensaje(MensajeHTTPRequestGCM& requestGCM);
        void armarBodyDelMensaje(string tokenGCM, MensajeHTTPRequestGCM& requestGCM, JsonObject& dataJson);


};

#endif // MENSAJERO_H
