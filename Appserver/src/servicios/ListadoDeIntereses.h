#ifndef LISTADODEINTERESES_H
#define LISTADODEINTERESES_H


#include "JsonArray.h"
#include "JsonObject.h"

#include "Interes.h"
//#include <set>
#include <vector>

/** Clase que abstrae el formato con el que se guardan los intereses
* en el shared server.
*/

class ListadoDeIntereses
{
    public:
        ListadoDeIntereses();
        virtual ~ListadoDeIntereses();

        /** Agrega un interes nuevo al listado */
        void agregarIntereses(string jsonListadoIntereses);

        /** Devuelve true si el interes pertenece al listado. False si no.*/
        bool tieneInteres(Interes& interes);

        /** Devuelve la cantidad de intereses que hay en el listado. */
        int size();

        /** Devuelve el i-esimo interes del listado */
        Interes getInteres(int i);

        /** Devuelve el listado en formato de string. Se devuelve un json object
        * en formato de string
        */
        string toString();
    protected:
    private:
        void agregarInteres(string jsonInteres);
        //set<Interes> intereses;
        vector<Interes> intereses;
};

#endif // LISTADODEINTERESES_H
