#ifndef SERVICIOREGISTRO_H
#define SERVICIOREGISTRO_H

//#include "mongoose.h"
#include <iostream>
#include <map>
#include "json/json.h"
#include <fstream>
#include "MensajeHTTPRequest.h"
#include "CredencialesDeUsuarios.h"
#include "ManejadorDeConexiones.h"

class ManejadorDeConexiones;
using namespace std;

class servicioRegistro
{
    public:
        //servicioRegistro(mg_mgr* manager, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales );
        servicioRegistro(ManejadorDeConexiones* manejadorDeConexiones, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales );
        ~servicioRegistro();

        string getRespuesta();
        void esperarRespuesta();
        void setCodigoResuesta(int codigo);
        void desbloquear();
    protected:
    private:
        //mg_mgr* manager;
        ManejadorDeConexiones* manejadorDeConexiones;
        //static int tiempo; //SOLO PARA PROBAR SI ERA UNO O DOS THREADS
        //static void handlerResgistro(struct mg_connection* conexion, int evento, void* ev_data);


        MensajeHTTPRequest mensajeHTTP;

        string respuesta;
        int codigoRespuesta;


        //Para probrar
        int espera;

        CredencialesDeUsuarios* usuariosRegistrados;

        bool esperandoRespuesta;
        string crearMensajeParaAlta(string usuario);
        void agregarInteresAlJarray(Json::Value interes, Json::Value valor, Json::Value& jarray );

        void atenderRegistro();
        void realizarRegistro(string usuario, string password);





};

#endif // SERVICIOREGISTRO_H
