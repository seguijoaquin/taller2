#ifndef RESPUESTADELSERVICIO_H
#define RESPUESTADELSERVICIO_H

#include "MensajeHTTPReply.h"


class RespuestaDelServicio
{
    //Mas tarde hacerla clase abstracta
    public:
        RespuestaDelServicio();
        virtual ~RespuestaDelServicio();

        string toString();

    protected:
        MensajeHTTPReply respuesta;
    private:
};

#endif // RESPUESTADELSERVICIO_H
