#include "SesionesDeUsuarios.h"
using namespace std;

SesionesDeUsuarios::SesionesDeUsuarios()
{
    //ctor
}


bool SesionesDeUsuarios::existeSesionDe(string usuario){
    return (this->tokensDeSesionesDeUsuario.find(usuario) != this->tokensDeSesionesDeUsuario.end() );
}

bool SesionesDeUsuarios::validarTokenConUsuario(string usuario, string token){
    return ( (this->existeSesionDe(usuario)) && ((this->tokensDeSesionesDeUsuario)[usuario] ==  token) );

}

void SesionesDeUsuarios::agregarSesionDe(string usuario, string token){
    this->tokensDeSesionesDeUsuario[usuario] = token;

}



SesionesDeUsuarios::~SesionesDeUsuarios()
{
    //dtor
}
