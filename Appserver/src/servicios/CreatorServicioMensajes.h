#ifndef CREATORSERVICIOMENSAJES_H
#define CREATORSERVICIOMENSAJES_H

#include <CreatorServicio.h>

#include "MensajeHTTPRequest.h"
#include "SesionesDeUsuarios.h"
#include "Conversaciones.h"

#include "ServicioMensajes.h"
#include "ServicioInexistente.h"

class CreatorServicioMensajes : public CreatorServicio
{
    public:
        CreatorServicioMensajes(MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones);
        virtual ~CreatorServicioMensajes();
    protected:
    private:
};

#endif // CREATORSERVICIOMENSAJES_H
