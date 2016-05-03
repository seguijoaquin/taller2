#ifndef SESIONESDEUSUARIOSTESTS_H
#define SESIONESDEUSUARIOSTESTS_H
#include "SesionesDeUsuarios.h"
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>


//Heredar de TestFixture le permite usar los macros que agregan pruebas a los suites
//Creo una fixture de test que seria como un
class SesionesDeUsuariosTest : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE( SesionesDeUsuariosTest );
    CPPUNIT_TEST( testAgregarUnaSesionDeUsuario );
    CPPUNIT_TEST( testValidarUsuarioTokenCorrectos );
    CPPUNIT_TEST( testValidarUsuarioTokenIncorrectos );
    CPPUNIT_TEST_SUITE_END();
  public:
    SesionesDeUsuariosTest();
    ~SesionesDeUsuariosTest();
    void setUp();
    void tearDown();

    void testAgregarUnaSesionDeUsuario();
    void testValidarUsuarioTokenCorrectos();
    void testValidarUsuarioTokenIncorrectos();
  private:
    SesionesDeUsuarios* sesiones;

};

#endif // SESIONESDEUSUARIOSTESTS_H
