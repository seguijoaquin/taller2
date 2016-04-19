#include "constantes.hpp"
#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <json/json.h>
#include <json/value.h>
#include <fstream>


//Creo una fixture de test que seria como un
class ConstantesTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( ConstantesTest);
  CPPUNIT_TEST( testAlObtenerLaInstanciaDelSingletonDeberiaDarDiferenteDeNull );
  CPPUNIT_TEST_SUITE_END();

public:

  void setUp(){
    //subo el archivo de json
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    std::ifstream config_doc("constantes.json", std::ifstream::binary);
    config_doc >> root;




    std::cout << root << "\n";
    std::cout << "aslkdjaslkdjaslkdj"<< std::endl;
  };



  void testAlObtenerLaInstanciaDelSingletonDeberiaDarDiferenteDeNull(){
    CPPUNIT_ASSERT(Constantes::Instance() != NULL);
  }



};




// Agrega la TestFixture (ConstantesTest) al registro
CPPUNIT_TEST_SUITE_REGISTRATION( ConstantesTest );







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
