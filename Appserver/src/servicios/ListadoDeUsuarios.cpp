#include "ListadoDeUsuarios.h"

using namespace std;

ListadoDeUsuarios::ListadoDeUsuarios(){
}

ListadoDeUsuarios::~ListadoDeUsuarios(){
    /*
    for (map<string, Usuario>::iterator it = this->usuarios.begin(); it != this->usuarios.end(); ++it){
        delete (it->second);
    }
    */
}

void ListadoDeUsuarios::agregarUsuarios(string jsonListadoUsuarios){
    Logger::Instance()->log(INFO, "Se agregan usuarios al listado de usuarios");
    JsonObject jsonListado(jsonListadoUsuarios);
    JsonArray arrayUsuarios = jsonListado.getJsonArray("users");

    string jsonUsuario;
    while (arrayUsuarios>>jsonUsuario){
        this->agregarUsuario(jsonUsuario);
    }
}

void ListadoDeUsuarios::agregarUsuario(string jsonUsuario){
    //Usuario* nuevoUsuario = new Usuario(jsonUsuario);
    //string emailNuevoUsuario = nuevoUsuario->getEmail();

    //Si el usuario existia, entonces deleteo el anterior y lo actualizo
    /*
    if (this->usuarios.find(emailNuevoUsuario) != this->usuarios.end()){
        delete this->usuarios[emailNuevoUsuario];
    }
    this->usuarios[emailNuevoUsuario] = nuevoUsuario;
    */

    Usuario nuevoUsuario(jsonUsuario);
    string emailNuevoUsuario = nuevoUsuario.getEmail();
    this->usuarios[emailNuevoUsuario] = nuevoUsuario;

}


Usuario ListadoDeUsuarios::getUsuario(string usuario){
    if (this->usuarioExiste(usuario)){
        return ((this->usuarios[usuario]));
    }
    else{
        Logger::Instance()->log(WARNING, "El listado de usuarios devuelve un Usuario vacio");
        return Usuario();
    }
}

bool ListadoDeUsuarios::usuarioExiste(string usuario){
    return (  this->usuarios.find(usuario) != this->usuarios.end()    );
}



void ListadoDeUsuarios::irAlInicio(){
    this->itUsuarioActual = this->usuarios.begin();
}
bool ListadoDeUsuarios::getSiguienteUsuario(Usuario& usuario){

    if ( this->itUsuarioActual != this->usuarios.end() ){
        usuario = (itUsuarioActual->second);
        ++itUsuarioActual;
        return true;
    }
    else{
        return false;
    }
}

