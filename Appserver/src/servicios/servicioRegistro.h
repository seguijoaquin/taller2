#ifndef SERVICIOREGISTRO_H
#define SERVICIOREGISTRO_H

#include "mongoose.h"
#include <iostream>
#include <map>
#include "json/json.h"
#include <fstream>

using namespace std;

class servicioRegistro
{
    public:
        servicioRegistro(mg_mgr* manager, http_message* mensajeHTTP, map<string,string>* listaUsuarios );
        ~servicioRegistro();

        string getRespuesta();
    protected:
    private:
        mg_mgr* manager;
        http_message* mensajeHTTP;
        string respuesta;
        int codigoRespuesta;


        //Para probrar
        int espera;


        map<string,string>* listaUsuarios;
        bool bloqueado;
        string crearMensajeParaAlta(string usuario);
        void agregarInteresAlJarray(Json::Value interes, Json::Value valor, Json::Value& jarray );

        void atenderRegistro();
        void realizarRegistro(string usuario, string password);
        void desbloquear(int codigoRespuesta);

        //Refactorizar: *idea* si pongo a todos los atendedores que hereden del mismo atenderdor esto podria llamarse "handlerCliente" y que cada uno lo redefna
        //RTA: no necesariamente, puede que algunos como el GET no lo necesiten
        static int tiempo; //SOLO PARA PROBAR SI ERA UNO O DOS THREADS
        static void handlerResgistro(struct mg_connection* conexion, int evento, void* ev_data);
        //mg_event_handler_t handlerResgistro(struct mg_connection* conexion, int evento, void* ev_data);

};

#endif // SERVICIOREGISTRO_H
