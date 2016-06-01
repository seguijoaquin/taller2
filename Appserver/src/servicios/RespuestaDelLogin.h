#ifndef RESPUESTADELLOGIN_H
#define RESPUESTADELLOGIN_H

#include <RespuestaDelServicio.h>


class RespuestaDelLogin : public RespuestaDelServicio
{
    public:
        RespuestaDelLogin();
        virtual ~RespuestaDelLogin();

        void setRespuestaLoginCorrecto(string token);
        void setRespuestaLoginIncorrecto();

    protected:
    private:
};

#endif // RESPUESTADELLOGIN_H
