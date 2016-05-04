#ifndef BASEDEDATOS_H
#define BASEDEDATOS_H
#include "db.h"
#include <string>

using namespace std;

class BaseDeDatos
{
    public:
        BaseDeDatos(string ruta);
        virtual ~BaseDeDatos();

        void put(string clave, string valor);
        //Si la clave no existe devuelve VALOR_DE_CLAVE_NO_ENCONTRADA,;
        string get(string clave);
        bool existe(string clave);
    protected:
    private:
        rocksdb::DB* datos;
};

#endif // BASEDEDATOS_H
