#ifndef RESPUESTADELSERVICIO_H
#define RESPUESTADELSERVICIO_H

#include "MensajeHTTPReply.h"

/** Clase que abstrae el formato interno de respuestas que generan
* los distintos servicios al procesar una peticion
*/

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
