#ifndef CANDIDATOS_H
#define CANDIDATOS_H

#include "Pareja.h"
#include "BaseDeDatos.h"

/** Clase que abstrae la base de datos que contiene
 * la informacion acerca de los candidatos. Y realiza
 * su correspondiente gestion.
 */

class Candidatos
{
    public:
        Candidatos(string ruta);
        virtual ~Candidatos();


        /** Registra que usuario fue notificado sobre el candidato */
        void registrarNotificacionAUsuarioSobreCandidato(string usuario, string candidato);
    
        /** Devuelve True si el usuario ya fue notificado sobre el candidato. False en caso contrario */
        bool usuarioFueNotificadoSobreElCandidato(string usuario, string candidato);

    /** Devuelve True si hay match, es decir, ambos se dieron like. En caso contrario da false */
    bool usuarioVotaAFavorDe(string usuario1, string usuario2, bool votoAFavor);
    
    /** Devuelve true si existe un match entre ambos usuarios, es decir, si ambos se votaron de manera positiva.
     * False en cualquier otra situacion, es decir: a favor + no notificado, a favor + en contra, a favor + valor no emitido.
     */
    bool hayMatchEntre(string usuario1, string usuario2);


    protected:
    

    private:
    
        BaseDeDatos* parejas;
        string armarClaveDeLaPareja(string usuario1, string usuario2);
        bool existePareja(string usuario1, string usuario2);

        string obtenerPareja(string usuario1, string usuario2);
        void guardarPareja(string usuario1, string usuario2, Pareja* pareja);


};

#endif // CANDIDATOS_H
