#ifndef SHAREDDATABASE_H
#define SHAREDDATABASE_H

#include "ManejadorDeConexiones.h"
#include "MensajeHTTPRequest.h"
#include "MensajeHTTPReply.h"

#include "JsonObject.h"

class SharedDataBase
{
    public:
        /*en el listado de usuarios (/users) se devuelve solo un link a la foto del usuario, no se devuelve
        el base64 de todos los usuarios. El link en donde debe estar la foto es users/1/photo y en esa url se devuelve
        base64 de la imagen. Si uno consulta el detalle del usuario (users/1) ahí si se devuelve la imagen en base64.
        */

        SharedDataBase(ManejadorDeConexiones* conexiones);
        virtual ~SharedDataBase();

        //DESPUES MODIFICAR LO QUE SE PASE OMO PARAMETRO PARA QUE NO SE TENGA QUE PASAR COMO JSON....
        //QUE SE PASE UN PerfilUsuario&
        //bool registrarUsuar(string bodyJson);

        int registrarUsuario(string bodyJson);
        string obtenerPerfilDelUsuario(int idUsuario);
        string obtenerListadoDeUsuarios();
        bool eliminarUsuario(int idUsuario);

    protected:
    private:
        ManejadorDeConexiones* conexiones;
        MensajeHTTPRequest armarRequest(string metodo, string uri, string bodyJson);
        MensajeHTTPReply enviarHTTPRequest(MensajeHTTPRequest& request);
        string armarURIDeUsuario(int idUsuario);
};

#endif // SHAREDDATABASE_H
