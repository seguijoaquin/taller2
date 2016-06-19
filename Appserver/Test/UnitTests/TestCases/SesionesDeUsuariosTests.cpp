#include "SesionesDeUsuarios.h"
#include <iostream>
#include "gtest/gtest.h"
using namespace std;

class SesionesDeUsuariosTest : public testing::Test{
	protected:

		virtual void SetUp(){
			this->sesiones = new SesionesDeUsuarios();
		}

		virtual void TearDown(){
			delete sesiones;
		}

		SesionesDeUsuarios* sesiones;

		void agregarSesion(SesionesDeUsuarios* sesiones, string usuario, string token){
		    string tokenGCM = "TokenGCM";
            sesiones->agregarSesionDe(usuario,token, tokenGCM);
		}
};



TEST_F(SesionesDeUsuariosTest, testAgregarUnaSesionDeUsuario){
	this->agregarSesion(sesiones,"Usuario","Token");
	ASSERT_TRUE(sesiones->existeSesionDe("Usuario"));
}


TEST_F(SesionesDeUsuariosTest, testValidarUsuarioTokenCorrectos){
    this->agregarSesion(sesiones,"Usuario","Token");
    ASSERT_TRUE(sesiones->validarTokenConUsuario("Usuario","Token"));
}


TEST_F(SesionesDeUsuariosTest, testValidarUsuarioTokenIncorrectos){
    this->agregarSesion(sesiones,"Usuario","Token");
    ASSERT_FALSE(sesiones->validarTokenConUsuario("Usuario","JRRTolkien"));
    ASSERT_FALSE(sesiones->validarTokenConUsuario("NotUsuario","Token"));
    ASSERT_FALSE(sesiones->validarTokenConUsuario("NotUsuario","JRRTolkien"));
}

