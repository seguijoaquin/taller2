#ifndef RESPUESTADELCHAT_H
#define RESPUESTADELCHAT_H

#include <RespuestaDelServicio.h>


class RespuestaDelChat : public RespuestaDelServicio
{
    public:
        RespuestaDelChat();
        virtual ~RespuestaDelChat();

        void setRespuestaGCM(MensajeHTTPReply GCMreply);

        /*this->respuesta.setCodigo(503);
        this->respuesta.setMensajeDeEstado("Error del server");
        */

    protected:
    private:
};

#endif // RESPUESTADELCHAT_H
