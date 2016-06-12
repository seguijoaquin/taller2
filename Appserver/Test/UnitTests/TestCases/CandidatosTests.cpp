#include <string>
#include <vector>
#include "Candidatos.h"
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

class CandidatosTest : public testing::Test{
	protected:

        string usuario1 = "usuario1";
        string usuario2 = "usuario2";

		virtual void SetUp(){
			candidatos = new Candidatos("./Entorno/CandidatosDePrueba");
		}

		virtual void TearDown(){
			delete candidatos;
            system("../limpiarEntorno.sh");
		}



		/*bool verificarMensajeVacio(Mensajes& mensajes, int indice){
			return ( (mensajes.getEmisor(indice).empty()) && (mensajes.getMensaje(indice).empty()) );
		}
		*/


		Candidatos* candidatos;
};


TEST_F(CandidatosTest, testAlRegistrarLaNotificacionAUnUsuarioSobreElCandidatoElUsuarioQuedaNotificadoPeroElCandidatoNo){
    candidatos->registrarNotificacionAUsuarioSobreCandidato(usuario1,usuario2);
    ASSERT_TRUE( candidatos->usuarioFueNotificadoSobreElCandidato(usuario1, usuario2) );
    ASSERT_FALSE( candidatos->usuarioFueNotificadoSobreElCandidato(usuario2, usuario1) );
}

TEST_F(CandidatosTest, testSiUnUsuarioVotaAFavorDeOtroQueNoVotoSeTieneQueNoHuboMatch){
    candidatos->registrarNotificacionAUsuarioSobreCandidato(usuario1,usuario2);
    bool hayMatch = candidatos->usuarioVotaAFavorDe(usuario1,usuario2,true);
    ASSERT_FALSE(hayMatch);
}

TEST_F(CandidatosTest, testSiDosUsuariosVotanAFavorDelOtroEntoncesHayMatch){
    candidatos->registrarNotificacionAUsuarioSobreCandidato(usuario1,usuario2);
    candidatos->registrarNotificacionAUsuarioSobreCandidato(usuario2,usuario1);

    candidatos->usuarioVotaAFavorDe(usuario1,usuario2,true);
    bool hayMatch = candidatos->usuarioVotaAFavorDe(usuario2,usuario1,true);
    ASSERT_TRUE(hayMatch);
}


TEST_F(CandidatosTest, elVotoDeUsuariosNoNotificadosNoQuedaRegistrado){
    //No se notifica a ninguno de los dos, pero los dos votan positivo por el otro, aun asi no hay match
    candidatos->usuarioVotaAFavorDe(usuario1,usuario2,true);
    bool hayMatch = candidatos->usuarioVotaAFavorDe(usuario2,usuario1,true);
    ASSERT_FALSE(hayMatch);
}




