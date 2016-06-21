#ifndef SERVICIOPEDIRINFORMACION_H
#define SERVICIOPEDIRINFORMACION_H

#include <Servicio.h>

#include "SharedDataBase.h"
#include "MensajeHTTPRequest.h"
#include "CredencialesDeUsuarios.h"
#include "RespuestaInformacionPedida.h"

class ServicioPedirInformacion : public Servicio
{
    public:
        ServicioPedirInformacion(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, CredencialesDeUsuarios* credenciales);
        virtual ~ServicioPedirInformacion();
    protected:
    private:
        SharedDataBase* shared;
        MensajeHTTPRequest* mensajeHTTP;
        CredencialesDeUsuarios* credenciales;

        void atenderPedidoDeInformacion();
};

#endif // SERVICIOPEDIRINFORMACION_H
