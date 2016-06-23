#ifndef SESIONESDEUSUARIOS_H
#define SESIONESDEUSUARIOS_H

#include <map>
#include <string>
#include <iostream>
#include "Logger.h"

using namespace std;



struct datosDeSesion{
    string token;
    string tokenGCM;
};


/**
 * Clase encargada de la gestion de las sesiones de usuarios
 */


class SesionesDeUsuarios
{
    public:
        SesionesDeUsuarios();
        virtual ~SesionesDeUsuarios();

        /** Funcion que devuelve verdadero si existe una sesion de usuario para el propuesto*/
        bool existeSesionDe(string usuario);

        /** Funcion que devuelve verdadero si el token pertenece al usuario propuesto */
        bool validarTokenConUsuario(string usuario, string token);

        /** Inicia la sesion del usuario con el token del Appserver y el token de Google Cloud Messagin asignados*/
        void agregarSesionDe(string usuario, string token,string tokenGCM);

        /**  */
        string getTokenGCMDe(string usuario);

        /** Elimina completamente al usuario de la lista de sesiones*/
        void eliminarUsuario(string usuario);

        /** Anula el token del usuario pero guarda el resto de sus datos*/
        void terminarSesionDe(string usuario);

    protected:
    private:
        map<string,datosDeSesion> tokensDeSesionesDeUsuario;


};

#endif // SESIONESDEUSUARIOS_H
