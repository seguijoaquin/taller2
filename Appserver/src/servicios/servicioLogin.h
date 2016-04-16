#ifndef SERVICIOLOGIN_H
#define SERVICIOLOGIN_H
#include "mongoose.h"
#include <iostream>
#include <map>

using namespace std;

class servicioLogin
{
    public:
        servicioLogin(http_message* mensajeHTTP, map<string,string>* listaUsuarios);
        virtual ~servicioLogin();

        string getRespuesta();
    protected:
    private:
        http_message* mensajeHTTP;
        string respuesta;
        map<string,string>* listaUsuarios;
        bool usuarioExiste();
        void realizarLogin();
        string generarToken();

        void atenderLogin();
};

#endif // SERVICIOLOGIN_H
