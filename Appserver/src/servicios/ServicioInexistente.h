#ifndef SERVICIOINEXISTENTE_H
#define SERVICIOINEXISTENTE_H

#include "Servicio.h"
#include "RespuestaServicioInexistente.h"


class ServicioInexistente : public Servicio
{
    public:
        ServicioInexistente();
        virtual ~ServicioInexistente();
        void setRespuestaTokenInvalido();
    protected:
    private:
};

#endif // SERVICIOINEXISTENTE_H
