#ifndef USUARIO_H
#define USUARIO_H

#include "JsonObject.h"
#include "ListadoDeIntereses.h"
#include "Localizacion.h"


using namespace std;

/** Clase que contiene informacion pertinente acerca
 * de los usuarios del sistema
 */

class Usuario
{
    public:
        Usuario();
        Usuario(string jsonUsuario);
        virtual ~Usuario();

        /** Devuelve el email del usuario*/
        string getEmail();

        /**Devuelve el id del usuario*/
        int getId();

        /**Devuelve el nombre del usuario*/
        string getNombre();

        /** Devuelve toda la informacion almacenada en formato
         * de string
         */
        string toString();

        /** Devuelve el listado de intereses del usuario*/
        ListadoDeIntereses getIntereses();

        /** Devuelve la localizacion actual del usuario. */
        Localizacion getLocalizacion();

        /** Actualiza la ultima localizacion subida por la actual.*/
        void actualizarLocalizacion(Localizacion& localizacion);

    protected:
    private:
        JsonObject perfil;
        string email;
};

#endif // USUARIO_H
