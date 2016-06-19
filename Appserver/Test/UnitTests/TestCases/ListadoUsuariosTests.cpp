#include "ListadoDeUsuarios.h"
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
using namespace std;


class ListadoDeUsuariosTest : public testing::Test{
	protected:

        string leerArchivo(string nombre){
            //http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
            string ruta = direccion + nombre;
            ifstream in(ruta, ios::in | ios::binary);
            return( string( (istreambuf_iterator<char>(in)), istreambuf_iterator<char>()) );
        }

		virtual void SetUp(){

		}

		virtual void TearDown(){

		}


        string direccion = "./ArchivosTests/ArchivosListadoDeUsuariosTests/";
		string archivoDePrueba = "ListadoDeUsuarios.txt";
        int tamanioListado = 3;

		string sufijoEmailUsuariosDelListado = "usuario@usuario.com";
		string sufijoArchivoUsuarioEsperado = "interesesUsuario.txt";

        string archivoConUsuariosRepetidos = "ListadoUsuariosRepetidos.txt";
        string emailRepetido = "email@repetido.com";
        int idPrimerUsuarioRepetido = 10;
        int idSegundoUsuarioRepetido = 37;
        int idUltimoUsuarioRepetido = 25;

        string usuarioInexistente = "usuario@NoExiste";

        void inicializarListadoDePrueba(ListadoDeUsuarios& listado){
            listado.agregarUsuarios(leerArchivo(archivoDePrueba));
        }

        void inicializarListadoConUsuariosRepetidos(ListadoDeUsuarios& listado){
            listado.agregarUsuarios(leerArchivo(archivoConUsuariosRepetidos));
        }


        bool compararConUsuarioEsperado( Usuario& usuario){

            int id = usuario.getId();
            Usuario usuarioEsperado( leerArchivo(to_string(id) + sufijoArchivoUsuarioEsperado) );
            return compararUsuarios(usuario, usuarioEsperado);
        }

        bool compararUsuarios(Usuario& usuario1, Usuario& usuario2){
            bool sonIguales = ( ( usuario1.getEmail() == usuario2.getEmail()) && (usuario1.getId() == usuario2.getId()) );

            ListadoDeIntereses interesesUsuario1 = usuario1.getIntereses();
            ListadoDeIntereses interesesUsuario2 = usuario2.getIntereses();

            if ( (!sonIguales) || (interesesUsuario1.size() != interesesUsuario2.size() ) ){
                sonIguales = false;
            }
            else{
                sonIguales = true;
                int i = 1;
                while ( (i <= interesesUsuario1.size()) && sonIguales){
                    Interes interesActual = interesesUsuario1.getInteres(i);
                    sonIguales = interesesUsuario2.tieneInteres(interesActual);
                    i++;
                }
            }
            return sonIguales;
        }
};


TEST_F(ListadoDeUsuariosTest, testAgregarUsuariosAPartirDeUnStringConUnListadoDeUsuariosConElFormatoCorrectoAgregaALosUsuarios){
    ListadoDeUsuarios listado;
    this->inicializarListadoDePrueba(listado);

    for (int i= 1; i <= this->tamanioListado; i++){
        //Me fijo si estan todos los usuarios del listado
        string email = to_string(i) + this->sufijoEmailUsuariosDelListado;
        Usuario usuario = listado.getUsuario(email);
        ASSERT_TRUE( this->compararConUsuarioEsperado(usuario) );
    }
}

TEST_F(ListadoDeUsuariosTest, testSiElListadoTieneDosOMasUsuariosConElMismoEmailElUnicoUsuarioQueQuedaEnElListadoEsElUltimoDeLaLista){
    ListadoDeUsuarios listado;
    this->inicializarListadoConUsuariosRepetidos(listado);

    Usuario usuario = listado.getUsuario(emailRepetido);
    ASSERT_NE(idPrimerUsuarioRepetido, usuario.getId());
    ASSERT_NE(idSegundoUsuarioRepetido, usuario.getId());
    ASSERT_EQ(idUltimoUsuarioRepetido, usuario.getId());
}


TEST_F(ListadoDeUsuariosTest, testPedirUnUsuarioQueNoEsteEnElListadoDevuelveUnUsuarioVacio){
    ListadoDeUsuarios listado;
    this->inicializarListadoDePrueba(listado);

    Usuario usuario = listado.getUsuario(usuarioInexistente);
    ASSERT_EQ("", usuario.getEmail());
    ASSERT_EQ(0, usuario.getId());

    ListadoDeIntereses intereses = usuario.getIntereses();
    ASSERT_EQ(0, intereses.size());
}

TEST_F(ListadoDeUsuariosTest, testRecorrerElListadoDeusuarios){
    ListadoDeUsuarios listado;
    this->inicializarListadoDePrueba(listado);

    listado.irAlInicio();
    Usuario usuario;
    while(listado.getSiguienteUsuario(usuario)){
        ASSERT_TRUE( this->compararConUsuarioEsperado(usuario) );
    }
}

TEST_F(ListadoDeUsuariosTest, testSeVaAlInicioDelListadoParObtenerAlMismoUsuario){
    ListadoDeUsuarios listado;
    this->inicializarListadoDePrueba(listado);

    Usuario usuario1, usuario2;
    listado.irAlInicio();
    listado.getSiguienteUsuario(usuario1);
    listado.irAlInicio();
    listado.getSiguienteUsuario(usuario2);
    ASSERT_TRUE( this->compararUsuarios(usuario1, usuario2) );

}



