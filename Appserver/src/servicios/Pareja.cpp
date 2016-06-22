#include "Pareja.h"

using namespace std;

int votoEnContra = 0;
int votoAFavor = 1;
int votoNoDefinido = 2;
int usuarioNoNotificado = 3;



Pareja::Pareja(string usuario1, string usuario2){

    this->usuario1 = usuario1;
    this->usuario2 = usuario2;

    this->votosDeUsuarios[usuario1] = usuarioNoNotificado;
    this->votosDeUsuarios[usuario2] = usuarioNoNotificado;
}


Pareja::Pareja(string texto){
    istringstream pareja(texto);
    pareja >> this->usuario1;
    pareja >> this->usuario2;

    string votoUsuario;

    pareja >> votoUsuario;
    this->votosDeUsuarios[usuario1] = StringUtil::str2int(votoUsuario);

    pareja >> votoUsuario;
    this->votosDeUsuarios[usuario2] = StringUtil::str2int(votoUsuario);

}

string Pareja::toString(){
    string votoUsuario1 = StringUtil::int2string(this->votosDeUsuarios[usuario1]);
    string votoUsuario2 = StringUtil::int2string(this->votosDeUsuarios[usuario2]);
    string parejaString = this->usuario1 + " " + this->usuario2 + " " + votoUsuario1 + " " + votoUsuario2;

    Logger::Instance()->log(DEBUG, "Pareja toString(): " + parejaString);
    return parejaString;
}

Pareja::~Pareja()
{
    //dtor
}


bool Pareja::existeUsuario(string usuario){
    return ( this->votosDeUsuarios.find(usuario) != this->votosDeUsuarios.end() );
}

void Pareja::usuarioVota(string usuario, bool votoAFavor){
    if (this->existeUsuario(usuario)){
        if (votoAFavor){
            this->votosDeUsuarios[usuario] = votoAFavor;
        }
        else{
            this->votosDeUsuarios[usuario] = votoEnContra;
        }
    }
}

void Pareja::notificarUsuario(string usuario){
    if (this->existeUsuario(usuario)){
        this->votosDeUsuarios[usuario] = votoNoDefinido;
    }
}


bool Pareja::estaNotificado(string usuario){

    return ( ( this->existeUsuario(usuario) ) && (this->votosDeUsuarios[usuario] != usuarioNoNotificado) );
/*
    if (this->existeUsuario(usuario)){
        return this->votosDeUsuarios>[usuario] == usuarioNoNotificado;
    }
    else{
        return false;
    }
*/
}


bool Pareja::estaDefinida(){
    return ( ( (this->votosDeUsuarios[this->usuario1] == votoEnContra) || (this->votosDeUsuarios[this->usuario2] == votoEnContra) ) ||
             ( (this->votosDeUsuarios[this->usuario1] == votoAFavor) && (this->votosDeUsuarios[this->usuario2] == votoAFavor)   ));
}

bool Pareja::hayMatch() {
    return ( (this->votosDeUsuarios[this->usuario1] == votoAFavor) && (this->votosDeUsuarios[this->usuario2] == votoAFavor) );
}


