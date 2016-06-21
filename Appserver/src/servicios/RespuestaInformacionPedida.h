#ifndef RESPUESTAINFORMACIONPEDIDA_H
#define RESPUESTAINFORMACIONPEDIDA_H

#include <RespuestaDelServicio.h>
#include "Usuario.h"


class RespuestaInformacionPedida : public RespuestaDelServicio
{
    public:
        RespuestaInformacionPedida();
        virtual ~RespuestaInformacionPedida();

        void setRespuestaInformacionPedida(Usuario& usuario);
    protected:
    private:
};

#endif // RESPUESTAINFORMACIONPEDIDA_H
