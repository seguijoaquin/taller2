#ifndef SERVICIOREGISTRO_H
#define SERVICIOREGISTRO_H

#include "mongoose.h"
#include <iostream>
#include <map>
#include "json/json.h"
#include <fstream>
//#include "../include/rocksdb/db.h"
//#include "rocksdb/db.h"
#include "db.h"
#include "MensajeHTTPRequest.h"

using namespace std;

class servicioRegistro
{
    public:
        //servicioRegistro(mg_mgr* manager, http_message* mensajeHTTP, rocksdb::DB* dbUsuarios );
        servicioRegistro(mg_mgr* manager, MensajeHTTPRequest mensajeHTTP, rocksdb::DB* dbUsuarios );
        ~servicioRegistro();

        string getRespuesta();
    protected:
    private:
        mg_mgr* manager;
        //http_message* mensajeHTTP;
        MensajeHTTPRequest mensajeHTTP;
        string respuesta;
        int codigoRespuesta;


        //Para probrar
        int espera;

        rocksdb::DB* dbUsuarios;

        bool bloqueado;
        string crearMensajeParaAlta(string usuario);
        void agregarInteresAlJarray(Json::Value interes, Json::Value valor, Json::Value& jarray );

        void atenderRegistro();
        void realizarRegistro(string usuario, string password);
        void setCodigoResuesta(int codigo);
        void desbloquear();

        static int tiempo; //SOLO PARA PROBAR SI ERA UNO O DOS THREADS
        static void handlerResgistro(struct mg_connection* conexion, int evento, void* ev_data);

};

#endif // SERVICIOREGISTRO_H
