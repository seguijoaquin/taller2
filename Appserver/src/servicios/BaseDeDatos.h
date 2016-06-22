#ifndef BASEDEDATOS_H
#define BASEDEDATOS_H
#include "db.h"
#include <string>
#include "Logger.h"

using namespace std;

/*!
 * Esta clase se encarga abstraer la biblioteca de bases de datos utilizada.
 */

class BaseDeDatos
{
    public:
        BaseDeDatos(string ruta);
        virtual ~BaseDeDatos();

        void put(string clave, string valor);/*!< Sirve para ingresar un dato en la base de datos*/


        string get(string clave);/*!< Sirve para obtener el valor asociado a la clave que se pasa como parametro. Si la clave no existe devuelve VALOR_DE_CLAVE_NO_ENCONTRADA*/

    bool existe(string clave);/*!< Sire para validar la existencia de una clave*/

    void eliminar(string clave);/*!< Se utiliza para eliminar un dato de la base de datos a partir de su clave asociada*/

    protected:
    private:
        rocksdb::DB* datos;
};

#endif // BASEDEDATOS_H
