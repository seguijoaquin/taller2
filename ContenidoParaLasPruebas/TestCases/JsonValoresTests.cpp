#include "JsonValoresTests.h"

//using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( JsonValoresTests );


JsonValoresTests::JsonValoresTests(){

}
JsonValoresTests::~JsonValoresTests(){

}

void JsonValoresTests::setUp(){
}
void JsonValoresTests::tearDown(){

}

void JsonValoresTests::agregarNumeroAlJsonArray(int numero,JsonArray& jarray){
    //int nro = numero;
    //jarray.agregar(nro);
    jarray.agregar(numero);
}

void JsonValoresTests::agregarPalabraAlJsonArray(string palabra,JsonArray& jarray){
    //int nro = numero;
    //jarray.agregar(nro);
    jarray.agregar(palabra);
}

bool JsonValoresTests::compararStringConJsonValor(string stringEsperado,JsonValor jvalor){
    return jvalor.toString().compare(stringEsperado);
}





void JsonValoresTests::testJsonArrayComienzaVacio(){
  JsonArray jarray;
  CPPUNIT_ASSERT(compararStringConJsonValor("[]", jarray));
}

void JsonValoresTests::testAgregarUnNumerolJsonArray(){
  JsonArray jarray;
  this->agregarNumeroAlJsonArray(1,jarray);
  CPPUNIT_ASSERT(compararStringConJsonValor("[1]", jarray));
}

void JsonValoresTests::testAgregarVariosNumerosAlJsonArrayElUltimoEnAgregarseEsElDeMayorOrden(){
  JsonArray jarray;
  this->agregarNumeroAlJsonArray(1,jarray);
  this->agregarNumeroAlJsonArray(2,jarray);
  this->agregarNumeroAlJsonArray(3,jarray);
  this->agregarNumeroAlJsonArray(4,jarray);
  this->agregarNumeroAlJsonArray(5,jarray);

  CPPUNIT_ASSERT(compararStringConJsonValor("[1,2,3,4,5]", jarray));
  //if(jarray[0].toString().compare("1")){
  CPPUNIT_ASSERT(compararStringConJsonValor("1", jarray[0]));
  CPPUNIT_ASSERT(compararStringConJsonValor("2", jarray[1]));
  CPPUNIT_ASSERT(compararStringConJsonValor("3", jarray[2]));
  CPPUNIT_ASSERT(compararStringConJsonValor("4", jarray[3]));
  CPPUNIT_ASSERT(compararStringConJsonValor("5", jarray[4]));
}



void JsonValoresTests::testAgregarUnaPalabraAlJsonArray(){
  JsonArray jarray;
  this->agregarPalabraAlJsonArray("uno",jarray);
  CPPUNIT_ASSERT(compararStringConJsonValor("\"uno\"",jarray));
}

//Tal vez habria que refactorizar esta test.....
void JsonValoresTests::testAgregarVariasPalabrasAlJsonArray(){
  JsonArray jarray;
  this->agregarPalabraAlJsonArray("uno",jarray);
  this->agregarPalabraAlJsonArray("dos",jarray);
  this->agregarPalabraAlJsonArray("tres",jarray);
  this->agregarPalabraAlJsonArray("cuatro",jarray);
  this->agregarPalabraAlJsonArray("cinco",jarray);
  CPPUNIT_ASSERT(compararStringConJsonValor("[\"uno\",\"dos\",\"tres\",\"cuatro\",\"cinco\"]", jarray));
  CPPUNIT_ASSERT(compararStringConJsonValor("\"uno\"",jarray[0]));
  CPPUNIT_ASSERT(compararStringConJsonValor("\"dos\"",jarray[1]));
  CPPUNIT_ASSERT(compararStringConJsonValor("\"tres\"",jarray[2]));
  CPPUNIT_ASSERT(compararStringConJsonValor("\"cuatro\"",jarray[3]));
  CPPUNIT_ASSERT(compararStringConJsonValor("\"cinco\"",jarray[4]));
}

void JsonValoresTests::testAgregarUnJsonArrayAlJsonArray(){
  JsonArray jarray1, jarray2;
  this->agregarPalabraAlJsonArray("1",jarray1);
  this->agregarPalabraAlJsonArray("2",jarray1);

  this->agregarPalabraAlJsonArray("11",jarray2);
  this->agregarPalabraAlJsonArray("22",jarray2);
  this->agregarPalabraAlJsonArray("33",jarray2);

  this->agregarPalabraAlJsonArray("3",jarray1);

  jarray1.agregar(jarray2);
  CPPUNIT_ASSERT(compararStringConJsonValor("[1,2,[11,22,33],3]",jarray1));
}






