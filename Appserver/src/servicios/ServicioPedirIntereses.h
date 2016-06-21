#ifndef SERVICIOPEDIRINTERESES_H
#define SERVICIOPEDIRINTERESES_H

#include <Servicio.h>
#include "SharedDataBase.h"
#include "RespuestaPedirIntereses.h"

class ServicioPedirIntereses : public Servicio
{
    public:
        ServicioPedirIntereses(SharedDataBase* shared);
        virtual ~ServicioPedirIntereses();
    protected:
    private:
};

#endif // SERVICIOPEDIRINTERESES_H
