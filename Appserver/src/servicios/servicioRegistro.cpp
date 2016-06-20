#include "servicioRegistro.h"

/*servicioRegistro::servicioRegistro(ManejadorDeConexiones* manejadorDeConexiones, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales){
    this->manejadorDeConexiones = manejadorDeConexiones;
    this->mensajeHTTP = mensajeHTTP;
    this->usuariosRegistrados = credenciales;

    //Para testear
    this->espera = 0;
    this->atenderRegistro();
}*/

servicioRegistro::servicioRegistro(SharedDataBase* shared, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales, AdministradorCandidatos* administradorCandidatos){
    this->shared = shared;
    this->mensajeHTTP = mensajeHTTP;
    this->usuariosRegistrados = credenciales;
    this->administradorCandidatos = administradorCandidatos;
    this->atenderRegistro();
}


void servicioRegistro::atenderRegistro(){

    //string usuarioIngresado = this->mensajeHTTP.getHeader("Usuario");
    string passwordIngresado = this->mensajeHTTP.getHeader("Password");
    Usuario usuarioIngresado(this->mensajeHTTP.getBody());

    if (this->usuariosRegistrados->existeUsuario(getClaveParaRegistrarse(usuarioIngresado))){
        RespuestaDelRegistro* respuestaRegistro = new RespuestaDelRegistro();
        respuestaRegistro->setRespuestaUsuarioExistente();
        this->respuesta = respuestaRegistro;
    }
    else{
        this->realizarRegistro(usuarioIngresado,passwordIngresado);
    }
}

//void servicioRegistro::realizarRegistro(string usuario, string password){
void servicioRegistro::realizarRegistro(Usuario& usuario, string password){

    //REFACTORIZAR:

    /*Problema para mas adelante: si llegan dos PUTs iguales, puede que se registren los dos, tal vez lo pueda
    resolver el atendedorHTTP con una lista de "usuarios que esperan ser registrados", otra seria tener esa lista como
    variable statica, todas las instancias la pueden ver, checkeo esa lista ademas de la lista de usuarios ya registrados
    para saber si el nombre esta usado o no y devuelvo un error adecuado
    */
    //Para probar esto se podria agregar un sleep en el ev handler para simular que tarda mucho en inscribirse.


    //Refactorizar: Ahora esta devolviendo el json nada mas, cambiarle el nombre o hacer que cree el mensaje completo
    //TODO: agarar todos los errores

    //ESTO YA NO SIRVE PORQUE PASO USUARIOS
    //string bodyJson = crearMensajeParaAlta(usuario);

    //POR AHORA SE PASA EL BODY DEL JSON, DEBERIA


    //Refactorizar: CODIGO_ALTA_CORRECTA.... etc
    //if (respustaShared.getCodigo() == 201){


    //int idShared = this->shared->registrarUsuario(bodyJson);
    int idShared = this->shared->registrarUsuario(usuario);
    RespuestaDelRegistro* respuestaRegistro = new RespuestaDelRegistro();
    if ( idShared > -1 ){
        this->usuariosRegistrados->agregarNuevoUsuario(getClaveParaRegistrarse(usuario),password, idShared);
        this->administradorCandidatos->inicializarCandidato(getClaveParaRegistrarse(usuario));


        respuestaRegistro->setRespuestaRegistroCorrecto();

        //this->respuesta = "HTTP/1.1 201 Se pudo registrar el usuario\r\n\r\n";
    }
    else{
        //Cambiarlo para diferentes errores
        respuestaRegistro->setRespuestaErrorDelSharedServer();
        //this->respuesta = "HTTP/1.1 503 Error del server\r\n\r\n";
    }
    this->respuesta = respuestaRegistro;

}


string servicioRegistro::getClaveParaRegistrarse(Usuario& usuario){
    return usuario.getEmail();
}




/*
void servicioRegistro::agregarInteresAlJarray(string interes, string valor, JsonArray& jarray ){
    JsonObject interesJobj;
    interesJobj.agregarClaveValor("category", interes);
    interesJobj.agregarClaveValor("value", valor);
    jarray.agregar(interesJobj);
}


string servicioRegistro::crearMensajeParaAlta(string usuario){

    JsonObject mensajeAltaJobj;
    JsonObject usuarioJobj;
    JsonObject ubicacionJobj;
    JsonArray interesesJarray;

    usuarioJobj.agregarClaveValor("name", usuario);
    usuarioJobj.agregarClaveValor("alias", "alias1");

    usuarioJobj.agregarClaveValor("email", usuario);
    usuarioJobj.agregarClaveValor("sex", "M");
    usuarioJobj.agregarClaveValor("edad", "22");

    agregarInteresAlJarray("music/band","radiohead", interesesJarray);
    agregarInteresAlJarray("music/band","pearl jam", interesesJarray);
    agregarInteresAlJarray("outdoors","running", interesesJarray);
    usuarioJobj.agregarClaveValor("interests", interesesJarray);

    ubicacionJobj.agregarClaveValor("latitude", "-121.45356");
    ubicacionJobj.agregarClaveValor("longitude","46.51119");
    usuarioJobj.agregarClaveValor("location", ubicacionJobj);

    mensajeAltaJobj.agregarClaveValor("user",usuarioJobj);

    string bodyJson = mensajeAltaJobj.toString();


    //mensajeAlta = "POST /users HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\nContent-Type: application/json\r\n\r\n" + bodyJson;
    //cout<<"EL MENSAJE DE ALTA ES:\n\n\n"<<mensajeAlta<<"\n\n\n";

    //return mensajeAlta;
    cout<<"EL JSON ES: "<<bodyJson<<"\n\n";
    return bodyJson;
}
*/

servicioRegistro::~servicioRegistro()
{
    //dtor
}
