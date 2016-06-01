#ifndef RESPUESTADELREGISTRO_H
#define RESPUESTADELREGISTRO_H

#include <RespuestaDelServicio.h>


class RespuestaDelRegistro : public RespuestaDelServicio
{
    public:
        RespuestaDelRegistro();
        virtual ~RespuestaDelRegistro();

        void setRespuestaUsuarioExistente();
        void setRespuestaErrorDelSharedServer();
        void setRespuestaRegistroCorrecto();
    protected:
    private:
};

#endif // RESPUESTADELREGISTRO_H
