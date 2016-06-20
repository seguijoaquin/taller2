#ifndef SERVICIOELIMINARUSUARIO_H
#define SERVICIOELIMINARUSUARIO_H

#include <Servicio.h>

#include "SharedDataBase.h"
#include "CredencialesDeUsuarios.h"
#include "SesionesDeUsuarios.h"
#include "RespuestaEliminacion.h"


class ServicioEliminarUsuario : public Servicio
{
    public:
        ServicioEliminarUsuario(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, CredencialesDeUsuarios* credenciales, SesionesDeUsuarios* sesiones);
        virtual ~ServicioEliminarUsuario();
    protected:
    private:
        SharedDataBase* shared;
        MensajeHTTPRequest* mensajeHTTP;
        CredencialesDeUsuarios* credenciales;
        SesionesDeUsuarios* sesiones;

        void atenderEliminacion();
};

#endif // SERVICIOELIMINARUSUARIO_H
