#ifndef BASEDEDATOSTESTS_H
#define BASEDEDATOSTESTS_H
#include "BaseDeDatos.h"
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include <string>


using namespace std;

class BaseDeDatosTest : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE( BaseDeDatosTest );
    CPPUNIT_TEST( testAgregarUnaClaveValorNuevaYObtenerla );
    CPPUNIT_TEST( testAgregarUnaClaveValorDeUnaClaveExistenteModificaElValorDeLaClave );
    CPPUNIT_TEST( testObtenerElValorDeUnaClaveInexistenteDebeDevolverUnValorVacio );
    CPPUNIT_TEST( testExistenciaDeClaveExistente );
    CPPUNIT_TEST( testExistenciaDeClaveInexistente );

    CPPUNIT_TEST_SUITE_END();

  public:
    BaseDeDatosTest();
    ~BaseDeDatosTest();
    void setUp();
    void tearDown();


    /*IMPORTANTE: como ahora no puede crear y borrar la base de datos a mitad de la prueba, como regla
      uso como clave el nombre de la test
    */
    void testAgregarUnaClaveValorNuevaYObtenerla();
    void testAgregarUnaClaveValorDeUnaClaveExistenteModificaElValorDeLaClave();
    void testObtenerElValorDeUnaClaveInexistenteDebeDevolverUnValorVacio();
    void testExistenciaDeClaveExistente();
    void testExistenciaDeClaveInexistente();

  private:
    BaseDeDatos* baseDeDatos;


};

#endif // BASEDEDATOSTESTS_H
