#include "Usuario.h"

using namespace std;

Usuario::Usuario(string jsonUsuario){
    this->perfil = JsonObject(jsonUsuario);
}

Usuario::~Usuario(){
    //dtor
}



string Usuario::toString(){
    return this->perfil.toString();
}


string Usuario::getEmail(){
    return this->perfil.getString("email");
}

string Usuario::getId(){

}

bool Usuario::tieneInteres(string interes){

}


