#include "BaseDeDatos.h"
#include "gtest/gtest.h"
#include <string>
#include <iostream>

using namespace std;




// To use a test fixture, derive a class from testing::Test.
class BaseDeDatosTest : public testing::Test {

 protected:  // You should make the members protected s.t. they can be
             // accessed from sub-classes.

  // virtual void SetUp() will be called before each test is run.  You
  // should define it if you need to initialize the varaibles.
  // Otherwise, this can be skipped.

  virtual void SetUp() {
   	valor = "valor";
	valorDiferente = "valorDiferente";
	clave = "AgregarUnaClaveValorDeUnaClaveExistenteModificaElValorDeLaClave";
	baseDeDatos = new BaseDeDatos("./Entorno/BaseDeDatosDePrueba");
  }



  // virtual void TearDown() will be called after each test is run.
  // You should define it if there is cleanup work to do.  Otherwise,
  // you don't have to provide it.
  //
  virtual void TearDown() {
	delete baseDeDatos;
    system("../limpiarEntorno.sh");
  }




	//ACA TAMBIEN PODEMOS DEFINIR FUNCIONES Y UTILIZARLAS PARA HACER
	//EL MISMO TEST CON DIFERENTES DATOS.


  // Declares the variables your tests want to use.
  string clave;
  string valor;
  string valorDiferente;
  BaseDeDatos* baseDeDatos;
};


TEST_F(BaseDeDatosTest, testAgregarUnaClaveValorNuevaYObtenerla){
	baseDeDatos->put(clave,valor);
	ASSERT_EQ(valor,baseDeDatos->get(clave));
}


// El primer parametro es el nombre de la clase en la que describimos
// las variables a utilizar y demas.
//El segundo parametro es el nombre del test.
TEST_F(BaseDeDatosTest, AlHacerDosVecesUnPutConLaMismaClaveElValorAlmacenadoDeberiaSerElUltimoGuardado) {
	//Todas las variables estan definidas en la clase
	baseDeDatos->put(clave,valor);
	baseDeDatos->put(clave,valorDiferente);

	ASSERT_EQ(valorDiferente, baseDeDatos->get(clave));

}


TEST_F(BaseDeDatosTest, testAlPreguntarPorLaExistenciaDeUnaClaveInexistenteDeberiaDarFalse){
	 string clave = "ExistenciaDeClaveInexistente";
	 ASSERT_FALSE(baseDeDatos->existe(clave));
}



TEST_F(BaseDeDatosTest, existenciaDeUnaClaveExistente){
	baseDeDatos->put(clave,valor);
	ASSERT_TRUE(baseDeDatos->existe(clave));

}


TEST_F(BaseDeDatosTest, testObtenerElValorDeUnaClaveInexistenteDebeDevolverUnValorVacio){
	string claveInexistente = "CLAVEINEXISTENTE";
	ASSERT_FALSE(baseDeDatos->existe(claveInexistente));
	ASSERT_EQ("",baseDeDatos->get(claveInexistente));
}





