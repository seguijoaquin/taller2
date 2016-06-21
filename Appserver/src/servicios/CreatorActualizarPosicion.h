#ifndef CREATORACTUALIZARPOSICION_H
#define CREATORACTUALIZARPOSICION_H

#include <CreatorServicio.h>
#include "ServicioActualizarPosicion.h"
#include "SesionesDeUsuarios.h"

class CreatorActualizarPosicion : public CreatorServicio
{
    public:
        CreatorActualizarPosicion(SharedDataBase* shared, MensajeHTTPRequest* mensaje, SesionesDeUsuarios* sesiones, CredencialesDeUsuarios* credenciales);
        virtual ~CreatorActualizarPosicion();
    protected:
    private:
};

#endif // CREATORACTUALIZARPOSICION_H
