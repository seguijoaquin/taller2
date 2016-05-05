#ifndef MENSAJEHTTPREPLYTTESTS_H
#define MENSAJEHTTPREPLYTTESTS_H
#include "MensajeHTTPReply.h"
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
//#include "mongoose.h"


//Heredar de TestFixture le permite usar los macros que agregan pruebas a los suites
//Creo una fixture de test que seria como un
class HttpMessageReplyTest : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE( HttpMessageReplyTest );
    CPPUNIT_TEST( testObtenerCodigoDelMensajeHTTPReply );
    CPPUNIT_TEST( testObtenerMensajeDeEstadoDelMensajeHTTPReply );
    CPPUNIT_TEST( testObtenerHeadersDelMensajeHTTPReply );
    CPPUNIT_TEST_SUITE_END();
  public:
    HttpMessageReplyTest();
    ~HttpMessageReplyTest();
    void testObtenerCodigoDelMensajeHTTPReply();
    void testObtenerMensajeDeEstadoDelMensajeHTTPReply();
    void testObtenerHeadersDelMensajeHTTPReply();
  private:
    http_message mensajeMG;
    MensajeHTTPReply* mensaje;
    void iniciarMg_str(mg_str& mg_string, const char* contenido, size_t longitud);

};

#endif // MENSAJEHTTPREPLYTTESTS_H
