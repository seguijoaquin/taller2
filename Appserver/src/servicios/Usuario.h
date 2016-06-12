#ifndef USUARIO_H
#define USUARIO_H

#include "JsonObject.h"
#include <stack>

using namespace std;

class Usuario
{
    public:
        Usuario(string jsonUsuario);
        virtual ~Usuario();

        string getEmail();
        string getId();

        bool tieneInteres(string interes);
        void agregarPosibleMatch(Usuario* usuario);
        Usuario* getPosibleMatch();


        string toString();
    protected:
    private:
        JsonObject perfil;
        stack<Usuario*> posiblesMatches;


};

#endif // USUARIO_H
