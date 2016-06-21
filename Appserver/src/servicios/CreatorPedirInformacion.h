#ifndef CREATORPEDIRINFORMACION_H
#define CREATORPEDIRINFORMACION_H

#include <CreatorServicio.h>
#include "ServicioPedirInformacion.h"
#include "SesionesDeUsuarios.h"

class CreatorPedirInformacion : public CreatorServicio
{
    public:
        CreatorPedirInformacion(SharedDataBase* shared, MensajeHTTPRequest* mensaje, CredencialesDeUsuarios* credenciales, SesionesDeUsuarios* sesiones);
        virtual ~CreatorPedirInformacion();
    protected:
    private:
};

#endif // CREATORPEDIRINFORMACION_H
