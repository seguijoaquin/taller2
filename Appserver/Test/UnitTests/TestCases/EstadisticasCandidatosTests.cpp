#include <string>
#include <vector>
#include "EstadisticasCandidatos.h"
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

class EstadisticasCandidatosTest : public testing::Test{
	protected:

		virtual void SetUp(){

		}

		virtual void TearDown(){

		}

        void inicializarUsuarios(EstadisticasCandidatos& estadisticas, int cantidadDeUsuarios){
            for (int i=1; i <= cantidadDeUsuarios; i++){
                estadisticas.inicializarUsuario(to_string(i));
            }
        }

        void votarPorUsuario(EstadisticasCandidatos& estadisticas, string usuarioAVotar, int cantidadDeVotos){
            for (int i=1; i <= cantidadDeVotos; i++){
                estadisticas.contabilizarVotoPara(usuarioAVotar);
            }
        }

        void darCandidatosAUsuario(EstadisticasCandidatos& estadisticas, string usuario, int cantidadDeCandidatos){
            for (int i=1; i <=cantidadDeCandidatos; i++){
                estadisticas.contabilizarCandidatoPara(usuario);
            }
        }

        void superarLimiteDeCandidatos(EstadisticasCandidatos& estadisticas, string usuario){
            this->darCandidatosAUsuario(estadisticas,usuario,EstadisticasCandidatos::limiteCandidatos + 1 );
        }


};

TEST_F(EstadisticasCandidatosTest, testSaberSiUnUsuarioEsPopular){
    EstadisticasCandidatos estadisticas;
    this->inicializarUsuarios(estadisticas,1000);
    string usuarioPopular = "200";
    this->votarPorUsuario(estadisticas,usuarioPopular,500);
    ASSERT_TRUE(estadisticas.usuarioEsPopular(usuarioPopular));
}

TEST_F(EstadisticasCandidatosTest, testContabilizarLosCandidatosParaUnUsuarioYSaberSiSuperoElLimiteDeCandidatos){
    EstadisticasCandidatos estadisticas;
    string usuario = "usuario";
    estadisticas.inicializarUsuario(usuario);
    this->superarLimiteDeCandidatos(estadisticas,usuario);
    ASSERT_TRUE(estadisticas.usuarioSuperoLimiteDeCandidatos(usuario));
}


TEST_F(EstadisticasCandidatosTest, testInicializarUnUsuarioYaInicializadoNoReseteaSusEstadisticas){
    EstadisticasCandidatos estadisticas;
    int cantidadUsuarios = 1000;
    this->inicializarUsuarios(estadisticas,cantidadUsuarios);
    //Le doy 100 votos a todos
    for (int i = 1; i <= cantidadUsuarios; i++){
        this->votarPorUsuario(estadisticas,to_string(i),100);
    }
    //A "200" le doy 100 votos mas para hacerlo popular
    string usuarioAResetear = "200";
    this->votarPorUsuario(estadisticas,usuarioAResetear,100);
    this->superarLimiteDeCandidatos(estadisticas,usuarioAResetear);

    ASSERT_TRUE(estadisticas.usuarioEsPopular(usuarioAResetear));
    ASSERT_TRUE(estadisticas.usuarioSuperoLimiteDeCandidatos(usuarioAResetear));

    //"200" sigue siendo popular y con el limite superado
    estadisticas.inicializarUsuario(usuarioAResetear);
    ASSERT_TRUE(estadisticas.usuarioEsPopular(usuarioAResetear));
    ASSERT_TRUE(estadisticas.usuarioSuperoLimiteDeCandidatos(usuarioAResetear));
}



TEST_F(EstadisticasCandidatosTest, testSiSeVotaPorUnUsuarioNoInicializadoNoSeCuentanSusVotos){
    EstadisticasCandidatos estadisticas;

    int cantidadUsuarios = 1000;
    this->inicializarUsuarios(estadisticas,cantidadUsuarios);

    //El usuario "1100" no esta inicializado
    string usuarioNoInicializado = to_string(cantidadUsuarios + 100);
    //Voto varias veces por "1100", deberia ser popular
    this->votarPorUsuario(estadisticas,usuarioNoInicializado,1000);
    //No es popular
    ASSERT_FALSE(estadisticas.usuarioEsPopular(usuarioNoInicializado));
}

TEST_F(EstadisticasCandidatosTest, testSiSeDaUnCandidatoAUnUsuarioNoInicializadoNoSeCuentanSusCandidatos){
    EstadisticasCandidatos estadisticas;
    string usuarioNoInicializado = "usuario";
    this->superarLimiteDeCandidatos(estadisticas,usuarioNoInicializado);
    //A pesar de que supera el limite de candidatos, no se cuenta
    ASSERT_FALSE(estadisticas.usuarioSuperoLimiteDeCandidatos(usuarioNoInicializado));
}

