#include "servicioRegistro.h"

servicioRegistro::servicioRegistro(mg_mgr* manager, http_message* mensajeHTTP, map<string,string>* listaUsuarios ){
    this->manager = manager;
    this->mensajeHTTP = mensajeHTTP;
    this->listaUsuarios = listaUsuarios;
    this->codigoRespuesta = 0;
    this->atenderRegistro();
}


void servicioRegistro::atenderRegistro(){
    mg_str* headerUsuario = mg_get_http_header(mensajeHTTP, "Usuario");
    mg_str* headerPassword = mg_get_http_header(mensajeHTTP, "Password");

    string usuarioIngresado(headerUsuario->p,headerUsuario->len);
    string passwordIngresado(headerPassword->p,headerPassword->len);

    //Refactorizar: buscarUsuario()
    if (this->listaUsuarios->find(usuarioIngresado) == listaUsuarios->end()){
        //El NOMBRE de usuario NO existe y se puede inscribir
        this->realizarRegistro(usuarioIngresado,passwordIngresado);
    }
    else{
        //EL nombre SI existe, tengo que rechazarlo
        //Refactorizar
        this->respuesta = "HTTP/1.1 400 Usuario existente\r\n\r\n";
    }
}

void servicioRegistro::realizarRegistro(string usuario, string password){

    struct mg_connection* conexionParaRegistrarse;

    //Aca tal vez no se mande inmediantamente, tal vez la respuesta no le llegue en seguida, lo bloqueo y espero a que llegue la respuesta
    //Refactorizar: agregarle un timeout???
    //Refactorizar: darDeAlta(...) ademas debe agregarlo al archivo
    //REFACTORIZAR:
    //Problema para mas adelante: si llegan dos PUTs iguales, puede que se registren los dos, tal vez lo pueda resolver el atendedorHTTP con una lista de "usuarios que esperan ser registrados", otra seria tener esa lista como variable statica, todas las instancias la pueden ver, checkeo esa lista ademas de la lista de usuarios ya registrados para saber si el nombre esta usado o no y devuelvo un error adecuado
    //Para probar esto se podria agregar un sleep en el ev handler para simular que tarda mucho en inscribirse.

    //Refactorizar: Ahora esta devolviendo el json nada mas, cambiarle el nombre o hacer que cree el mensaje completo
    string bodyJson = crearMensajeParaAlta(usuario);
    conexionParaRegistrarse = mg_connect(this->manager,"t2shared.herokuapp.com:80", this->handlerResgistro); //SI
    mg_set_protocol_http_websocket(conexionParaRegistrarse);

    conexionParaRegistrarse->user_data = this;
    this->bloqueado = true;
    mg_printf(conexionParaRegistrarse, "POST /users/ HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\nContent-Length: %i\r\nContent-Type: application/json\r\n\r\n%s", bodyJson.length(), bodyJson.c_str()); //Funciona

    while (this->bloqueado){
        sleep(1);
        cout<<"esta esperando...\n";
    }

    //Refactorizar: CODIGO_ALTA_CORRECTA.... etc
    if (this->codigoRespuesta == 201){
        (*(this->listaUsuarios))[usuario] = password;
        this->respuesta = "HTTP/1.1 201 Se puedo registrar el usuario "+ usuario + " con contrasenia " + password +"\r\n\r\n";
    }
    else{
        //Cambiarlo para diferentes errores
        this->respuesta = "HTTP/1.1 500 ERROR no se pudo registrar\r\n\r\n";
    }

}


void servicioRegistro::desbloquear(int codigoRespuesta){
    this->codigoRespuesta = codigoRespuesta;
    this->bloqueado = false;
}

void servicioRegistro::handlerResgistro(struct mg_connection* conexion, int evento, void* ev_data){

    struct mbuf* recvBuffer = &(conexion->recv_mbuf);
    struct mbuf* sendBuffer = &(conexion->send_mbuf);


    switch (evento) {
        case MG_EV_CONNECT:
            {
                cout<<"EL REGISTRO SE CONECTO AL SERVER\n";
                //mbuf_remove(sendBuffer, sendBuffer->len);
                printf("Lo que hay en el buffer DEL REGISTRO en CONNECT es:\n%.*s\n", sendBuffer->len,sendBuffer->buf);
                //((servicioRegistro*)conexion->user_data)->desbloquear();
            }
            break;

        case MG_EV_HTTP_REPLY:
            {
                cout<<"EL SERVER TIRO EL REPLY\n";
                //Refactorizar esto, ver alguna forma para sincronizar el registrador con el mensaje del shared.....

                //NOTA: castear el ev_data a http_message* se puede hacer aca porque el caso MG_EV_HTTP_REPLY garantiza que haya un http_message en el ev_data
                ((servicioRegistro*)conexion->user_data)->desbloquear( ((http_message*) ev_data)->resp_code );
                printf("Lo que hay en el buffer DEL REGISTRO en RECV es:\n%.*s\n", recvBuffer->len,recvBuffer->buf);
                mbuf_remove(recvBuffer, recvBuffer->len);
                //Esto es porque ya no tiene sentido que esa conexion siga activa luego de recibir la respuesta
                conexion->flags |= MG_F_CLOSE_IMMEDIATELY;
            }
            break;
        case MG_EV_SEND:
            {
                cout<<"Se envio algo\n";
                printf("Lo que hay en el buffer DEL REGISTRO en SEND es:\n%.*s\n", sendBuffer->len,sendBuffer->buf);
            }
            break;
        case MG_EV_CLOSE:
            {
                cout<<"SE CERRO LA CONEXION\n";
            }
            break;
    }
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
    return bodyJson;
}


string servicioRegistro::getRespuesta(){
    return this->respuesta;
}

servicioRegistro::~servicioRegistro()
{
    //dtor
}
