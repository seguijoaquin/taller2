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

}

string Usuario::getId(){

}

bool Usuario::tieneInteres(string interes){

}

void Usuario::agregarPosibleMatch(Usuario* usuario){
    this->posiblesMatches.push(usuario);
}

Usuario* Usuario::getPosibleMatch(){
    if (!this->posiblesMatches.empty()){
        Usuario* posibleMatch = this->posiblesMatches.top();
        this->posiblesMatches.pop();
        return posibleMatch;
    }
    else{
        return nullptr;
    }
}


