#ifndef SERVICIOREGISTRO_H
#define SERVICIOREGISTRO_H

//#include "mongoose.h"
#include <iostream>
#include <map>

//#include "json/json.h"
#include "JsonObject.h"
#include "JsonArray.h"

#include <fstream>
#include "MensajeHTTPRequest.h"
#include "CredencialesDeUsuarios.h"
//#include "ManejadorDeConexiones.h"
#include "RespuestaDelRegistro.h"

#include "Servicio.h"
#include "SharedDataBase.h"

//class ManejadorDeConexiones;
using namespace std;

class servicioRegistro : public Servicio
{
    public:
        //servicioRegistro(ManejadorDeConexiones* manejadorDeConexiones, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales );
        servicioRegistro(SharedDataBase* shared, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales );
        ~servicioRegistro();

        //string getRespuesta();

        //void esperarRespuesta();
        //void setCodigoResuesta(int codigo);
        //Tal vez hacer que setRespuesta desbloquee al servicio/cliente
        //void dejarDeEsperar();
    protected:
    private:
        //ManejadorDeConexiones* manejadorDeConexiones;
        SharedDataBase* shared;

        MensajeHTTPRequest mensajeHTTP;

        //string respuesta;


        //Para probrar
        int espera;

        CredencialesDeUsuarios* usuariosRegistrados;

        //int codigoRespuesta;
        //bool esperandoRespuesta;

        string crearMensajeParaAlta(string usuario);
        //void agregarInteresAlJarray(Json::Value interes, Json::Value valor, Json::Value& jarray );
        void agregarInteresAlJarray(string interes, string valor, JsonArray& jarray );
        void atenderRegistro();
        void realizarRegistro(string usuario, string password);





};

#endif // SERVICIOREGISTRO_H
