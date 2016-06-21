#ifndef CREATORPEDIRINTERESES_H
#define CREATORPEDIRINTERESES_H

#include <CreatorServicio.h>
#include "ServicioPedirIntereses.h"

class CreatorPedirIntereses : public CreatorServicio
{
    public:
        CreatorPedirIntereses(SharedDataBase* shared);
        virtual ~CreatorPedirIntereses();
    protected:
    private:
};

#endif // CREATORPEDIRINTERESES_H
