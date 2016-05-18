#include "BaseDeDatos.h"
#include "gtest/gtest.h"
#include <string>
#include <iostream>

using namespace std;

TEST(AgregarUnaClaveValor, DeUnaClaveExistenteModificaElValorDeLaClave) {
	string valor = "valor";
	string valorDiferente = "valorDiferente";
	BaseDeDatos* baseDeDatos = new BaseDeDatos("./BaseDeDatosDePrueba");
	
	string clave = "AgregarUnaClaveValorDeUnaClaveExistenteModificaElValorDeLaClave";
	baseDeDatos->put(clave,valor);
	//Ahora agrego la misma clave pero con otro valor
	baseDeDatos->put(clave,valorDiferente);
	
	EXPECT_EQ(valorDiferente, baseDeDatos->get(clave));
}
