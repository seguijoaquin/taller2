#ifndef MENSAJEHTTPREQUESTTESTS_H
#define MENSAJEHTTPREQUESTTESTS_H
#include "MensajeHTTPRequest.h"
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
//#include "mongoose.h"


//Heredar de TestFixture le permite usar los macros que agregan pruebas a los suites
//Creo una fixture de test que seria como un
class HttpMessageRequestTest : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE( HttpMessageRequestTest );
    CPPUNIT_TEST( testObtenerMetodoDelMensajeHTTPRequest );
    CPPUNIT_TEST( testObtenerUriDelMensajeHTTPRequest );
    CPPUNIT_TEST( testObtenerHeadersDelMensajeHTTPRequest );
    CPPUNIT_TEST_SUITE_END();
  public:
    HttpMessageRequestTest();
    ~HttpMessageRequestTest();
    void testObtenerMetodoDelMensajeHTTPRequest();
    void testObtenerUriDelMensajeHTTPRequest();
    void testObtenerHeadersDelMensajeHTTPRequest();
  private:
    http_message mensajeMG;
    MensajeHTTPRequest* mensaje;
    void iniciarMg_str(mg_str& mg_string, const char* contenido, size_t longitud);

};

#endif // MENSAJEHTTPREQUESTTESTS_H
