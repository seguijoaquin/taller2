#include "AtendedorHTTP.h"


AtendedorHTTP::AtendedorHTTP(MensajeHTTPRequest mensajeHTTP, SesionesDeUsuarios* sesionesDeUsuarios){
    this->mensajeHTTPRequest = mensajeHTTP;
    this->sesionesDeUsuarios = sesionesDeUsuarios;
    this->atenderMesajeHTTP();
}


ServicioALanzar AtendedorHTTP::getServicioALanzar(){
    return this->servicioALanzar;
}



void AtendedorHTTP::atenderMesajeHTTP(){

    if (this->tienePermiso()){
        if (compararMetodoHTTP("POST")){
            if (compararUriHTTP("/chat")){
                this->servicioALanzar = LANZAR_SERVICIO_CHAT;
            }
        }
        else if (compararMetodoHTTP("GET")){
            if (compararUriHTTP("/login")){
                this->servicioALanzar = LANZAR_SERVICIO_LOGIN;
            }
            else if (compararUriHTTP("/mensajes")){
                this->servicioALanzar = LANZAR_SERVICIO_MENSAJES;
            }
            else if (compararUriHTTP("/test")){
                this->servicioALanzar = LANZAR_SERVICIO_TEST;
            }
        }
        else if (compararMetodoHTTP("PUT")){
            if (compararUriHTTP("/registro")){
                this->servicioALanzar = LANZAR_SERVICIO_REGISTRO;
            }
        }
        else if (compararMetodoHTTP("DELETE")){
            this->servicioALanzar = LANZAR_SERVICIO_CERRAR;
        }
    }
    else{
        this->servicioALanzar = LANZAR_SERVICIO_SIN_PERMISO;
    }
}

bool AtendedorHTTP::tienePermiso(){

    //Verificar permisos
    if (!(this->mensajeHTTPRequest.tieneHeader("Owner"))){
        //No tiene owner, entonces puede acceder cualquiera
        return true;
    }
    else{
        /*Si el servicio al que estoy entrando tiene owner, entonces me tengo que fijar los tokens (si no tiene owner como el login o el
          registro, entonces ni me fijo si tiene token, puede acceder cualquiera)
        */
        //Aca me tengo que fijar si Owner y Token coinciden

        //Me podria fijar si el token no es nulo, depende de si la comunicacion cliente-appserver tiene que ser robusta


        string ownerIngresado = this->mensajeHTTPRequest.getHeader("Owner");
        string tokenIngresado = this->mensajeHTTPRequest.getHeader("Token");

        //Despues se podria ver el tema de los que se permite que vean el recurso de otra persona, pero que tenga permiso (tal vez haya que guardar los usuarios que tengan permiso)



        //Refactorizar: TODO, IMPORTANTE, WARNING, ETC, ETC ACA SE PUEDE PONER QUE DIRECTAMENTE LAS SESION DE USUARIO ME DIGA SI TIENE PERMISO O NO
        //AHORA validarTokenConUsuario ESTA HACIENDO LO MISMO QUE LO DE ACA ABAJO JUNTO



        //if ( this->tokensDeUsuarios->find(ownerIngresado) == this->tokensDeUsuarios->end()){
        if ( !(this->sesionesDeUsuarios->existeSesionDe(ownerIngresado))){
            //significaria que el owner ingresado no se logueo recientemente (o no esta logueado si NO le ponemos timer al token)
            /*Si el owner ni siquiera tiene un token asignado, entonces mucho menos va a estar logueado, entonces no se deberia
             poder acceder a sus datos (por ahora, despues hay que ver los casos en que se pueda ver el perfil de otro como
             "invitado" en vez de como "owner"
            */
            return false;
        }
        else{
            //Refactorizar: TODO, IMPORTANTE, IMPORTANT, WARNING, HERE, ESTO SE PODRIA SIMPLIFICAR PASANDO ESTA LOGICA A SesionesDeUsuarios
            if  ( this->sesionesDeUsuarios->validarTokenConUsuario(ownerIngresado, tokenIngresado) ){
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

    if (this->mensajeHTTPRequest.getMetodo() == metodo){
        return true;
    }
    else{
        return false;
    }
}

bool AtendedorHTTP::compararUriHTTP(string uri){

    if (this->mensajeHTTPRequest.getURI() == uri){
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
