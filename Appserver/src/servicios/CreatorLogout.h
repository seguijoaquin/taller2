#ifndef CREATORLOGOUT_H
#define CREATORLOGOUT_H

#include <CreatorServicio.h>
#include "ServicioLogout.h"

class CreatorLogout : public CreatorServicio
{
    public:
        CreatorLogout(MensajeHTTPRequest* mensaje, SesionesDeUsuarios* sesiones);
        virtual ~CreatorLogout();
    protected:
    private:
};

#endif // CREATORLOGOUT_H
