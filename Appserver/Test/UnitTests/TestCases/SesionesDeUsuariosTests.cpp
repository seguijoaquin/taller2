#include "SesionesDeUsuarios.h"
#include <iostream>
#include "gtest/gtest.h"
//using namespace std;

class SesionesDeUsuariosTest : public testing::Test{
	protected:
	
		virtual void SetUp(){
			this->sesiones = new SesionesDeUsuarios();
		}
		
		virtual void TearDown(){
			delete sesiones;
		}
	
		SesionesDeUsuarios* sesiones;
};



TEST_F(SesionesDeUsuariosTest, testAgregarUnaSesionDeUsuario){
	sesiones->agregarSesionDe("Usuario","Token");
	ASSERT_TRUE(sesiones->existeSesionDe("Usuario"));
}


TEST_F(SesionesDeUsuariosTest, testValidarUsuarioTokenCorrectos){
  sesiones->agregarSesionDe("Usuario","Token");
  ASSERT_TRUE(sesiones->validarTokenConUsuario("Usuario","Token"));
}
	

TEST_F(SesionesDeUsuariosTest, testValidarUsuarioTokenIncorrectos){
	
  this->sesiones->agregarSesionDe("Usuario","Token");
  ASSERT_FALSE(sesiones->validarTokenConUsuario("Usuario","JRRTolkien"));
  ASSERT_FALSE(sesiones->validarTokenConUsuario("NotUsuario","Token"));
  ASSERT_FALSE(sesiones->validarTokenConUsuario("NotUsuario","JRRTolkien"));	

}
