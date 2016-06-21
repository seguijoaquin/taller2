#ifndef CREATORELIMINACION_H
#define CREATORELIMINACION_H

#include <CreatorServicio.h>
#include "ServicioEliminarUsuario.h"


class CreatorEliminacion : public CreatorServicio
{
    public:
        CreatorEliminacion(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, CredencialesDeUsuarios* credenciales, SesionesDeUsuarios* sesiones);
        virtual ~CreatorEliminacion();
    protected:
    private:
};

#endif // CREATORELIMINACION_H
