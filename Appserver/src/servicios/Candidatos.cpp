#include "Candidatos.h"

Candidatos::Candidatos(string ruta){
    this->parejas = new BaseDeDatos(ruta);
}

Candidatos::~Candidatos(){
    delete this->parejas;
}

string Candidatos::armarClaveDeLaPareja(string usuario1, string usuario2){
    if (usuario1 < usuario2){
        return (usuario1 + " " + usuario2);
    }
    else{
        return (usuario2 + " " + usuario1);
    }
}



bool Candidatos::existePareja(string usuario1, string usuario2){
    return this->parejas->existe( this->armarClaveDeLaPareja(usuario1, usuario2) );
}

string Candidatos::obtenerPareja(string usuario1, string usuario2){
    return this->parejas->get( this->armarClaveDeLaPareja(usuario1, usuario2) );
}

void Candidatos::guardarPareja(string usuario1, string usuario2, Pareja* pareja){
    this->parejas->put( this->armarClaveDeLaPareja(usuario1, usuario2), pareja->toString() );
}

void Candidatos::registrarNotificacionAUsuarioSobreCandidato(string usuario, string candidato){
    Pareja* pareja;
    if ( this->existePareja(usuario, candidato) ){
        pareja = new Pareja( obtenerPareja(usuario,candidato) );
    }
    else{
        pareja = new Pareja(usuario,candidato);
    }
    Logger::Instance()->log(INFO, "Se notifica a " + usuario + " sobre el candidato "+candidato);
    pareja->notificarUsuario(usuario);
    this->guardarPareja(usuario, candidato, pareja);
    delete pareja;
}

bool Candidatos::usuarioFueNotificadoSobreElCandidato(string usuario, string candidato){
    if ( this->existePareja(usuario, candidato) ){
        Pareja pareja( this->obtenerPareja(usuario, candidato) );
        return pareja.estaNotificado(usuario);
    }
    else{
        return false;
    }
}

bool Candidatos::usuarioVotaAFavorDe(string usuario1, string usuario2, bool votoAFavor){
    if ( this->existePareja(usuario1, usuario2) ){
        Logger::Instance()->log(INFO, usuario1 + "voto por " + usuario2);
        Pareja pareja( this->obtenerPareja(usuario1, usuario2) );
        pareja.usuarioVota(usuario1, votoAFavor);
        this->guardarPareja(usuario1, usuario2, &pareja);
        return pareja.hayMatch();
    }
    else{
        Logger::Instance()->log(WARNING, usuario1 + " intento votar por un usuario en una Pareja que no existe");
        return false;
    }
}



bool Candidatos::hayMatchEntre(string usuario1, string usuario2){
    if ( this->existePareja(usuario1, usuario2) ){
        Pareja pareja( this->obtenerPareja(usuario1, usuario2) );
        return pareja.hayMatch();
    }
    else{
        return false;
    }
}

