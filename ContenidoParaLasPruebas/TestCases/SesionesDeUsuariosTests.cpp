#include "SesionesDeUsuariosTests.h"

//using namespace std;

// Agrega la TestFixture (HttpMessageRequestTest) al registro
CPPUNIT_TEST_SUITE_REGISTRATION( SesionesDeUsuariosTest );


SesionesDeUsuariosTest::SesionesDeUsuariosTest(){

}
SesionesDeUsuariosTest::~SesionesDeUsuariosTest(){

}
void SesionesDeUsuariosTest::setUp(){
  cout<<"Set up \n";
  this->sesiones = new SesionesDeUsuarios();
}
void SesionesDeUsuariosTest::tearDown(){
  cout<<"Tear down \n";
  delete this->sesiones;
}

void SesionesDeUsuariosTest::testAgregarUnaSesionDeUsuario(){
  this->sesiones->agregarSesionDe("Usuario","Token");
  CPPUNIT_ASSERT(this->sesiones->existeSesionDe("Usuario"));
}

void SesionesDeUsuariosTest::testValidarUsuarioTokenCorrectos(){
  this->sesiones->agregarSesionDe("Usuario","Token");
  CPPUNIT_ASSERT(this->sesiones->validarTokenConUsuario("Usuario","Token"));
}

void SesionesDeUsuariosTest::testValidarUsuarioTokenIncorrectos(){
  this->sesiones->agregarSesionDe("Usuario","Token");
  CPPUNIT_ASSERT_FALSE(this->sesiones->validarTokenConUsuario("Usuario","JRRTolkien"));
  CPPUNIT_ASSERT_FALSE(this->sesiones->validarTokenConUsuario("NotUsuario","Token"));
  CPPUNIT_ASSERT_FALSE(this->sesiones->validarTokenConUsuario("NotUsuario","JRRTolkien"));
}
