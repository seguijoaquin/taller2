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
    JsonObject user;
    user.agregarClaveValor("user",this->perfil);
    return user.toString();
}


string Usuario::getEmail(){
    return this->email;
}

int Usuario::getId(){
    return this->perfil.getInt("id");
}

ListadoDeIntereses Usuario::getIntereses(){
    ListadoDeIntereses intereses;
    intereses.agregarIntereses(this->perfil.toString());
    return intereses;
}

Localizacion Usuario::getLocalizacion(){
    return Localizacion(this->perfil.getJsonObject("location").toString());
}

void Usuario::actualizarLocalizacion(Localizacion& localizacion){
    JsonObject posicion = localizacion.toJsonObject();
    this->perfil.agregarClaveValor("location", posicion);
}



