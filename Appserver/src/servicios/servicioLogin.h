#ifndef SERVICIOLOGIN_H
#define SERVICIOLOGIN_H
#include "mongoose.h"
#include <iostream>
#include <map>
//#include "../include/rocksdb/db.h"
#include "rocksdb/db.h"

using namespace std;

class servicioLogin
{
    public:
        //servicioLogin(http_message* mensajeHTTP, map<string,string>* listaUsuarios);
        servicioLogin(http_message* mensajeHTTP, rocksdb::DB* dbUsuarios );
        virtual ~servicioLogin();

        string getRespuesta();
    protected:
    private:
        http_message* mensajeHTTP;
        string respuesta;
        //map<string,string>* listaUsuarios;
        rocksdb::DB* dbUsuarios;

        bool usuarioExiste();
        void realizarLogin();
        string generarToken();

        void atenderLogin();
};

#endif // SERVICIOLOGIN_H
