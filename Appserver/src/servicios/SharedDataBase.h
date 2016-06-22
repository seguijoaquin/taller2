#ifndef SHAREDDATABASE_H
#define SHAREDDATABASE_H

#include "ManejadorDeConexiones.h"
#include "MensajeHTTPRequest.h"
#include "MensajeHTTPReply.h"

#include "JsonObject.h"

#include "ListadoDeUsuarios.h"
#include "ListadoDeIntereses.h"

#include "Logger.h"

/** Clase que abstrae la comunicacion con el Shared Server */


class SharedDataBase
{
    public:
        /*en el listado de usuarios (/users) se devuelve solo un link a la foto del usuario, no se devuelve
        el base64 de todos los usuarios. El link en donde debe estar la foto es users/1/photo y en esa url se devuelve
        base64 de la imagen. Si uno consulta el detalle del usuario (users/1) ahí si se devuelve la imagen en base64.
        */
        SharedDataBase(ManejadorDeConexiones* conexiones, string direccion);
        virtual ~SharedDataBase();

        /** Permite dar de alta a un usuario en el Shared Server*/
        int registrarUsuario(Usuario& usuario);

        /** Devuelve los datos correspondientes a un usuario con id "idUsuario"*/
        Usuario obtenerPerfilDelUsuario(int idUsuario);
        virtual ListadoDeUsuarios obtenerListadoDeUsuarios();

        /** Elimina un usuario del Shared Server, devuelve true caso de poder realizar la baja y false sino*/
        bool eliminarUsuario(int idUsuario);

        /** Devuelve el listado completo de intereses del Shared Server*/
        ListadoDeIntereses obtenerListadoDeIntereses();

        /** Modifica la foto de perfil de un usuario, devuelve true en caso de que la modificaion y false en caso contrario*/
        bool modificarFotoPerfil(int idUsuario, string fotoBase64);

        /** Modifica el perfil de un usuario, devuelve true en caso de que la modificaion y false en caso contrario*/
        bool modificarPerfilUsuario(Usuario& usuario);

        /** Modifica la direccion del Shared Server al cual se conecta*/
        void cambiarDireccion(string nuevaDireccion);

    protected:
    private:

        string direccionShared;

        ManejadorDeConexiones* conexiones;
        MensajeHTTPRequest armarRequest(string metodo, string uri, string bodyJson);
        MensajeHTTPReply enviarHTTPRequest(string metodo, string uri, string bodyJson);

        string armarURIDeUsuario(int idUsuario);

        ListadoDeUsuarios listadoDeUsuarios;
        ListadoDeIntereses listadoDeIntereses;
};

#endif // SHAREDDATABASE_H
