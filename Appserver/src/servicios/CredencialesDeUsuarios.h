#ifndef CREDENCIALESDEUSUARIOS_H
#define CREDENCIALESDEUSUARIOS_H

#include "db.h"
#include <string>

using namespace std;

class CredencialesDeUsuarios
{
    public:
        CredencialesDeUsuarios(string ruta);
        virtual ~CredencialesDeUsuarios();

        bool validarCredenciales(string usuario, string password);
        //Devuelve T si se pudo agregar y F si el usuario ya existe.
        bool agregarNuevoUsuario(string usuario, string password);

        bool existeUsuario(string usuario);
    protected:
    private:


        rocksdb::DB* credenciales;
};

#endif // CREDENCIALESDEUSUARIOS_H
