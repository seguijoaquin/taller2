#ifndef RESPUESTASERVICIOINEXISTENTE_H
#define RESPUESTASERVICIOINEXISTENTE_H

#include <RespuestaDelServicio.h>


class RespuestaServicioInexistente : public RespuestaDelServicio
{
    public:
        RespuestaServicioInexistente();
        virtual ~RespuestaServicioInexistente();

        void setRespuestaTokenInvalido();
    protected:
    private:
};

#endif // RESPUESTASERVICIOINEXISTENTE_H
