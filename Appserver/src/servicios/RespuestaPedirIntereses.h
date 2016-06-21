#ifndef RESPUESTAPEDIRINTERESES_H
#define RESPUESTAPEDIRINTERESES_H

#include <RespuestaDelServicio.h>
#include "ListadoDeIntereses.h"

class RespuestaPedirIntereses : public RespuestaDelServicio
{
    public:
        RespuestaPedirIntereses();
        virtual ~RespuestaPedirIntereses();
        void setRespuestaInteresesPedidos(ListadoDeIntereses& iteresesPedidos);
    protected:
    private:
};

#endif // RESPUESTAPEDIRINTERESES_H
