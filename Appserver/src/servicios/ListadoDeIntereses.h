#ifndef LISTADODEINTERESES_H
#define LISTADODEINTERESES_H


#include "JsonArray.h"
#include "JsonObject.h"

#include "Interes.h"
//#include <set>
#include <vector>

class ListadoDeIntereses
{
    public:
        ListadoDeIntereses();
        virtual ~ListadoDeIntereses();

        void agregarIntereses(string jsonListadoIntereses);
        bool tieneInteres(Interes& interes);

        int size();
        Interes getInteres(int i);
        string toString();
    protected:
    private:
        void agregarInteres(string jsonInteres);
        //set<Interes> intereses;
        vector<Interes> intereses;
};

#endif // LISTADODEINTERESES_H
