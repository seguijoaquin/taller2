#ifndef SERVICIO_H
#define SERVICIO_H

#include "RespuestaDelServicio.h"

/** Clase de la que heredan los servicios
 * que brinda el servidor
 */

class Servicio
{
    public:
        Servicio();
        virtual ~Servicio();
    
        /** Devuelve la respuesta, esta es seteada en las clases que
         * heredan de esta.
         */
        RespuestaDelServicio* getRespuesta();
    protected:
        RespuestaDelServicio*respuesta;
    private:

};

#endif // SERVICIO_H
