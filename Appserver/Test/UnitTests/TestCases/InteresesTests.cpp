#include "Interes.h"
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
using namespace std;


class InteresesTest : public testing::Test{
	protected:

		virtual void SetUp(){

		}

		virtual void TearDown(){

		}

		string rutaArchivoDePrueba = "./ArchivosTests/ArchivosInteresesTests/Interes.txt";
		string rutaArchivoDePruebaConDiferenteCategoria = "./ArchivosTests/ArchivosInteresesTests/InteresDiferenteCategoria.txt";
		string rutaArchivoDePruebaConDiferenteValor = "./ArchivosTests/ArchivosInteresesTests/InteresDiferenteValor.txt";
		string rutaArchivoDePruebaConDiferenteCategoriaYValor = "./ArchivosTests/ArchivosInteresesTests/InteresDiferenteCategoriaYValor.txt";

        string categoriaInteresDePrueba = "CATEGORIA";
        string valorInteresDePrueba = "VALOR";

        string leerArchivo(string ruta){
            //http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
            ifstream in(ruta, ios::in | ios::binary);
            return( string( (istreambuf_iterator<char>(in)), istreambuf_iterator<char>()) );
        }

        Interes crearInteres(string ruta){
            return Interes( leerArchivo(ruta)  );
        }

        bool compararIntereses(Interes& interes1, Interes& interes2){
            return (   (interes1.comparar(interes2))  &&  (interes2.comparar(interes1))  );
        }

        bool compararCategorias(Interes& interes1, Interes& interes2 ){
            return ( interes1.getCategoria() == interes2.getCategoria() );
        }
        bool compararValores(Interes& interes1, Interes& interes2 ){
            return ( interes1.getValor() == interes2.getValor() );
        }
};


TEST_F(InteresesTest, testIniciarInteresDesdeUnStringConElFormatoCorrectoDaUnInteresConLaCategoriaYValorCorrectos){
    Interes interes = this->crearInteres( rutaArchivoDePrueba );
    ASSERT_EQ(categoriaInteresDePrueba, interes.getCategoria());
    ASSERT_EQ(valorInteresDePrueba, interes.getValor());
}


TEST_F(InteresesTest, testCompararUnInteresConOtroQueSeaElMismoDaVerdadero){
    Interes interes1 = this->crearInteres( rutaArchivoDePrueba );
    Interes interes2 = this->crearInteres( rutaArchivoDePrueba );
    ASSERT_TRUE(this->compararIntereses(interes1, interes2));
}

TEST_F(InteresesTest, testCompararUnInteresConOtroQueTengaDiferenteCategoriaDaFalso ){
    Interes interes = this->crearInteres( rutaArchivoDePrueba );
    Interes interesDirenteCategoria = this->crearInteres( rutaArchivoDePruebaConDiferenteCategoria );

    ASSERT_FALSE( this->compararCategorias(interes, interesDirenteCategoria ) );
    ASSERT_TRUE( this->compararValores(interes, interesDirenteCategoria ) );
    ASSERT_FALSE(this->compararIntereses(interes, interesDirenteCategoria));
}


TEST_F(InteresesTest, testCompararUnInteresConOtroQueTengaDiferenteValorDaFalso ){
    Interes interes = this->crearInteres( rutaArchivoDePrueba );
    Interes interesDiferenteValor = this->crearInteres( rutaArchivoDePruebaConDiferenteValor  );

    ASSERT_TRUE( this->compararCategorias(interes, interesDiferenteValor ) );
    ASSERT_FALSE( this->compararValores(interes, interesDiferenteValor ) );
    ASSERT_FALSE(this->compararIntereses(interes, interesDiferenteValor));
}

TEST_F(InteresesTest, testCompararUnInteresConOtroQueTengaDiferenteCategoriaYValorDaFalso ){
    Interes interes = this->crearInteres( rutaArchivoDePrueba );
    Interes interesDiferenteCategoriaYValor = this->crearInteres( rutaArchivoDePruebaConDiferenteCategoriaYValor );

    ASSERT_FALSE( this->compararCategorias(interes, interesDiferenteCategoriaYValor ) );
    ASSERT_FALSE( this->compararValores(interes, interesDiferenteCategoriaYValor ) );
    ASSERT_FALSE(this->compararIntereses(interes, interesDiferenteCategoriaYValor));
}




/*
TEST_F(SesionesDeUsuariosTest, testAgregarUnaSesionDeUsuario){
	sesiones->agregarSesionDe("Usuario","Token");
	ASSERT_TRUE(sesiones->existeSesionDe("Usuario"));
	ASSERT_FALSE(sesiones->validarTokenConUsuario("NotUsuario","JRRTolkien"));
	ASSERT_EW(1,1);
}
*/
