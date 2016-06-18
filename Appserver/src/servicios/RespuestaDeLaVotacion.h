#ifndef RESPUESTADELAVOTACION_H
#define RESPUESTADELAVOTACION_H

#include <RespuestaDelServicio.h>


class RespuestaDeLaVotacion : public RespuestaDelServicio
{
    public:
        RespuestaDeLaVotacion();
        virtual ~RespuestaDeLaVotacion();

        void setRespuestaSeRegistroVoto();
    protected:
    private:
};

#endif // RESPUESTADELAVOTACION_H
