#ifndef LISTADODEUSUARIOS_H
#define LISTADODEUSUARIOS_H

#include "JsonObject.h"
#include "JsonArray.h"

#include "Usuario.h"
#include <set>

#include <iostream>

class ListadoDeUsuarios
{
    public:
        ListadoDeUsuarios();
        virtual ~ListadoDeUsuarios();

        void agregarUsuarios(string jsonListadoUsuarios);
    protected:
    private:
        void agregarUsuario(string jsonUsuario);

        set<Usuario*> usuarios;
};

#endif // LISTADODEUSUARIOS_H
