#ifndef LISTADODEINTERESES_H
#define LISTADODEINTERESES_H


#include "JsonArray.h"
#include "JsonObject.h"

#include "Interes.h"
#include <set>

class ListadoDeIntereses
{
    public:
        ListadoDeIntereses();
        virtual ~ListadoDeIntereses();

        void agregarIntereses(string jsonListadoIntereses);
    protected:
    private:
        void agregarInteres(string jsonInteres);
        set<Interes*> intereses;
};

#endif // LISTADODEINTERESES_H
