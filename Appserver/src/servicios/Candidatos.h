#ifndef CANDIDATOS_H
#define CANDIDATOS_H

#include "Pareja.h"
#include "BaseDeDatos.h"

class Candidatos
{
    public:
        Candidatos(string ruta);
        virtual ~Candidatos();



        void registrarNotificacionAUsuarioSobreCandidato(string usuario, string candidato);
        bool usuarioFueNotificadoSobreElCandidato(string usuario, string candidato);

        //Puede devolver true o false dependiendo si hay match o no
        //Devuelve true para que el administrador pueda saber si hubo match para mandarle la notificacion al otro
        bool usuarioVotaAFavorDe(string usuario1, string usuario2, bool votoAFavor);


    protected:
    private:
        BaseDeDatos* parejas;
        string armarClaveDeLaPareja(string usuario1, string usuario2);
        bool existePareja(string usuario1, string usuario2);

        string obtenerPareja(string usuario1, string usuario2);
        void guardarPareja(string usuario1, string usuario2, Pareja* pareja);


};

#endif // CANDIDATOS_H
