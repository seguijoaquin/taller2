#include "MensajeHTTPReply.h"
#include "gtest/gtest.h"
#include <string>
#include <iostream>



using namespace std;

class MensajeHTTPReplyTest : public  testing::Test {
	
	protected:
	
	virtual void SetUp(){
		
		  mg_str estado, header0, header1, headerVacio, valor0, valor1, valorVacio, body;
		  
		  this->iniciarMg_str(estado, "ERROR OK",8);
		  this->iniciarMg_str(header0, "Header0",7);
		  this->iniciarMg_str(header1, "Header1",7);
		  this->iniciarMg_str(headerVacio, "",0);
		  this->iniciarMg_str(valor0, "Valor0",6);
		  this->iniciarMg_str(valor1, "Valor1",6);
		  this->iniciarMg_str(valorVacio, "",0);
  		  this->iniciarMg_str(body, "",0);

		  //Aca se copian los valores
		  this->mensajeMG.resp_code = 666;
		  this->mensajeMG.resp_status_msg = estado;

		  this->mensajeMG.header_names[0] = header0;
		  this->mensajeMG.header_values[0] = valor0;

		  this->mensajeMG.header_names[1] = header1;
		  this->mensajeMG.header_values[1] = valor1;

		  this->mensajeMG.header_names[2] = headerVacio;
		  this->mensajeMG.header_values[2] = valorVacio;

	          this->mensajeMG.body = body;

		  mensaje = new MensajeHTTPReply(&(this->mensajeMG));
		
		}
	
		void iniciarMg_str(mg_str& mg_string, const char* contenido, size_t longitud){
			mg_string.p = contenido;
			mg_string.len = longitud;
		}
	
	
		virtual void TearDown(){
			delete mensaje;
		}
	
	
		http_message mensajeMG;
		MensajeHTTPReply* mensaje;
    
	
};





TEST_F(MensajeHTTPReplyTest, testObjetenerCodigoDelMensajeHTTPReply){

	ASSERT_EQ(666,mensaje->getCodigo());
	
}


TEST_F(MensajeHTTPReplyTest, testObtenerMensajeDeEstadoDelMensajeHTTPReply){

	ASSERT_EQ("ERROR OK",mensaje->getMensajeDeEstado());
}



TEST_F(MensajeHTTPReplyTest, testObtenerHeaderDelMensajeHTTPReply){
	ASSERT_EQ("Valor0",mensaje->getHeader("Header0"));
	ASSERT_EQ("Valor1",mensaje->getHeader("Header1"));
}





