#include "MensajeHTTPRequest.h"
#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <json/json.h>
//#include <json/value.h>
#include <fstream>

#include "db.h"


//Creo una fixture de test que seria como un
class HttpMessageRequestTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( HttpMessageRequestTest );
  CPPUNIT_TEST( testPrueboCrearUnaInstanciaVacia );
  CPPUNIT_TEST_SUITE_END();

public:



  void testPrueboCrearUnaInstanciaVacia(){
    MensajeHTTPRequest* msj = new MensajeHTTPRequest();
    CPPUNIT_ASSERT( msj == NULL);
    delete msj;
  }

  //void testPrueboCrearInstancia



};




// Agrega la TestFixture (ConstantesTest) al registro
CPPUNIT_TEST_SUITE_REGISTRATION( HttpMessageRequestTest );







int main(int argc, char* argv[])
{
  // Get the top level suite from the registry
  CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

  // Adds the test to the list of test to run
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( suite );

  // Change the default outputter to a compiler error format outputter
  runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
                                                       std::cerr ) );
  // Run the tests.
  bool wasSucessful = runner.run();

  // Return error code 1 if the one of test failed.
  return wasSucessful ? 0 : 1;
}
