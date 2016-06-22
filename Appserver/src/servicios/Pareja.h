#ifndef PAREJA_H
#define PAREJA_H

#include "StringUtil.h"
#include <iostream>
#include <map>
#include "Logger.h"

using namespace std;

/** Clase que representa una posible pareja, es decir dos usuarios
* que comparten al menos un interes.
*/

class Pareja
{
    public:
        Pareja(string usuario1, string usuario2);
        Pareja(string texto);
        virtual ~Pareja();

        /** Guarda el voto de un usuario. True significa voto a favor
        * False voto negativo.
        */
        void usuarioVota(string usuario, bool votoAFavor);

        /** Funcion que cambia el estado del voto de no notificado a no definido
        * No notificado es cuando no se le mostro el candidato.
        */
        void notificarUsuario(string usuario);

        /** Devuelve true si el estado del voto es diferente de no notificado.
        * False en otro caso
        */
        bool estaNotificado(string usuario);

        /** Devuelve true si el usuario realizo el voto. False en otro caso*/
        bool estaDefinida();

        /** Devuelve true si ambos usuarios han votado a favor es decir existe
        * un match entre ellos. False en caso de que al menos un voto este o no
        * definido o no notificado.
        */
        bool hayMatch();

        string toString();
    protected:
    private:
        map<string, int> votosDeUsuarios;
        string usuario1;
        string usuario2;
        bool existeUsuario(string usuario);
};

#endif // PAREJA_H
