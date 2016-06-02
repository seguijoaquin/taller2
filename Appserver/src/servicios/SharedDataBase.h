#ifndef SHAREDDATABASE_H
#define SHAREDDATABASE_H

#include "ManejadorDeConexiones.h"
#include "MensajeHTTPRequest.h"
#include "MensajeHTTPReply.h"

class SharedDataBase
{
    public:
        SharedDataBase(ManejadorDeConexiones* conexiones);
        virtual ~SharedDataBase();

        //DESPUES MODIFICAR LO QUE SE PASE OMO PARAMETRO PARA QUE NO SE TENGA QUE PASAR COMO JSON....
        bool registrarUsuario(string bodyJson);

    protected:
    private:
        ManejadorDeConexiones* conexiones;
};

#endif // SHAREDDATABASE_H
