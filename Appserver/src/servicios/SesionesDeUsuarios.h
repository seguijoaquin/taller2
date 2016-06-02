#ifndef SESIONESDEUSUARIOS_H
#define SESIONESDEUSUARIOS_H

#include <map>
#include <string>
#include <iostream>

using namespace std;



struct datosDeSesion{
    string token;
    string tokenGCM;
};


class SesionesDeUsuarios
{
    public:
        SesionesDeUsuarios();
        virtual ~SesionesDeUsuarios();

        bool existeSesionDe(string usuario);
        bool validarTokenConUsuario(string usuario, string token);
        void agregarSesionDe(string usuario, string token,string tokenGCM);

        string getTokenGCMDe(string usuario);

    protected:
    private:
        map<string,datosDeSesion> tokensDeSesionesDeUsuario;


};

#endif // SESIONESDEUSUARIOS_H
