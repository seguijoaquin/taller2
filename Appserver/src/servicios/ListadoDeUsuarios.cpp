#include "ListadoDeUsuarios.h"

using namespace std;

ListadoDeUsuarios::ListadoDeUsuarios()
{
    //ctor
}

ListadoDeUsuarios::~ListadoDeUsuarios(){
    for (set<Usuario*>::iterator it = this->usuarios.begin(); it != this->usuarios.end(); ++it){
        delete (*it);
    }
}

void ListadoDeUsuarios::agregarUsuarios(string jsonListadoUsuarios){
    JsonObject jsonListado(jsonListadoUsuarios);
    JsonArray arrayUsuarios = jsonListado.getJsonArray("users");

    string jsonUsuario;
    while (arrayUsuarios>>jsonUsuario){
        this->agregarUsuario(jsonUsuario);
    }
}

void ListadoDeUsuarios::agregarUsuario(string jsonUsuario){
    this->usuarios.insert(new Usuario(jsonUsuario));
}

