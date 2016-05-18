#include "BaseDeDatosTests.h"

using namespace std;

string valor = "valor";
string valorDiferente = "valorDiferente";
string valorDeClaveInexistente = "";

CPPUNIT_TEST_SUITE_REGISTRATION( BaseDeDatosTest );

BaseDeDatosTest::BaseDeDatosTest(){
}

BaseDeDatosTest::~BaseDeDatosTest(){

}




void BaseDeDatosTest::setUp(){
  //TODO: se podria agregar que borre y rearme el directorio en que este la base de datos, pero no se como hacerlo desde c++...
  /*IMPORTANTE: como ahora no puede crear y borrar la base de datos a mitad de la prueba, como regla
    uso como clave el nombre de la test
  */
  //Si ya existe, la abre
  this->baseDeDatos = new BaseDeDatos("./BaseDeDatosDePrueba");
}
void BaseDeDatosTest::tearDown(){
  //TODO: se podria agregar que borre y rearme el directorio en que este la base de datos, pero no se como hacerlo desde c++...
  /*IMPORTANTE: como ahora no puede crear y borrar la base de datos a mitad de la prueba, como regla
    uso como clave el nombre de la test
  */
  //Esto NO borra la carpeta BaseDeDatosDePrueba ni su contenido
  delete this->baseDeDatos;
}


void BaseDeDatosTest::testAgregarUnaClaveValorNuevaYObtenerla(){
  string clave = "AgregarUnaClaveValorNueva";
  this->baseDeDatos->put(clave,valor);
  CPPUNIT_ASSERT_EQUAL(valor,this->baseDeDatos->get(clave));
}

void BaseDeDatosTest::testAgregarUnaClaveValorDeUnaClaveExistenteModificaElValorDeLaClave(){
  string clave = "AgregarUnaClaveValorDeUnaClaveExistenteModificaElValorDeLaClave";
  this->baseDeDatos->put(clave,valor);
  //Ahora agrego la misma clave pero con otro valor
  this->baseDeDatos->put(clave,valorDiferente);
  CPPUNIT_ASSERT_EQUAL(valorDiferente,this->baseDeDatos->get(clave));
  CPPUNIT_ASSERT(valor != this->baseDeDatos->get(clave));
}

void BaseDeDatosTest::testObtenerElValorDeUnaClaveInexistenteDebeDevolverUnValorVacio(){
  //Por la regla me aseguro que ninguna otra test uso esta clave
  string clave = "ObtenerElValorDeUnaClaveInexistenteDebeDevolverUnValorVacio";
  CPPUNIT_ASSERT_EQUAL(valorDeClaveInexistente,this->baseDeDatos->get(clave));
}

void BaseDeDatosTest::testExistenciaDeClaveExistente(){
  string clave = "ExistenciaDeClaveExistente";
  this->baseDeDatos->put(clave,valor);
  CPPUNIT_ASSERT(this->baseDeDatos->existe(clave));
}

void BaseDeDatosTest::testExistenciaDeClaveInexistente(){
  //Por la regla me aseguro que ninguna otra test uso esta clave
  string clave = "ExistenciaDeClaveInexistente";
  CPPUNIT_ASSERT(!this->baseDeDatos->existe(clave));
}
