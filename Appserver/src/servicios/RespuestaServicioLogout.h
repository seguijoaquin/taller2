#ifndef RESPUESTASERVICIOLOGOUT_H
#define RESPUESTASERVICIOLOGOUT_H

#include <RespuestaDelServicio.h>


class RespuestaServicioLogout : public RespuestaDelServicio
{
    public:
        RespuestaServicioLogout();
        virtual ~RespuestaServicioLogout();
        void setRespuestaLogoutCorrecto();
    protected:
    private:

};

#endif // RESPUESTASERVICIOLOGOUT_H
