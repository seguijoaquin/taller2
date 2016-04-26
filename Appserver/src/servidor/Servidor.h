#ifndef SERVIDOR_H
#define SERVIDOR_H

//#include "../include/mongoose.h"
//#include "../include/rocksdb/db.h"
//#include "mongoose/mongoose.h"
//#include "rocksdb/db.h"
#include "mongoose.h"
#include "db.h"
#include <iostream>
#include <fstream>
#include <map>
#include <thread>
#include "AtendedorHTTP.h"
#include "ConstantesEventosServicios.h"

#include "servicioRegistro.h"
#include "servicioLogin.h"


/*  CON ESTO ESTUVE PROBANDO SI HAY MULTITHREADING EN LAS CONEXIONES OUTBOUND
int tiempo;
*/

//const char* PATHLOGIN = "/login";
//ESTO LO VOY A TENER QUE GUARDAR EN OTRO LUGAR O LO MANEJO CON ROCKSDB
//map<string,string> listaUsuarios;


class Servidor
{
    public:
        Servidor();
        virtual ~Servidor();

        void iniciar();

        string getRespuestaDelServicio(http_message* mensajeHTTP);

    protected:
    private:
        mg_connection* conexionListening;


        rocksdb::DB* credencialesUsuarios;
        mg_mgr manager;
        map<string,string> tokensDeUsuarios;

        static void handlerServer(struct mg_connection* conexion, int evento, void* ev_data);



        void iniciarManager();
        void iniciarBaseDeDatos();
        void escucharMensajes();

};



#endif // SERVIDOR_H
