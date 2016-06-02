#ifndef CREATORSERVICIO_H
#define CREATORSERVICIO_H

#include "Servicio.h"

class CreatorServicio
{
    public:
        CreatorServicio();
        virtual ~CreatorServicio();
        Servicio* getServicio();
    protected:
        Servicio* servicio;
    private:

};

#endif // CREATORSERVICIO_H
