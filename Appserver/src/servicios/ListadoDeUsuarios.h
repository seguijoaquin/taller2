#ifndef LISTADODEUSUARIOS_H
#define LISTADODEUSUARIOS_H

#include "JsonObject.h"
#include "JsonArray.h"

#include "Usuario.h"

#include <map>
#include <iostream>

class ListadoDeUsuarios
{
    public:
        ListadoDeUsuarios();
        virtual ~ListadoDeUsuarios();

        void agregarUsuarios(string jsonListadoUsuarios);

        //PRECONDICION: EL USUARIO EXISTE
        Usuario getUsuario(string usuario);

        //T si hubo siguiente usuario, F si llego al final
        bool getSiguienteUsuario(Usuario& usuario);
        void irAlInicio();
    protected:
    private:
        void agregarUsuario(string jsonUsuario);
        map<string,Usuario> usuarios;

        map<string,Usuario>::iterator itUsuarioActual;
        bool usuarioExiste(string usuario);
};

#endif // LISTADODEUSUARIOS_H
