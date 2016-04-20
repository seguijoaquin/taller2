#ifndef SERVIDOR_H
#define SERVIDOR_H

//#include "../include/mongoose.h"
//#include "../include/rocksdb/db.h"
#include "mongoose/mongoose.h"
#include "rocksdb/db.h"
#include <iostream>
#include <fstream>
#include <map>
#include <thread>
#include "AtendedorHTTP.h"


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
        static rocksdb::DB* credencialesUsuarios;
        static mg_mgr manager;

    protected:
    private:
        mg_connection* conexionListening;



        static void handlerServer(struct mg_connection* conexion, int evento, void* ev_data);



        void iniciarManager();
        void iniciarBaseDeDatos();
        void escucharMensajes();

};



#endif // SERVIDOR_H
