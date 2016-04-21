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

        //Las tengo que hacer staticas para poder pasarlas al AtendedorHTTP en el handler....
        /*La otra seria poner las credenciales como user data del manager, despues en el ev handler, de la conexion sacar el manager
          y del manager sacar las credenciales....
        */
        //http://stackoverflow.com/questions/27221020/cast-error-passing-a-void-function-with-namespace

        string getRespuestaDelServicio(http_message* mensajeHTTP);

    protected:
    private:
        mg_connection* conexionListening;


        rocksdb::DB* credencialesUsuarios;
        mg_mgr manager;
        static void handlerServer(struct mg_connection* conexion, int evento, void* ev_data);



        void iniciarManager();
        void iniciarBaseDeDatos();
        void escucharMensajes();

};



#endif // SERVIDOR_H
