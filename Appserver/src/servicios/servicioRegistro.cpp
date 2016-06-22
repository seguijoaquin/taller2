#include "servicioRegistro.h"

servicioRegistro::servicioRegistro(SharedDataBase* shared, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales, AdministradorCandidatos* administradorCandidatos){
    Logger::Instance()->log(INFO, "Se crea el Servicio de Registro");
    this->shared = shared;
    this->mensajeHTTP = mensajeHTTP;
    this->usuariosRegistrados = credenciales;
    this->administradorCandidatos = administradorCandidatos;
    this->atenderRegistro();
}


void servicioRegistro::atenderRegistro(){

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


    int idShared = this->shared->registrarUsuario(usuario);
    RespuestaDelRegistro* respuestaRegistro = new RespuestaDelRegistro();
    if ( idShared > -1 ){
        this->usuariosRegistrados->agregarNuevoUsuario(getClaveParaRegistrarse(usuario),password, idShared);
        this->administradorCandidatos->inicializarCandidato(getClaveParaRegistrarse(usuario));
        respuestaRegistro->setRespuestaRegistroCorrecto();
    }
    else{
        //Cambiarlo para diferentes errores
        respuestaRegistro->setRespuestaErrorDelSharedServer();
    }
    this->respuesta = respuestaRegistro;

}


string servicioRegistro::getClaveParaRegistrarse(Usuario& usuario){
    return usuario.getEmail();
}


servicioRegistro::~servicioRegistro()
{
    //dtor
}
