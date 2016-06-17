#ifndef CREATORMODIFICARFOTO_H
#define CREATORMODIFICARFOTO_H

#include <CreatorServicio.h>

#include "SesionesDeUsuarios.h"
#include "ServicioModificarFoto.h"
#include "ServicioInexistente.h"
#include "CredencialesDeUsuarios.h"

class CreatorModificarFoto : public CreatorServicio
{
    public:
        CreatorModificarFoto(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, CredencialesDeUsuarios* credenciales);
        virtual ~CreatorModificarFoto();
    protected:
    private:
};

#endif // CREATORMODIFICARFOTO_H
