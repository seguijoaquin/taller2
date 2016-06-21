#ifndef SERVICIOMODIFICARFOTO_H
#define SERVICIOMODIFICARFOTO_H

#include <Servicio.h>

#include "SharedDataBase.h"
#include "CredencialesDeUsuarios.h"
#include "RespuestaModificarFoto.h"

/** Servicio que gestiona la modificacion de fotos
 * de los usuarios.
 */

class ServicioModificarFoto : public Servicio
{
    public:
        ServicioModificarFoto(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, CredencialesDeUsuarios* credenciales);
        virtual ~ServicioModificarFoto();
    protected:
    private:
        SharedDataBase* shared;
        MensajeHTTPRequest* mensajeHTTP;
        CredencialesDeUsuarios* credenciales;
        void atenderModificacionFoto();
};

#endif // SERVICIOMODIFICARFOTO_H
