#include "MensajeHTTPReplyTests.h"

//using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( HttpMessageReplyTest );

void HttpMessageReplyTest::iniciarMg_str(mg_str& mg_string, const char* contenido, size_t longitud){
    mg_string.p = contenido;
    mg_string.len = longitud;
}

HttpMessageReplyTest::HttpMessageReplyTest(){
  mg_str estado, header0, header1, headerVacio, valor0, valor1, valorVacio;
  this->iniciarMg_str(estado, "ERROR OK",8);
  this->iniciarMg_str(header0, "Header0",7);
  this->iniciarMg_str(header1, "Header1",7);
  this->iniciarMg_str(headerVacio, "",0);
  this->iniciarMg_str(valor0, "Valor0",6);
  this->iniciarMg_str(valor1, "Valor1",6);
  this->iniciarMg_str(valorVacio, "",0);

  //Aca se copian los valores
  this->mensajeMG.resp_code = 666;
  this->mensajeMG.resp_status_msg = estado;

  this->mensajeMG.header_names[0] = header0;
  this->mensajeMG.header_values[0] = valor0;

  this->mensajeMG.header_names[1] = header1;
  this->mensajeMG.header_values[1] = valor1;

  this->mensajeMG.header_names[2] = headerVacio;
  this->mensajeMG.header_values[2] = valorVacio;

  //El 0 dummy esta por ahora, porque queria probar algo en el codigo, TODO: sacarla
  this->mensaje = new MensajeHTTPReply(&(this->mensajeMG));
}

HttpMessageReplyTest::~HttpMessageReplyTest(){
  delete this->mensaje;
}

void HttpMessageReplyTest::testObtenerCodigoDelMensajeHTTPReply(){
  CPPUNIT_ASSERT( 666 == this->mensaje->getCodigo());
}

void HttpMessageReplyTest::testObtenerMensajeDeEstadoDelMensajeHTTPReply(){
  CPPUNIT_ASSERT( "ERROR OK" == this->mensaje->getMensajeDeEstado());
}

void HttpMessageReplyTest::testObtenerHeadersDelMensajeHTTPReply(){
  CPPUNIT_ASSERT( "Valor0" == this->mensaje->getHeader("Header0"));
  CPPUNIT_ASSERT( "Valor1" == this->mensaje->getHeader("Header1"));
}
