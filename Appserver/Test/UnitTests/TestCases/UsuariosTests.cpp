#include "Usuario.h"
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
using namespace std;


class UsuarioTests : public testing::Test{
	protected:

		virtual void SetUp(){

		}

		virtual void TearDown(){

		}


        string direccion = "./ArchivosTests/ArchivosUsuariosTests/";
		string archivoUsuarioDePrueba = "Usuario.txt";
        string emailDePrueba = "email@prueba.com";
        int idSharedDePrueba = 5;
        //Debe tener los mismos intereses que el archivo del usuario de prueba
        string archivoInteresesDelUsuario = "InteresesDelUsuario.txt";

        string leerArchivo(string nombre){
            //http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
            string ruta = direccion + nombre;
            ifstream in(ruta, ios::in | ios::binary);
            return( string( (istreambuf_iterator<char>(in)), istreambuf_iterator<char>()) );
        }

        Usuario getUsuarioDePrueba(){
            return Usuario( leerArchivo(archivoUsuarioDePrueba) );
        }

        bool compararConLosInteresesEsperados(ListadoDeIntereses& listado){
            ListadoDeIntereses interesesEsperados;
            interesesEsperados.agregarIntereses( leerArchivo(archivoInteresesDelUsuario) );

            bool sonIguales;
            if (listado.size() != interesesEsperados.size() ){
                sonIguales = false;
            }
            else{
                sonIguales = true;
                int i = 1;
                while ( (i <= listado.size()) && sonIguales){
                    Interes interesActual = listado.getInteres(i);
                    sonIguales = interesesEsperados.tieneInteres(interesActual);
                    i++;
                }
            }
            return sonIguales;
        }
};


TEST_F(UsuarioTests, testSeCreaUnUsuarioYSeObtienenElEmailYIdEsperados){
    Usuario usuario = getUsuarioDePrueba();

    ASSERT_EQ(this->emailDePrueba, usuario.getEmail());
    ASSERT_EQ(this->idSharedDePrueba, usuario.getId());
}


TEST_F(UsuarioTests, testSeCreaUnUsuarioYSeComparanLosInteresesConLosInteresesEsperados){
    Usuario usuario = getUsuarioDePrueba();
    ListadoDeIntereses listado = usuario.getIntereses();
    ASSERT_TRUE(this->compararConLosInteresesEsperados(listado));
}

