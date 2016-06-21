#ifndef INTERES_H
#define INTERES_H

#include "JsonObject.h"

/** Clase que gestiona el almacenamiento y operaciones logicas correspondientes
* a los intereses.
*/
class Interes
{
    public:
        Interes(string jsonInteres);
        virtual ~Interes();

        /** Devuelve la categoria a la que pertenece el interes */
        string getCategoria();

        /** Devuelve el valor del interes, por ejemplo el nombre de una banda
        * musical
        */
        string getValor();

        /** Devuelve True si el interes pasado como parametro es igual al que
        * llama al metodo y false en caso contrario. Se considera que son iguales
        si tanto sus categorias como valores coinciden */
        bool comparar(Interes& interes);

        /** Devuelve la informacion que guarda en formato de json object.
        * La informacion guardada es categoria y valor.
        */
        JsonObject toJsonObject();

    protected:
    private:
        string categoria;
        string valor;
};

#endif // INTERES_H
