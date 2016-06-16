#include "Usuario.h"

using namespace std;

Usuario::Usuario(){

}

Usuario::Usuario(string jsonUsuario){
    this->perfil = JsonObject(jsonUsuario).getJsonObject("user");
    this->email = this->perfil.getString("email");
}

Usuario::~Usuario(){
    //dtor
}



string Usuario::toString(){
    return this->perfil.toString();
}


string Usuario::getEmail(){
    return this->email;
}

string Usuario::getId(){
    return this->perfil.getString("id");
}

ListadoDeIntereses Usuario::getIntereses(){
    ListadoDeIntereses intereses;
    intereses.agregarIntereses(this->perfil.toString());
    return intereses;
}




