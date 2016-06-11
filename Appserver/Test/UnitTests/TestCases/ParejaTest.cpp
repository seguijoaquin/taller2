#include <string>
#include <vector>
#include "Pareja.h"
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

class ParejaTest : public testing::Test{
	protected:
	    string usuario1 = "usuario1";
	    string usuario2 = "usuario2";
};




TEST_F(ParejaTest, testCuandoSeCreanLasParejasNingunoDeLosUsuariosEstaNotificado){
    Pareja pareja(usuario1, usuario2);

    ASSERT_FALSE( pareja.estaNotificado(usuario1) );
    ASSERT_FALSE( pareja.estaNotificado(usuario2) );
}


TEST_F(ParejaTest, testCuandoSeCreaUnaParejaNoEstaDefinida){
    Pareja pareja(usuario1, usuario2);

    ASSERT_FALSE( pareja.estaDefinida() );
}

TEST_F(ParejaTest, testCuandoSeCreaUnaParejaNoHayMatch){
    Pareja pareja(usuario1, usuario2);

    ASSERT_FALSE( pareja.hayMatch() );
}


TEST_F(ParejaTest, testSeNotificaAUnUsuarioSobreLaPareja){
    Pareja pareja(usuario1, usuario2);
    pareja.notificarUsuario(usuario1);
    ASSERT_TRUE( pareja.estaNotificado(usuario1) );
}

TEST_F(ParejaTest, testElVotoEnContraDeUnUsuarioDefineLaParejaComoSinMatch){
    Pareja pareja(usuario1, usuario2);
    pareja.usuarioVota(usuario1,false);
    ASSERT_TRUE( pareja.estaDefinida() );
    ASSERT_FALSE( pareja.hayMatch() );
}

TEST_F(ParejaTest, testElVotoAFavorDeAmbosUsuariosDefineLaParejaComoMatc){
    Pareja pareja(usuario1, usuario2);
    pareja.usuarioVota(usuario1,true);
    pareja.usuarioVota(usuario2,true);
    ASSERT_TRUE( pareja.estaDefinida() );
    ASSERT_TRUE(pareja.hayMatch() );
}






