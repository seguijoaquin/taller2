#include "SesionesDeUsuarios.h"
using namespace std;

SesionesDeUsuarios::SesionesDeUsuarios()
{
    //ctor
}


bool SesionesDeUsuarios::existeSesionDe(string usuario){
    //if ( this->tokensDeUsuarios->find(ownerIngresado) == this->tokensDeUsuarios->end()){
    if (this->tokensDeSesionesDeUsuario.find(usuario) == this->tokensDeSesionesDeUsuario.end() ){
        return false;
    }
    else{
        return true;
    }
}

bool SesionesDeUsuarios::validarTokenConUsuario(string usuario, string token){
    if (!this->existeSesionDe(usuario) ){
        //Si ni siquiera tiene sesion, mucho menos va a tener token
        return false;
    }
    else{
        if  ( (this->tokensDeSesionesDeUsuario)[usuario] !=  token  ){
            //Aca esta logueado pero los tokens son diferentes
            return false;
        }
        else{
            return true;
        }
    }
}

void SesionesDeUsuarios::agregarSesionDe(string usuario, string token){
    this->tokensDeSesionesDeUsuario[usuario] = token;

}













SesionesDeUsuarios::~SesionesDeUsuarios()
{
    //dtor
}
