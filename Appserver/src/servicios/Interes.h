#ifndef INTERES_H
#define INTERES_H

#include "JsonObject.h"


class Interes
{
    public:
        Interes(string jsonInteres);
        virtual ~Interes();
    protected:
    private:
        string categoria;
        string valor;
};

#endif // INTERES_H