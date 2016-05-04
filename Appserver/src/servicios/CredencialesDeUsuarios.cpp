#include "CredencialesDeUsuarios.h"

using namespace std;

CredencialesDeUsuarios::CredencialesDeUsuarios(string ruta){
    //https://github.com/facebook/rocksdb/issues/957 diferentes alternativas para guardar datos, tambien se podria usar un json...
    rocksdb::Options options;
    options.create_if_missing = true;
    //Lanzar errores si fuera necesario
    //WARNING: no se si las opciones pueden perder scope antes de que se destruya la base de datos, si no puede--> options variable privada
    rocksdb::Status status = rocksdb::DB::Open(options, ruta, &(this->credenciales));
}



bool CredencialesDeUsuarios::validarCredenciales(string usuario, string password){
    string passwordGuardado;
    rocksdb::Status estado = this->credenciales->Get(rocksdb::ReadOptions(), usuario, &passwordGuardado );
    if (estado.IsNotFound()){
        return false;
    }
    else{
        if(passwordGuardado == password){
            return true;
        }
        else{
            return false;
        }
    }
}

bool CredencialesDeUsuarios::agregarNuevoUsuario(string usuario, string password){
    if (this->existeUsuario(usuario)){
        return false;
    }
    else{
        this->credenciales->Put(rocksdb::WriteOptions(),usuario,password);
        return true;
    }

}

bool CredencialesDeUsuarios::existeUsuario(string usuario){
    string aux;
    rocksdb::Status estado = this->credenciales->Get(rocksdb::ReadOptions(), usuario, &aux );
    if(  estado.IsNotFound() ){
        //El NOMBRE de usuario NO existe
        return false;
    }
    else{
        //EL nombre SI existe
        return true;
    }
}


CredencialesDeUsuarios::~CredencialesDeUsuarios(){
    delete this->credenciales;
}
