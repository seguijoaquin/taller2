#include "BaseDeDatos.h"

using namespace std;

string VALOR_DE_CLAVE_NO_ENCONTRADA = "";

BaseDeDatos::BaseDeDatos(string ruta){
    //https://github.com/facebook/rocksdb/issues/957 diferentes alternativas para guardar datos, tambien se podria usar un json...
    rocksdb::Options options;
    options.create_if_missing = true;
    //Lanzar errores si fuera necesario
    //WARNING: no se si las opciones pueden perder scope antes de que se destruya la base de datos, si no puede--> options variable privada
    rocksdb::Status status = rocksdb::DB::Open(options, ruta, &(this->datos));
    Logger::Instance()->log(INFO, "Se abre una base de datos en " + ruta);
}

BaseDeDatos::~BaseDeDatos(){
    delete this->datos;
}


void BaseDeDatos::put(string clave, string valor){
    this->datos->Put(rocksdb::WriteOptions(),clave,valor);
}

string BaseDeDatos::get(string clave){
    //NO se modifica el contenido de la varaiable valor si no se encuentra la clave
    string valor = VALOR_DE_CLAVE_NO_ENCONTRADA;
    this->datos->Get(rocksdb::ReadOptions(), clave, &valor );
    if (!this->existe(clave)){
        Logger::Instance()->log(WARNING, "Clave " + clave + " no encontrada");
    }
    return valor;
}

bool BaseDeDatos::existe(string clave){
    string aux;
    rocksdb::Status estado = this->datos->Get(rocksdb::ReadOptions(), clave, &aux );
    return (!estado.IsNotFound());
}

void BaseDeDatos::eliminar(string clave){
    this->datos->Delete(rocksdb::WriteOptions(),clave);
}
