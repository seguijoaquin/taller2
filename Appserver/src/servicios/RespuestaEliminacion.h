#ifndef RESPUESTAELIMINACION_H
#define RESPUESTAELIMINACION_H

#include <RespuestaDelServicio.h>


class RespuestaEliminacion : public RespuestaDelServicio
{
    public:
        RespuestaEliminacion();
        virtual ~RespuestaEliminacion();
        void setRespuestaEliminacionCorrecta();
        void setRespuestaEliminacionIncorrecta();
    protected:
    private:
};

#endif // RESPUESTAELIMINACION_H
