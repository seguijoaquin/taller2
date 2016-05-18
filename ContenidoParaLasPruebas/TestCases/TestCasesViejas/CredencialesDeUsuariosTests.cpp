#include "CredencialesDeUsuariosTests.h"

using namespace std;

string password = "password";
string passwordIncorrecto = "passwordIncorrecto";

CPPUNIT_TEST_SUITE_REGISTRATION( CredencialesDeUsuariosTest );

CredencialesDeUsuariosTest::CredencialesDeUsuariosTest(){

}
CredencialesDeUsuariosTest::~CredencialesDeUsuariosTest(){

}




void CredencialesDeUsuariosTest::setUp(){
  //TODO: se podria agregar que borre y rearme el directorio en que este la base de datos, pero no se como hacerlo desde c++...
  /*IMPORTANTE: como ahora no puede crear y borrar la base de datos a mitad de la prueba, como regla
    uso como nombre de usuario el nombre de la test
  */
  //Si ya existe, la abre
  this->credenciales = new CredencialesDeUsuarios("./CredencialesDePrueba");
}
void CredencialesDeUsuariosTest::tearDown(){
  //TODO: se podria agregar que borre y rearme el directorio en que este la base de datos, pero no se como hacerlo desde c++...
  /*IMPORTANTE: como ahora no puede crear y borrar la base de datos a mitad de la prueba, como regla
    uso como nombre de usuario el nombre de la test
  */
  //Esto NO borra la carpeta CredencialesDePrueba ni su contenido
  delete this->credenciales;
}


void CredencialesDeUsuariosTest::agregarUsuario(string usuario){
  //Agrego siempre el mismo password
  this->credenciales->agregarNuevoUsuario(usuario,password);
}


void CredencialesDeUsuariosTest::testAgregarUnNuevoUsuario(){
  //Si devuelve T, es porque se pudo agregar un nuevo usuario
  CPPUNIT_ASSERT(this->credenciales->agregarNuevoUsuario("AgregarUnNuevoUsuario",password));
}


void CredencialesDeUsuariosTest::testAgregarUnUsuarioYaExistente(){
  //Si devuelve F, es porque el usuario ya existe
  string usuario = "AgregarUnUsuarioYaExistente";
  this->agregarUsuario(usuario);
  //Intento agregar dos veces al mismo
  CPPUNIT_ASSERT(!this->credenciales->agregarNuevoUsuario(usuario,password));
}

void CredencialesDeUsuariosTest::testUsuarioExistente(){
  string usuario = "testUsuarioExistente";
  this->agregarUsuario(usuario);
  //como lo agregue en la linea anterior, obviamente va a existir
  CPPUNIT_ASSERT(this->credenciales->existeUsuario(usuario));
}

void CredencialesDeUsuariosTest::testUsuarioInexistente(){
  string usuario = "UsuarioInexistente";
  //Nunca se agrega, va a dar F
  CPPUNIT_ASSERT(!this->credenciales->existeUsuario(usuario));
}



void CredencialesDeUsuariosTest::testValidarCredencialesCorrectas(){
  string usuario = "ValidarCredencialesCorrectas";
  //Esta funcion agrega como password a la variable password, definida al principio de este archivo
  this->agregarUsuario(usuario);
  //Se devuelve T si las credenciales son validas, F si no
  CPPUNIT_ASSERT(this->credenciales->validarCredenciales(usuario, password));
}

void CredencialesDeUsuariosTest::testValidarCredencialesIncorrectas(){
  string usuario = "ValidarCredencialesIncorrectas";
  this->agregarUsuario(usuario);
  //Se devuelve T si las credenciales son validas, F si no
  CPPUNIT_ASSERT(!this->credenciales->validarCredenciales(usuario, passwordIncorrecto));
}
