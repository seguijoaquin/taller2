#include "MensajeHTTPRequestTests.h"

//using namespace std;

// Agrega la TestFixture (HttpMessageRequestTest) al registro
CPPUNIT_TEST_SUITE_REGISTRATION( HttpMessageRequestTest );

void HttpMessageRequestTest::iniciarMg_str(mg_str& mg_string, const char* contenido, size_t longitud){
    mg_string.p = contenido;
    mg_string.len = longitud;
}

HttpMessageRequestTest::HttpMessageRequestTest(){
  mg_str metodo, uri, header0, header1, headerVacio, valor0, valor1, valorVacio;
  this->iniciarMg_str(metodo, "METODO",6);
  this->iniciarMg_str(uri, "Uri1/Uri2/servicio",18);
  this->iniciarMg_str(header0, "Header0",7);
  this->iniciarMg_str(header1, "Header1",7);
  this->iniciarMg_str(headerVacio, "",0);
  this->iniciarMg_str(valor0, "Valor0",6);
  this->iniciarMg_str(valor1, "Valor1",6);
  this->iniciarMg_str(valorVacio, "",0);

  //Aca se copian los valores
  this->mensajeMG.method = metodo;
  this->mensajeMG.uri = uri;

  this->mensajeMG.header_names[0] = header0;
  this->mensajeMG.header_values[0] = valor0;

  this->mensajeMG.header_names[1] = header1;
  this->mensajeMG.header_values[1] = valor1;

  this->mensajeMG.header_names[2] = headerVacio;
  this->mensajeMG.header_values[2] = valorVacio;

  //El 0 dummy esta por ahora, porque queria probar algo en el codigo, TODO: sacarla
  this->mensaje = new MensajeHTTPRequest(&(this->mensajeMG),0);
}

HttpMessageRequestTest::~HttpMessageRequestTest(){
  delete this->mensaje;
}

void HttpMessageRequestTest::testObtenerMetodoDelMensajeHTTPRequest(){
  CPPUNIT_ASSERT( "METODO" == this->mensaje->getMetodo());
}

void HttpMessageRequestTest::testObtenerUriDelMensajeHTTPRequest(){
  CPPUNIT_ASSERT( "Uri1/Uri2/servicio" == this->mensaje->getURI());
}

void HttpMessageRequestTest::testObtenerHeadersDelMensajeHTTPRequest(){
  CPPUNIT_ASSERT( "Valor0" == this->mensaje->getHeader("Header0"));
  CPPUNIT_ASSERT( "Valor1" == this->mensaje->getHeader("Header1"));
}
