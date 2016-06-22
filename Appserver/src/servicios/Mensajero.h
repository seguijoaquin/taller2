#ifndef MENSAJERO_H
#define MENSAJERO_H

#include "ManejadorDeConexiones.h"
#include "SesionesDeUsuarios.h"
#include "MensajeHTTPRequestGCM.h"
#include "MensajeHTTPReply.h"
//#include "json/json.h"
#include "JsonObject.h"

/** Clase encargada de el envio de mensajes tanto a los
* clientes como al shared server.
*/

class Mensajero
{
    public:
        Mensajero(ManejadorDeConexiones* conexiones, SesionesDeUsuarios* sesiones);
        virtual ~Mensajero();

        /** Envia un mensaje HTTP. Devuelve True si el status code de la
        * respuesta es 200
        */
        bool enviarMensaje(string emisor, string receptor, string mensaje);

        /** Se le envia un mensaje HTTP al usuario pasado por parametro
        * notificandole que posee un match.
        */
        bool notificarUsuarioSobreMatchCon(string usuario, string match);

    protected:
    private:
        ManejadorDeConexiones* conexiones;
        SesionesDeUsuarios* sesiones;
        bool enviarMensaje(MensajeHTTPRequestGCM& requestGCM);
        void armarBodyDelMensaje(string tokenGCM, MensajeHTTPRequestGCM& requestGCM, JsonObject& dataJson);


};

#endif // MENSAJERO_H
