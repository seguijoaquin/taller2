#include "JsonArray.h"
#include <iostream>
#include "gtest/gtest.h"
//using namespace std;



class JsonValoresTests : public testing::Test{
	
	protected:
	
		void agregarNumeroAlJsonArray(int numero,JsonArray& jarray){
			//int nro = numero;
			//jarray.agregar(nro);
			jarray.agregar(numero);
		}

		void agregarPalabraAlJsonArray(string palabra,JsonArray& jarray){
			//int nro = numero;
			//jarray.agregar(nro);
			jarray.agregar(palabra);
		}

		bool compararStringConJsonValor(string stringEsperado,JsonValor jvalor){
			return jvalor.toString().compare(stringEsperado);
		}
		
	
	
	
};



TEST_F(JsonValoresTests,testJsonArrayComienzaVacio){
  JsonArray jarray;
  ASSERT_TRUE(compararStringConJsonValor("[]", jarray));
}



TEST_F(JsonValoresTests, testAgregarUnNumerolJsonArray){
  JsonArray jarray;
  agregarNumeroAlJsonArray(1,jarray);
  ASSERT_TRUE(compararStringConJsonValor("[1]", jarray));
}






TEST_F(JsonValoresTests,testAgregarVariosNumerosAlJsonArrayElUltimoEnAgregarseEsElDeMayorOrden){
  JsonArray jarray;
  this->agregarNumeroAlJsonArray(1,jarray);
  this->agregarNumeroAlJsonArray(2,jarray);
  this->agregarNumeroAlJsonArray(3,jarray);
  this->agregarNumeroAlJsonArray(4,jarray);
  this->agregarNumeroAlJsonArray(5,jarray);

  ASSERT_TRUE(compararStringConJsonValor("[1,2,3,4,5]", jarray));
  //if(jarray[0].toString().compare("1")){
  ASSERT_TRUE(compararStringConJsonValor("1", jarray[0]));
  ASSERT_TRUE(compararStringConJsonValor("2", jarray[1]));
  ASSERT_TRUE(compararStringConJsonValor("3", jarray[2]));
  ASSERT_TRUE(compararStringConJsonValor("4", jarray[3]));
  ASSERT_TRUE(compararStringConJsonValor("5", jarray[4]));
}






TEST_F(JsonValoresTests,testAgregarUnaPalabraAlJsonArray){
  JsonArray jarray;
  this->agregarPalabraAlJsonArray("uno",jarray);
  ASSERT_TRUE(compararStringConJsonValor("\"uno\"",jarray));
}

//Tal vez habria que refactorizar esta test.....
TEST_F(JsonValoresTests,testAgregarVariasPalabrasAlJsonArray){
  JsonArray jarray;
  this->agregarPalabraAlJsonArray("uno",jarray);
  this->agregarPalabraAlJsonArray("dos",jarray);
  this->agregarPalabraAlJsonArray("tres",jarray);
  this->agregarPalabraAlJsonArray("cuatro",jarray);
  this->agregarPalabraAlJsonArray("cinco",jarray);
  ASSERT_TRUE(compararStringConJsonValor("[\"uno\",\"dos\",\"tres\",\"cuatro\",\"cinco\"]", jarray));
  ASSERT_TRUE(compararStringConJsonValor("\"uno\"",jarray[0]));
  ASSERT_TRUE(compararStringConJsonValor("\"dos\"",jarray[1]));
  ASSERT_TRUE(compararStringConJsonValor("\"tres\"",jarray[2]));
  ASSERT_TRUE(compararStringConJsonValor("\"cuatro\"",jarray[3]));
  ASSERT_TRUE(compararStringConJsonValor("\"cinco\"",jarray[4]));
}

TEST_F(JsonValoresTests,testAgregarUnJsonArrayAlJsonArray){
  JsonArray jarray1, jarray2;
  this->agregarPalabraAlJsonArray("1",jarray1);
  this->agregarPalabraAlJsonArray("2",jarray1);

  this->agregarPalabraAlJsonArray("11",jarray2);
  this->agregarPalabraAlJsonArray("22",jarray2);
  this->agregarPalabraAlJsonArray("33",jarray2);

  this->agregarPalabraAlJsonArray("3",jarray1);

  jarray1.agregar(jarray2);
  ASSERT_TRUE(compararStringConJsonValor("[1,2,[11,22,33],3]",jarray1));
}



/*















*/



