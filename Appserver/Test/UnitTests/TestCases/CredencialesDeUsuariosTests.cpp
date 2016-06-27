#include "gtest/gtest.h"
#include "CredencialesDeUsuarios.h"
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "servicioRegistro.h"

using namespace std;


class CredencialesDeUsuariosTest : public testing::Test {

 protected:  // You should make the members protected s.t. they can be
             // accessed from sub-classes.

  // virtual void SetUp() will be called before each test is run.  You
  // should define it if you need to initialize the varaibles.
  // Otherwise, this can be skipped.

  virtual void SetUp() {
	cout<<"Se van a creear credenciales\n";
	credenciales = new CredencialesDeUsuarios("./Entorno/CredencialesDePrueba");
	cout<<"Se crearon credenciales\n";
	password = "password";
	passwordIncorrecto = "passwordIncorrecto";
	usuario = "NUEVO_USUARIO";
  }



  // virtual void TearDown() will be called after each test is run.
  // You should define it if there is cleanup work to do.  Otherwise,
  // you don't have to provide it.
  //
  virtual void TearDown() {
	cout<<"Se deletea credenciales\n";
	delete credenciales;
	cout<<"Se limpia el entorno\n";
	system("../limpiarEntorno.sh");
  }


	//ACA TAMBIEN PODEMOS DEFINIR FUNCIONES Y UTILIZARLAS PARA HACER
	//EL MISMO TEST CON DIFERENTES DATOS.


  // Declares the variables your tests want to use.
  string usuario;
  string password;
  string passwordIncorrecto;
  CredencialesDeUsuarios* credenciales;
};






TEST_F(CredencialesDeUsuariosTest, agregarUnNuevoUsuarioDeberiaDarTrue){
	ASSERT_TRUE(credenciales->agregarNuevoUsuario(usuario,password,5));
}



TEST_F(CredencialesDeUsuariosTest, alTratarDeAgregarUnUsuarioExistenteDeberiaDarFalse){
	cout<<"COMIENZA alTratarDeAgregarUnUsuarioExistenteDeberiaDarFalse\n";
	credenciales->agregarNuevoUsuario(usuario,password,5);
	cout<<"Se agrego un nuevo usuario\n";
	ASSERT_FALSE(credenciales->agregarNuevoUsuario(usuario,password,5));
	cout<<"Se paso el ASSERT\n";
}


TEST_F(CredencialesDeUsuariosTest, testAlPreguntarSiExisteUnUsuarioExistenteDeberiaDarTrue){
	credenciales->agregarNuevoUsuario(usuario,password,5);
	ASSERT_TRUE(credenciales->existeUsuario(usuario));
}

TEST_F(CredencialesDeUsuariosTest, testAlPreguntarSiExisteUnUsuarioInexistenteDeberiaDarFalse){

	ASSERT_FALSE(credenciales->existeUsuario(usuario));

}

TEST_F(CredencialesDeUsuariosTest, testValidarCredencialesCorrectasDaTrue){
	credenciales->agregarNuevoUsuario(usuario,password,5);
	ASSERT_TRUE(credenciales->validarCredenciales(usuario,password));
}


TEST_F(CredencialesDeUsuariosTest, testValidarCredencialesIncorrectasDaFalse){
	credenciales->agregarNuevoUsuario(usuario,password,5);
	ASSERT_FALSE(credenciales->validarCredenciales(usuario,passwordIncorrecto));
}





