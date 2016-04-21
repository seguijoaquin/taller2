#include "AtendedorHTTP.h"

/*AtendedorHTTP::AtendedorHTTP(http_message* mensajeHTTP, rocksdb::DB* credencialesUsuarios, mg_mgr* manager){
    this->mensajeHTTP = mensajeHTTP;
    this->credencialesUsuarios = credencialesUsuarios;
    this->manager = manager;
    this->atenderMesajeHTTP();
}
*/


AtendedorHTTP::AtendedorHTTP(http_message* mensajeHTTP){
    this->mensajeHTTP = mensajeHTTP;
    this->atenderMesajeHTTP();
}


ServicioALanzar AtendedorHTTP::getServicioALanzar(){
    return this->servicioALanzar;
}





/*string AtendedorHTTP::getRespuesta(){
    return this->respuesta;
}
*/

void AtendedorHTTP::atenderMesajeHTTP(){

    //Verificar permisos

    if (compararMetodoHTTP(mensajeHTTP,"POST")){
        //respuesta = atenderPOST(mensajeHTTP);
    }
    else if (compararMetodoHTTP(mensajeHTTP,"GET")){
        if (compararUriHTTP(mensajeHTTP, "/login")){
            //servicioLogin logginer(mensajeHTTP, &listaUsuarios);
            //servicioLogin logginer(mensajeHTTP, this->credencialesUsuarios);
            //this->respuesta = logginer.getRespuesta();
            //cout<<"RESPUESTA DEL SERVICIO LOGIN:\n"<<this->respuesta<<"\n";
            this->servicioALanzar = LANZAR_SERVICIO_LOGIN;
        }
    }
    else if (compararMetodoHTTP(mensajeHTTP, "PUT")){
        if (compararUriHTTP(mensajeHTTP, "/registro")){
            //servicioRegistro registrador(&manager, mensajeHTTP, &listaUsuarios);
            //servicioRegistro registrador(this->manager, mensajeHTTP, this->credencialesUsuarios);
            //this->respuesta = registrador.getRespuesta();
            //cout<<"RESPUESTA DEL SERVICIO REGISTRO:\n"<<this->respuesta<<"\n";
            this->servicioALanzar = LANZAR_SERVICIO_REGISTRO;
        }
    }
}



bool AtendedorHTTP::compararMetodoHTTP(http_message* mensajeHTTP, string metodo){

    if (mg_vcmp(&(mensajeHTTP->method), StringUtil::stringToChar(metodo)) == 0){
        return true;
    }
    else{
        return false;
    }
}

bool AtendedorHTTP::compararUriHTTP(http_message* mensajeHTTP, string uri){
    if (mg_vcmp(&(mensajeHTTP->uri), StringUtil::stringToChar(uri)) == 0){
        return true;
    }
    else{
        return false;
    }
}




AtendedorHTTP::~AtendedorHTTP()
{
    //dtor
}
