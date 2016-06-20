#ifndef ESTADISTICASCANDIDATOS_H
#define ESTADISTICASCANDIDATOS_H

#include <string>
#include <map>
#include <set>
#include <math.h>

using namespace std;

struct Estadisticas{
    string usuario;
    int cantidadDeCandidatosPedidos;
    int cantidadDeVotosPositivos;
};

class EstadisticasCandidatos
{
    public:
        EstadisticasCandidatos();
        virtual ~EstadisticasCandidatos();

        void inicializarUsuario(string usuario);

        void contabilizarCandidatoPara(string usuario);
        bool usuarioSuperoLimiteDeCandidatos(string usuario);

        void contabilizarVotoPara(string usuario);
        bool usuarioEsPopular(string usuario);

        const static int limiteCandidatos;
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
