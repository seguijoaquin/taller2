#include "MensajeHTTPRequest.h"
#include "gtest/gtest.h"
#include <string>
#include <iostream>

using namespace std;


class HttpMessageRequestTest : public testing::Test{
	
	protected:
	
		virtual void SetUp(){
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
			mensaje = new MensajeHTTPRequest(&(this->mensajeMG));
			
		}
	
	
		virtual void TearDown(){
			delete mensaje;
		}
		
		
		string crearHeaderBodyLenght(string body){

			return ("Content-Length: " + to_string(body.length()) + "\r\n");
		}
		
		void iniciarMg_str(mg_str& mg_string, const char* contenido, size_t longitud){
			mg_string.p = contenido;
			mg_string.len = longitud;
		}
	
		http_message mensajeMG;
		MensajeHTTPRequest* mensaje;
	
};



TEST_F(HttpMessageRequestTest, testObjenerMetodoDelMensajeHTTPRequest){
	
	ASSERT_EQ("METODO", mensaje->getMetodo());
	
}

TEST_F(HttpMessageRequestTest, testObtenerUriDelMensajeHTTPRequest){
	ASSERT_EQ( "Uri1/Uri2/servicio", mensaje->getURI());
	
}

TEST_F(HttpMessageRequestTest, testObtenerHeadersDelMensajeHTTPRequest){
  ASSERT_EQ( "Valor0" , mensaje->getHeader("Header0"));
  ASSERT_EQ( "Valor1" , mensaje->getHeader("Header1"));	
	
}

TEST_F(HttpMessageRequestTest,testCrearUnMensajeHTTPRequestDesdeCero){
  MensajeHTTPRequest mensajeDesdeCero;
  string metodo,uri,header1,valor1,header2,valor2, body;
  metodo = "METODO";
  uri = "Uri3/Uri4/servicio";
  header1 = "Header1";
  valor1 = "Valor1";
  header2= "Header2";
  valor2 = "Valor2";
  body = "body body body\n funciona con newlines\nsomething";
  mensajeDesdeCero.setMetodo(metodo);
  mensajeDesdeCero.setURI(uri);
  mensajeDesdeCero.agregarHeader(header1, valor1);
  mensajeDesdeCero.agregarHeader(header2, valor2);
  mensajeDesdeCero.setBody(body);

  string headerBodyLenght = crearHeaderBodyLenght(body);

  string mensajeEsperado = metodo + " " + uri + " HTTP/1.1\r\n" + headerBodyLenght + header1 + ": " + valor1 + "\r\n" + header2 + ": " + valor2 + "\r\n\r\n" + body;

  ASSERT_EQ( mensajeEsperado,mensajeDesdeCero.toString());
}

