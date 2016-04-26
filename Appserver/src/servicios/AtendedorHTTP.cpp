#include "AtendedorHTTP.h"


AtendedorHTTP::AtendedorHTTP(http_message* mensajeHTTP, map<string,string>* tokensDeUsuarios){
    this->mensajeHTTP = mensajeHTTP;
    this->tokensDeUsuarios = tokensDeUsuarios;
    this->atenderMesajeHTTP();
}


ServicioALanzar AtendedorHTTP::getServicioALanzar(){
    return this->servicioALanzar;
}



void AtendedorHTTP::atenderMesajeHTTP(){

    if (this->tienePermiso()){
        if (compararMetodoHTTP("POST")){
            //respuesta = atenderPOST(mensajeHTTP);
        }
        else if (compararMetodoHTTP("GET")){
            if (compararUriHTTP("/login")){
                this->servicioALanzar = LANZAR_SERVICIO_LOGIN;
            }
        }
        else if (compararMetodoHTTP("PUT")){
            if (compararUriHTTP("/registro")){
                this->servicioALanzar = LANZAR_SERVICIO_REGISTRO;
            }
        }
    }
    else{
        this->servicioALanzar = LANZAR_SERVICIO_SIN_PERMISO;
    }
}

bool AtendedorHTTP::tienePermiso(){

    //Verificar permisos
    //Esto tambien podria ponerse en un archivo "Utilities" porque tambien lo usa el servicioLogin
    mg_str* headerOwner = mg_get_http_header(this->mensajeHTTP, "Owner");

    if (headerOwner == NULL ){
        //No tiene owner, entonces puede acceder cualquiera
        return true;
    }
    else{
        /*Si el servicio al que estoy entrando tiene owner, entonces me tengo que fijar los tokens (si no tiene owner como el login o el
          registro, entonces ni me fijo si tiene token, puede acceder cualquiera)
        */
        //Aca me tengo que fijar si Owner y Token coinciden
        mg_str* headerToken = mg_get_http_header(this->mensajeHTTP, "Token");
        //Me podria fijar si el token no es nulo, depende de si la comunicacion cliente-appserver tiene que ser robusta

        //Refactorizar: otra vez esta funcion se repite en ServicioLogin, podria ponerla en "Utilities"
        string ownerIngresado(headerOwner->p,headerOwner->len);
        string tokenIngresado(headerToken->p,headerToken->len);

        //Despues se podria ver el tema de los que se permite que vean el recurso de otra persona, pero que tenga permiso (tal vez haya que guardar los usuarios que tengan permiso)


        if ( this->tokensDeUsuarios->find(ownerIngresado) == this->tokensDeUsuarios->end()){
            //significaria que el owner ingresado no se logueo recientemente (o no esta logueado si NO le ponemos timer al token)
            /*Si el owner ni siquiera tiene un token asignado, entonces mucho menos va a estar logueado, entonces no se deberia
             poder acceder a sus datos (por ahora, despues hay que ver los casos en que se pueda ver el perfil de otro como
             "invitado" en vez de como "owner"
            */
            return false;
        }
        else{
            if  ( (*(this->tokensDeUsuarios))[ownerIngresado] !=  tokenIngresado  ){
                //NO tiene permiso,
                return false;
            }
            else{
                //Tiene permiso
                return true;
            }
        }
    }








}

bool AtendedorHTTP::compararMetodoHTTP( string metodo){

    if (mg_vcmp(&(this->mensajeHTTP->method), StringUtil::stringToChar(metodo)) == 0){
        return true;
    }
    else{
        return false;
    }
}

bool AtendedorHTTP::compararUriHTTP(string uri){
    if (mg_vcmp(&(this->mensajeHTTP->uri), StringUtil::stringToChar(uri)) == 0){
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
