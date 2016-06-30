#ifndef SESIONESDEUSUARIOS_H
#define SESIONESDEUSUARIOS_H

#include <map>
#include <string>
#include <iostream>
#include "Logger.h"
#include <thread>
#include <chrono>

using namespace std;



struct datosDeSesion{
    string token;
    string tokenGCM;
    int tiempoSesion;
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

        /** Se terminan las sesiones que superen SEGUNDOS_MAXIMO_SESION */
        void terminarSesionesVencidas();

    protected:
    private:
        map<string,datosDeSesion> tokensDeSesionesDeUsuario;

        static void verificarSesionesVecidas(SesionesDeUsuarios* sesiones);

        thread* resetear;
        bool activo;


};

#endif // SESIONESDEUSUARIOS_H
