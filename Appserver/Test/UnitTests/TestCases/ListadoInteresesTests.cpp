#include "ListadoDeIntereses.h"
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
using namespace std;


class ListadoDeInteresesTest : public testing::Test{
	protected:

		virtual void SetUp(){

		}

		virtual void TearDown(){

		}


        string direccion = "./ArchivosTests/ArchivosListadoDeInteresesTests/";
		string archivoDePrueba = "ListadoDeIntereses.txt";
		int tamanioListadoDePrueba = 3;

		string archivoInteresDelListado = "InteresDelListado.txt";
        string archivoInteresQueNoEstaEnElListado = "InteresQueNoEstaEnElListado.txt";

        string prefijoCategoriaIntereses = "CATEGORIA";
        string prefijoValorIntereses = "VALOR";

        string leerArchivo(string nombre){
            //http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
            string ruta = direccion + nombre;
            ifstream in(ruta, ios::in | ios::binary);
            return( string( (istreambuf_iterator<char>(in)), istreambuf_iterator<char>()) );
        }

        void inicializarListadoDePrueba(ListadoDeIntereses& listado){
            listado.agregarIntereses(leerArchivo(archivoDePrueba));
        }

        bool compararInteres( Interes& interes, string categoriaEsperada, string valorEsperado ){
            return ( ( interes.getCategoria() == categoriaEsperada) && (interes.getValor() == valorEsperado) );
        }

        Interes crearInteresDelListado(){
            return Interes( leerArchivo(archivoInteresDelListado)  );
        }

        Interes crearInteresQueNoEsteEnElListado(){
            return Interes( leerArchivo(archivoInteresQueNoEstaEnElListado)  );
        }
};


TEST_F(ListadoDeInteresesTest, testAgregarInteresesAUnListadoAPartirDeUnStringConElFormatoCorrecto){
    ListadoDeIntereses listado;
    this->inicializarListadoDePrueba(listado);

    ASSERT_EQ(this->tamanioListadoDePrueba, listado.size());

    for (int i= 1; i <= listado.size(); i++){
        string categoriaEsperada = prefijoCategoriaIntereses + to_string(i);
        string valorEsperado = prefijoValorIntereses + to_string(i);
        Interes interes = listado.getInteres(i);
        ASSERT_TRUE( this->compararInteres( interes , categoriaEsperada, valorEsperado ) );
    }
}

TEST_F(ListadoDeInteresesTest, testQuererAccederAUnInteresConIndiceInvalidoDevuelveUnInteresVacio){
    ListadoDeIntereses listado;
    this->inicializarListadoDePrueba(listado);

    int indiceInvalido = listado.size() + 1;
    Interes interes = listado.getInteres(indiceInvalido);
    ASSERT_TRUE( this->compararInteres( interes , "", "") );

}


TEST_F(ListadoDeInteresesTest, testVerSiElListadoTieneUnInteresQueEfectivamenteTieneDevuelveVerdadero){
    ListadoDeIntereses listado;
    this->inicializarListadoDePrueba(listado);

    Interes interes = crearInteresDelListado();
    ASSERT_TRUE( listado.tieneInteres(interes) );
}

TEST_F(ListadoDeInteresesTest, testVerSiElListadoTieneUnInteresQueNoTieneDevuelveFalso){
    ListadoDeIntereses listado;
    this->inicializarListadoDePrueba(listado);

    Interes interes = crearInteresQueNoEsteEnElListado();
    ASSERT_FALSE( listado.tieneInteres(interes) );
}
