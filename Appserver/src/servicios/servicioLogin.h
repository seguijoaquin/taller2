#ifndef SERVICIOLOGIN_H
#define SERVICIOLOGIN_H
#include "mongoose.h"
#include <iostream>
#include <map>
//#include "../include/rocksdb/db.h"
//#include "rocksdb/db.h"
#include "MensajeHTTPRequest.h"
#include "SesionesDeUsuarios.h"
#include "CredencialesDeUsuarios.h"


using namespace std;

class servicioLogin
{
    public:
        //servicioLogin(http_message* mensajeHTTP, rocksdb::DB* dbUsuarios, map<string,string>* tokensDeUsuarios);
        //servicioLogin(MensajeHTTPRequest mensajeHTTP, rocksdb::DB* dbUsuarios, map<string,string>* tokensDeUsuarios);
        //servicioLogin(MensajeHTTPRequest mensajeHTTP, rocksdb::DB* dbUsuarios, SesionesDeUsuarios* sesionesDeUsuarios);
        servicioLogin(SesionesDeUsuarios* sesionesDeUsuarios, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales);
        virtual ~servicioLogin();

        string getRespuesta();
    protected:
    private:
        //http_message* mensajeHTTP;
        MensajeHTTPRequest mensajeHTTP;
        string respuesta;
        //rocksdb::DB* dbUsuarios;
        CredencialesDeUsuarios* credenciales;

        //map<string,string>* tokensDeUsuarios;
        SesionesDeUsuarios* sesionesDeUsuarios;

        bool usuarioExiste();
        void realizarLogin();
        string generarToken();

        void atenderLogin();
};

#endif // SERVICIOLOGIN_H
