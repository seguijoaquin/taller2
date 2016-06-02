#include "CredencialesDeUsuarios.h"

using namespace std;

CredencialesDeUsuarios::CredencialesDeUsuarios(string ruta){
    this->credenciales = new BaseDeDatos(ruta);
}



bool CredencialesDeUsuarios::validarCredenciales(string usuario, string password){
    return ( (this->existeUsuario(usuario)) && (this->getPasswordDe(usuario) == password) );
}

bool CredencialesDeUsuarios::agregarNuevoUsuario(string usuario, string password){
    if (this->existeUsuario(usuario)){
        return false;
    }
    else{
        this->agregarUsuarioYCredenciales(usuario,password);
        return true;
    }
}

bool CredencialesDeUsuarios::existeUsuario(string usuario){
    return this->credenciales->existe(usuario);
}

string CredencialesDeUsuarios::getPasswordDe(string usuario){
    return this->credenciales->get(usuario);
}

void CredencialesDeUsuarios::agregarUsuarioYCredenciales(string usuario, string password){
    this->credenciales->put(usuario,password);
}

CredencialesDeUsuarios::~CredencialesDeUsuarios(){
    delete this->credenciales;
}
