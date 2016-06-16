#ifndef RESPUESTADELABUSQUEDA_H
#define RESPUESTADELABUSQUEDA_H

#include <RespuestaDelServicio.h>

#include "Usuario.h"

class RespuestaDeLaBusqueda : public RespuestaDelServicio
{
    public:
        RespuestaDeLaBusqueda();
        virtual ~RespuestaDeLaBusqueda();

        void setRespuestaCandidatoEncontrado(Usuario* usuario);
        void setRespuestaCandidatoNoEncontrado();
    protected:
    private:
};

#endif // RESPUESTADELABUSQUEDA_H
