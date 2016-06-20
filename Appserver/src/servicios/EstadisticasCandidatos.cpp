#include "EstadisticasCandidatos.h"

using namespace std;

const int EstadisticasCandidatos::limiteCandidatos = 3;
const double EstadisticasCandidatos::porcentajeUsuariosPopulares = 0.01;

EstadisticasCandidatos::EstadisticasCandidatos()
{
    //ctor
}

EstadisticasCandidatos::~EstadisticasCandidatos()
{
    //dtor
}

int EstadisticasCandidatos::getCantidadVotosPara(string usuario){
    if (this->existeUsuario(usuario)){
        return this->estadisticasPorUsuario[usuario].cantidadDeVotosPositivos;
    }
    else{
        return 0;
    }
}

string EstadisticasCandidatos::buscarUsuarioPopularConMenosVotos(){
    int votosDeUsuarioPopular = 100000;
    string usuarioPopularConMenosVotos = "";
    for( set<string>::iterator it = this->usuariosPopulares.begin() ; it != this->usuariosPopulares.end(); ++it){
        int votosAux = this->getCantidadVotosPara(*it);
        if ( votosAux < votosDeUsuarioPopular ){
            usuarioPopularConMenosVotos = (*it);
            votosDeUsuarioPopular = votosAux;
        }
    }
    return usuarioPopularConMenosVotos;
}

void EstadisticasCandidatos::contabilizarVotoPara(string usuario){
    if (this->existeUsuario(usuario)){
        this->estadisticasPorUsuario[usuario].cantidadDeVotosPositivos++;
        this->actualizarUsuariosPopulares(usuario);
    }
}

void EstadisticasCandidatos::actualizarUsuariosPopulares(string usuario){
    if (!this->usuarioEsPopular(usuario)){
        string usuarioPopularConMenosVotos = this->buscarUsuarioPopularConMenosVotos();
        if ( (usuarioPopularConMenosVotos != "") && (this->getCantidadVotosPara(usuario) > this->getCantidadVotosPara(usuarioPopularConMenosVotos)) ){
            this->usuariosPopulares.erase(usuarioPopularConMenosVotos);
            this->usuariosPopulares.insert(usuario);
        }
    }
}

bool EstadisticasCandidatos::usuarioEsPopular(string usuario){
    return (this->usuariosPopulares.find(usuario) != this->usuariosPopulares.end());
}


void EstadisticasCandidatos::contabilizarCandidatoPara(string usuario){
    if (this->existeUsuario(usuario)){
        this->estadisticasPorUsuario[usuario].cantidadDeCandidatosPedidos++;
    }
}

bool EstadisticasCandidatos::usuarioSuperoLimiteDeCandidatos(string usuario){
    if (!this->existeUsuario(usuario)){
        return false;
    }
    else{
        return ( this->estadisticasPorUsuario[usuario].cantidadDeCandidatosPedidos >= limiteCandidatos );
    }
}


bool EstadisticasCandidatos::existeUsuario(string usuario){
    return (this->estadisticasPorUsuario.find(usuario) != this->estadisticasPorUsuario.end() );
}

void EstadisticasCandidatos::inicializarUsuario(string usuario){

    if( !this->existeUsuario(usuario)){

        Estadisticas estadisticas;
        estadisticas.cantidadDeCandidatosPedidos = 0;
        estadisticas.cantidadDeVotosPositivos = 0;
        this->estadisticasPorUsuario[usuario] = estadisticas;

        if ( floor(this->estadisticasPorUsuario.size()*porcentajeUsuariosPopulares) > this->usuariosPopulares.size()){
            //buscar al usuario con mas votos que no este en la lista de los populares y agregarlo a la lista de los populares
            string usuarioConMasVotos = "";
            for( map<string, Estadisticas>::iterator it = this->estadisticasPorUsuario.begin() ; it != this->estadisticasPorUsuario.end(); ++it){
                string usuarioAux = it->first;
                if ( ( this->getCantidadVotosPara(usuarioAux) >=  this->getCantidadVotosPara(usuarioConMasVotos)) &&
                     ( !this->usuarioEsPopular(usuarioAux) ) ){
                    usuarioConMasVotos = usuarioAux;
                }
            }
            if (usuarioConMasVotos != ""){
                this->usuariosPopulares.insert(usuarioConMasVotos);
            }
        }
    }
}
