#ifndef ESTADISTICASCANDIDATOS_H
#define ESTADISTICASCANDIDATOS_H

#include <string>
#include <map>
#include <set>
#include <math.h>

using namespace std;

/** Estructura que guarda las estadisticas de los usuarios */
struct Estadisticas{
    string usuario;
    int cantidadDeCandidatosPedidos;
    int cantidadDeVotosPositivos;
};

/** Clase que se encarga de la gestion de las estadisticas de los usuarios */

class EstadisticasCandidatos
{
    public:
        EstadisticasCandidatos();
        virtual ~EstadisticasCandidatos();

        /** Inicializa las estadisticas de un usuario */
        void inicializarUsuario(string usuario);

        /** Agrega uno a la cantidad de candidatos del usuario pasado como parametro
        */
        void contabilizarCandidatoPara(string usuario);

        /** Devuelve T si el usuario supero el limite de candidatos. False en
        caso contrario */
        bool usuarioSuperoLimiteDeCandidatos(string usuario);

        /** Agrega uno a la cantidad de votos del usuario pasado como parametro
        */
        void contabilizarVotoPara(string usuario);

        /** Devuelve true si el usuario es popular o false en caso contrario*/
        bool usuarioEsPopular(string usuario);

        /** limite de candidatos posibles para un usuario */
        const static int limiteCandidatos;

        /** Porcentaje de usuarios que son populares. */
        const static double porcentajeUsuariosPopulares;

    protected:
    private:
        int getCantidadVotosPara(string usuario);
        bool existeUsuario(string usuario);

        map<string,Estadisticas> estadisticasPorUsuario;
        set<string> usuariosPopulares;

        string buscarUsuarioPopularConMenosVotos();

        void actualizarUsuariosPopulares(string usuario);
};

#endif // ESTADISTICASCANDIDATOS_H
