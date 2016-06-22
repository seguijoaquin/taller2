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
    bool esValido = ( (this->existeSesionDe(usuario)) && ((this->tokensDeSesionesDeUsuario)[usuario].token ==  token) );
    if (!esValido){
        Logger::Instance()->log(WARNING, "Token y Usuario no son validos");
    }
    return esValido;


}

void SesionesDeUsuarios::agregarSesionDe(string usuario, string token, string tokenGCM){
    this->tokensDeSesionesDeUsuario[usuario].token = token;
    this->tokensDeSesionesDeUsuario[usuario].tokenGCM = tokenGCM;
    Logger::Instance()->log(INFO, "Se inicio la sesion de "+ usuario);
}


string SesionesDeUsuarios::getTokenGCMDe(string usuario){
    if (this->existeSesionDe(usuario)){
        return this->tokensDeSesionesDeUsuario[usuario].tokenGCM;
    }
    else{
        Logger::Instance()->log(WARNING, "No se tiene el TokenGCM de "+ usuario);
        return "";
    }
}

void SesionesDeUsuarios::eliminarUsuario(string usuario){
    this->tokensDeSesionesDeUsuario.erase(usuario);
    Logger::Instance()->log(INFO, "Se elimino "+ usuario);
}

SesionesDeUsuarios::~SesionesDeUsuarios()
{
    //dtor
}
