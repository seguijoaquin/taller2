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
    return ( (this->existeSesionDe(usuario)) && ((this->tokensDeSesionesDeUsuario)[usuario].token ==  token) );

}

void SesionesDeUsuarios::agregarSesionDe(string usuario, string token, string tokenGCM){
    this->tokensDeSesionesDeUsuario[usuario].token = token;
    this->tokensDeSesionesDeUsuario[usuario].tokenGCM = tokenGCM;

}


string SesionesDeUsuarios::getTokenGCMDe(string usuario){
    if (this->existeSesionDe(usuario)){
        return this->tokensDeSesionesDeUsuario[usuario].tokenGCM;
    }
    else{
        return "";
    }
}

void SesionesDeUsuarios::eliminarUsuario(string usuario){
    this->tokensDeSesionesDeUsuario.erase(usuario);
}

SesionesDeUsuarios::~SesionesDeUsuarios()
{
    //dtor
}
