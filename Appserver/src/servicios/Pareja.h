#ifndef PAREJA_H
#define PAREJA_H

#include "StringUtil.h"
#include <iostream>
#include <map>

using namespace std;

class Pareja
{
    public:
        Pareja(string usuario1, string usuario2);
        Pareja(string texto);
        virtual ~Pareja();
        void usuarioVota(string usuario, bool votoAFavor);
        void notificarUsuario(string usuario);
        bool estaNotificado(string usuario);
        bool estaDefinida();
        bool hayMatch();

        string toString();
    protected:
    private:
        map<string, int> votosDeUsuarios;
        string usuario1;
        string usuario2;
        bool existeUsuario(string usuario);
};

#endif // PAREJA_H
