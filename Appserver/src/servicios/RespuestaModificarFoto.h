#ifndef RESPUESTAMODIFICARFOTO_H
#define RESPUESTAMODIFICARFOTO_H

#include <RespuestaDelServicio.h>


class RespuestaModificarFoto : public RespuestaDelServicio
{
    public:
        RespuestaModificarFoto();
        virtual ~RespuestaModificarFoto();

        void setRespuestaModificacionCorrecta();
        void setRespuestaModificacionIncorrecta();
    protected:
    private:
};

#endif // RESPUESTAMODIFICARFOTO_H
