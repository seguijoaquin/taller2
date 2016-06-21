#ifndef CREATORSERVICIO_H
#define CREATORSERVICIO_H

#include "Servicio.h"
#include "ServicioInexistente.h"

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
