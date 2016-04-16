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

        map<string,string>* listaUsuarios;
        bool bloqueado;
        string crearMensajeParaAlta(string usuario);
        void agregarInteresAlJarray(Json::Value interes, Json::Value valor, Json::Value& jarray );

        void atenderRegistro();
        void realizarRegistro(string usuario, string password);
        void desbloquear(int codigoRespuesta);

        static void handlerResgistro(struct mg_connection* conexion, int evento, void* ev_data);

};

#endif // SERVICIOREGISTRO_H
