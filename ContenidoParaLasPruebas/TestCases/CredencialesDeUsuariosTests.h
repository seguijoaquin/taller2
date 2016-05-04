#ifndef CREDENCIALESDEUSUARIOSTESTS_H
#define CREDENCIALESDEUSUARIOSTESTS_H
#include "CredencialesDeUsuarios.h"
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include "servicioRegistro.h"


using namespace std;



class CredencialesDeUsuariosTest : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE( CredencialesDeUsuariosTest );
    CPPUNIT_TEST( testAgregarUnNuevoUsuario );
    CPPUNIT_TEST( testAgregarUnUsuarioYaExistente );
    CPPUNIT_TEST( testUsuarioExistente );
    CPPUNIT_TEST( testUsuarioInexistente );
    CPPUNIT_TEST( testValidarCredencialesCorrectas );
    CPPUNIT_TEST( testValidarCredencialesIncorrectas );
    CPPUNIT_TEST_SUITE_END();

  public:
    CredencialesDeUsuariosTest();
    ~CredencialesDeUsuariosTest();
    void setUp();
    void tearDown();


    /*IMPORTANTE: como ahora no puede crear y borrar la base de datos a mitad de la prueba, como regla
      uso como nombre de usuario el nombre de la test
    */
    void testAgregarUnNuevoUsuario();
    void testAgregarUnUsuarioYaExistente();

    void testUsuarioExistente();
    void testUsuarioInexistente();

    void testValidarCredencialesCorrectas();
    void testValidarCredencialesIncorrectas();

  private:
    CredencialesDeUsuarios* credenciales;
    void agregarUsuario(string usuario);

};

#endif // CREDENCIALESDEUSUARIOSTESTS_H
