#ifndef SESIONESDEUSUARIOS_H
#define SESIONESDEUSUARIOS_H

#include <map>
#include <string>

using namespace std;


class SesionesDeUsuarios
{
    public:
        SesionesDeUsuarios();
        virtual ~SesionesDeUsuarios();

        bool existeSesionDe(string usuario);
        bool validarTokenConUsuario(string usuario, string token);
        void agregarSesionDe(string usuario, string token);

    protected:
    private:
        map<string,string> tokensDeSesionesDeUsuario;


};

#endif // SESIONESDEUSUARIOS_H
