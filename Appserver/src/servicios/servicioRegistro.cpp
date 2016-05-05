#include "servicioRegistro.h"

servicioRegistro::servicioRegistro(ManejadorDeConexiones* manejadorDeConexiones, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales){
    this->manejadorDeConexiones = manejadorDeConexiones;
    this->mensajeHTTP = mensajeHTTP;
    this->usuariosRegistrados = credenciales;
    this->codigoRespuesta = 0;
    //Para testear
    this->espera = 0;
    this->atenderRegistro();
}


void servicioRegistro::atenderRegistro(){

    string usuarioIngresado = this->mensajeHTTP.getHeader("Usuario");
    string passwordIngresado = this->mensajeHTTP.getHeader("Password");

    if (this->usuariosRegistrados->existeUsuario(usuarioIngresado)){
        this->respuesta = "HTTP/1.1 400 Usuario existente\r\n\r\n";
    }
    else{
        this->realizarRegistro(usuarioIngresado,passwordIngresado);
    }
}

void servicioRegistro::realizarRegistro(string usuario, string password){


    //Aca tal vez no se mande inmediantamente, tal vez la respuesta no le llegue en seguida, lo bloqueo y espero a que llegue la respuesta
    //Refactorizar: agregarle un timeout???
    //REFACTORIZAR:

    /*Problema para mas adelante: si llegan dos PUTs iguales, puede que se registren los dos, tal vez lo pueda
    resolver el atendedorHTTP con una lista de "usuarios que esperan ser registrados", otra seria tener esa lista como
    variable statica, todas las instancias la pueden ver, checkeo esa lista ademas de la lista de usuarios ya registrados
    para saber si el nombre esta usado o no y devuelvo un error adecuado
    */
    //Para probar esto se podria agregar un sleep en el ev handler para simular que tarda mucho en inscribirse.


    //Refactorizar: Ahora esta devolviendo el json nada mas, cambiarle el nombre o hacer que cree el mensaje completo
    //TODO: agarar todos los errores
    string bodyJson = crearMensajeParaAlta(usuario);
    this->manejadorDeConexiones->iniciarConexionComoCliente("POST", "/users/",bodyJson,"80", "t2shared.herokuapp.com", this);
    while (this->esperandoRespuesta){
        sleep(1);
        this->espera++;
        //cout<<"esta esperando...\n";
    }

    //Refactorizar: CODIGO_ALTA_CORRECTA.... etc
    if (this->codigoRespuesta == 201){
        this->usuariosRegistrados->agregarNuevoUsuario(usuario,password);
        this->respuesta = "HTTP/1.1 201 Se pudo registrar el usuario\r\n\r\n";
    }
    else{
        //Cambiarlo para diferentes errores
        this->respuesta = "HTTP/1.1 503 Error del server\r\n\r\n";
    }

}



void servicioRegistro::setCodigoResuesta(int codigo){
    this->codigoRespuesta = codigo;
}

void servicioRegistro::esperarRespuesta(){
    this->esperandoRespuesta = true;
}

void servicioRegistro::desbloquear(){
    this->esperandoRespuesta = false;
    cout<<"Espero: "<<this->espera<<"\n";
}

void servicioRegistro::agregarInteresAlJarray(Json::Value interes, Json::Value valor, Json::Value& jarray ){
    Json::Value interesJobj;
    interesJobj["category"] = interes;
    interesJobj["value"] = valor;
    jarray.append(interesJobj);
}

string servicioRegistro::crearMensajeParaAlta(string usuario){
    Json::Value mensajeAltaJobj;
    Json::Value usuarioJobj;
    Json::Value ubicacionJobj;
    Json::Value interesesJarray;

    usuarioJobj["name"] = usuario;
    usuarioJobj["alias"] = "alias1";
    usuarioJobj["email"] = "hard_coded@email.com";

    agregarInteresAlJarray("music/band","radiohead", interesesJarray);
    agregarInteresAlJarray("music/band","pearl jam", interesesJarray);
    agregarInteresAlJarray("outdoors","running", interesesJarray);
    usuarioJobj["interests"] = interesesJarray;

    ubicacionJobj["latitude"] = "-121.45356";
    ubicacionJobj["longitude"] = "46.51119";
    usuarioJobj["location"] = ubicacionJobj;

    mensajeAltaJobj["user"] = usuarioJobj;


    Json::StyledWriter styledWriter;
    //string mensajeAlta;// = styledWriter.write(mensajeAltaJobj);

    string bodyJson = styledWriter.write(mensajeAltaJobj);


    //mensajeAlta = "POST /users HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\nContent-Type: application/json\r\n\r\n" + bodyJson;
    //cout<<"EL MENSAJE DE ALTA ES:\n\n\n"<<mensajeAlta<<"\n\n\n";

    //return mensajeAlta;
    cout<<"EL JSON ES: "<<bodyJson<<"\n\n";
    return bodyJson;
}


string servicioRegistro::getRespuesta(){
    return this->respuesta;
}

servicioRegistro::~servicioRegistro()
{
    //dtor
}
