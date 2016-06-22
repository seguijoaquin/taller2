#ifndef LISTADODEUSUARIOS_H
#define LISTADODEUSUARIOS_H

#include "JsonObject.h"
#include "JsonArray.h"

#include "Usuario.h"

#include <map>
#include <iostream>

/** Clase que abstrae el formato con el que se guarda el listado de usuarios
* en el shared server.
*/

class ListadoDeUsuarios
{
    public:
        ListadoDeUsuarios();
        virtual ~ListadoDeUsuarios();

        /** Agrega un usuario al sistema */
        void agregarUsuarios(string jsonListadoUsuarios);

        //PRECONDICION: EL USUARIO EXISTE
        /** Devuelve una clase Usuario con los datos completos para un usuario
        * determinado. El usuario debe existir.
        */
        Usuario getUsuario(string usuario);

        /** Devuelve True si hubo siguiente usuario, False si llego al final. En
        * caso de devolver True el usuario pasado por parametro contiene
        * los datos del siguiente usuario. */
        bool getSiguienteUsuario(Usuario& usuario);

        /** Posiciona el iterador en el comienzo del listado*/
        void irAlInicio();
    protected:
    private:
        void agregarUsuario(string jsonUsuario);
        map<string,Usuario> usuarios;

        map<string,Usuario>::iterator itUsuarioActual;
        bool usuarioExiste(string usuario);
};

#endif // LISTADODEUSUARIOS_H
