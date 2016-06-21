#ifndef RESPUESTAACTUALIZARPOSICION_H
#define RESPUESTAACTUALIZARPOSICION_H

#include <RespuestaDelServicio.h>


class RespuestaActualizarPosicion : public RespuestaDelServicio
{
    public:
        RespuestaActualizarPosicion();
        virtual ~RespuestaActualizarPosicion();

        void setRespuestaActualizacionCorrecta();
        void setRespuestaActualizacionIncorrecta();
    protected:
    private:
};

#endif // RESPUESTAACTUALIZARPOSICION_H
