#ifndef CREDENCIALESDEUSUARIOS_H
#define CREDENCIALESDEUSUARIOS_H

#include "BaseDeDatos.h"
#include "JsonObject.h"
#include <string>

using namespace std;

    /**
     * Clase encargada de la gestion de credenciales de usuarios
     * User y password
     */

class CredencialesDeUsuarios
{
    public:
        CredencialesDeUsuarios(string ruta);
        virtual ~CredencialesDeUsuarios();

        /** Valida que el password para el usuario propuesto concuerde con el verdadero*/
        bool validarCredenciales(string usuario, string password);
    
        /** Devuelve T si se pudo agregar y F si el usuario ya existe.*/
        bool agregarNuevoUsuario(string usuario, string password, int idUsuario);
    
        /** Devuelve true si existe el usuario propuesto o false en caso contrario.*/
        bool existeUsuario(string usuario);

        /** Devuelve el id del usuario pasado por parametro */
        int getIDSharedDe(string usuario);

        /** Elimina un usuario de la base de datos */
        void eliminiarUsuario(string usuario);
    protected:
    private:

        string getPasswordDe(string usuario);
        void agregarUsuarioYCredenciales(string usuario, string password, int idUsuario);


        BaseDeDatos* credenciales;
};

#endif // CREDENCIALESDEUSUARIOS_H
