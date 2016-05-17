#ifndef JSONVALORESTESTS_H
#define JSONVALORESTESTS_H
#include "JsonArray.h"
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>


//Heredar de TestFixture le permite usar los macros que agregan pruebas a los suites
//Creo una fixture de test que seria como un
class JsonValoresTests : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE( JsonValoresTests );
    CPPUNIT_TEST( testJsonArrayComienzaVacio );
    CPPUNIT_TEST( testAgregarUnNumerolJsonArray );
    CPPUNIT_TEST( testAgregarVariosNumerosAlJsonArrayElUltimoEnAgregarseEsElDeMayorOrden );
    CPPUNIT_TEST( testAgregarUnaPalabraAlJsonArray );
    CPPUNIT_TEST( testAgregarVariasPalabrasAlJsonArray );
    CPPUNIT_TEST( testAgregarUnJsonArrayAlJsonArray );
    CPPUNIT_TEST_SUITE_END();
  public:
    JsonValoresTests();
    ~JsonValoresTests();
    void setUp();
    void tearDown();

    void testJsonArrayComienzaVacio();
    void testAgregarUnNumerolJsonArray();
    void testAgregarVariosNumerosAlJsonArrayElUltimoEnAgregarseEsElDeMayorOrden();
    void testAgregarUnaPalabraAlJsonArray();
    void testAgregarVariasPalabrasAlJsonArray();
    void testAgregarUnJsonArrayAlJsonArray();
  private:
     void agregarNumeroAlJsonArray(int numero,JsonArray& jarray);
     void agregarPalabraAlJsonArray(string palabra,JsonArray& jarray);
     bool compararStringConJsonValor(string stringEsperado,JsonValor jvalor);

};

#endif // JSONVALORESTESTS_H
