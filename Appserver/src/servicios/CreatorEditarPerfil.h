#ifndef CREATOREDITARPERFIL_H
#define CREATOREDITARPERFIL_H

#include <CreatorServicio.h>
#include "ServicioEditarPerfil.h"
#include "SesionesDeUsuarios.h"

class CreatorEditarPerfil : public CreatorServicio
{
    public:
        CreatorEditarPerfil(SharedDataBase* shared, MensajeHTTPRequest* mensaje, SesionesDeUsuarios* sesiones, CredencialesDeUsuarios* credenciales);
        virtual ~CreatorEditarPerfil();
    protected:
    private:
};

#endif // CREATOREDITARPERFIL_H
