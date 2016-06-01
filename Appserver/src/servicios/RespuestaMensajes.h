#ifndef RESPUESTAMENSAJES_H
#define RESPUESTAMENSAJES_H

#include <RespuestaDelServicio.h>
#include "Mensajes.h"


class RespuestaMensajes : public RespuestaDelServicio
{
    public:
        RespuestaMensajes();
        virtual ~RespuestaMensajes();

        void setMensajesComoRespuesta(Mensajes& mensajes);
    protected:
    private:
};

#endif // RESPUESTAMENSAJES_H
