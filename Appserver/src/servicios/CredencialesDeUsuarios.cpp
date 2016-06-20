#include "CredencialesDeUsuarios.h"

using namespace std;

CredencialesDeUsuarios::CredencialesDeUsuarios(string ruta){
    this->credenciales = new BaseDeDatos(ruta);
}



bool CredencialesDeUsuarios::validarCredenciales(string usuario, string password){
    return ( (this->existeUsuario(usuario)) && (this->getPasswordDe(usuario) == password) );
}

bool CredencialesDeUsuarios::agregarNuevoUsuario(string usuario, string password, int idShared){
    if (this->existeUsuario(usuario)){
        return false;
    }
    else{
        this->agregarUsuarioYCredenciales(usuario,password,idShared);
        return true;
    }
}

bool CredencialesDeUsuarios::existeUsuario(string usuario){
    return this->credenciales->existe(usuario);
}

string CredencialesDeUsuarios::getPasswordDe(string usuario){
    //return this->credenciales->get(usuario);
    JsonObject datos(this->credenciales->get(usuario));
    return datos.getString("password");
}

int CredencialesDeUsuarios::getIDSharedDe(string usuario){
    JsonObject datos(this->credenciales->get(usuario));
    return datos.getInt("idShared");
}


void CredencialesDeUsuarios::agregarUsuarioYCredenciales(string usuario, string password, int idShared){
    JsonObject datos;
    datos.agregarClaveValor("password",password);
    datos.agregarClaveValor("idShared",idShared);
    this->credenciales->put(usuario,datos.toString());
}


void CredencialesDeUsuarios::eliminiarUsuario(string usuario){
    this->credenciales->eliminar(usuario);
}


CredencialesDeUsuarios::~CredencialesDeUsuarios(){
    delete this->credenciales;
}
