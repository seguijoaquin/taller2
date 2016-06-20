#ifndef ADMINISTRADORCANDIDATOS_H
#define ADMINISTRADORCANDIDATOS_H

#include "SharedDataBase.h"
#include "Mensajero.h"
#include "Candidatos.h"
#include "EstadisticasCandidatos.h"

/*!
 *  Se encarga de asignar los posibles matches dependiendo de si se cumplen o no las condiciones
 *  Avisa en caso de match y registra las notificaciones en Candidatos
 *  A los de afuera les permite obtener matches y registrar votos
*/
class AdministradorCandidatos
{
    public:
        AdministradorCandidatos(SharedDataBase* shared, Mensajero* mensajero);
        virtual ~AdministradorCandidatos();
	
	
        void inicializarCandidato(string usuario); /*!< Inicializa las estadisticas de un usuario*/

        //El que pide al candidato es responsable de deletear al Usuario*
        Usuario* buscarCandidatoPara(string usuario); /*!< Devuelve un posible match para el usuario pasado como parametro. Es responsabilidad del que llama a esta funcion liberar la memoria del Usuario entregado. Si el usuario es nullptr significa que ningun candidato cumple con las condiciones*/
  
	void usuarioVotaAFavorDe(string usuario1, string usuario2, bool votoAFavor); /*!< Se registra el voto del usuario1 para el usuario2 y se actualizan las estadisticas */

        bool hayMatchEntre(string usuario1, string usuario2);/*!< Funcion que devuelve verdadero si ambos se votaron favorablemente*/

        bool compararIntereses(Usuario& usuario1, Usuario& usuario2); /*!< Funcion que devuelve verdadero si ambos usuarios tienen al menos un interes en comun*/

    protected:
    private:
        
	//Lo necesita para armar la lista de matches
        SharedDataBase* shared;
        //Lo necesita para notificar los matches
        Mensajero* mensajero;

        Candidatos candidatos = Candidatos("./Candidatos");
        EstadisticasCandidatos estadisticas;
};

#endif // ADMINISTRADORCANDIDATOS_H
