#include "servicioRegistro.h"

servicioRegistro::servicioRegistro(mg_mgr* manager, http_message* mensajeHTTP, map<string,string>* listaUsuarios ){
    this->manager = manager;
    this->mensajeHTTP = mensajeHTTP;
    this->listaUsuarios = listaUsuarios;
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
    //Refactorizar: poner el localhost:8001 como constante


    //NUEVO
    //Refactorizar: Ahora esta devolviendo el json nada mas, cambiarle el nombre
    //El mensaje para resgistrarse va a tirar solo el mensaje json
    string mensajeParaRegistrarse = crearMensajeParaAlta(usuario);
    char* headers = "Content-Type: application/json\r\n";
    conexionParaRegistrarse = mg_connect_http(this->manager, this->handlerResgistro, "t2shared.herokuapp.com/users/", headers, mensajeParaRegistrarse.c_str());
    //mg_printf(conexionParaRegistrarse,"%s",mensajeParaRegistrarse.c_str());

    //Sabiendo como funciona el mg_connect_http esto (pasarle user data a la conexion) puede no funcionar si el poll se hace antes de asignar la data


    //Refactorizar: esto se tendria que armar en una funcion usando el jsoncpp
    //Si le borro el primer mensaje enviado despues de conectarse puede servir
    //Idea para la sincronizacion: tal vez pueda evitar que se mande en el CONNECT, le borro el buffer en el CONNECT
    //Esto fue para sincronizarlos, lo tengo que reformular
/*    this->bloqueado = true;
    while (this->bloqueado){
        sleep(1);
    }
 */

    //Aca tal vez no se mande inmediantamente, tal vez la respuesta no le llegue en seguida, lo bloqueo y espero a que llegue la respuesta
    //
    this->bloqueado = true;
    //Refactorizar: agregarle un timeout???
 /*   cout<<"VA a esperar en el while\n";
    while (this->bloqueado){
        sleep(1);
    }
*/
    //Refactorizar: darDeAlta(...) ademas debe agregarlo al archivo
    //REFACTORIZAR:
    //WARNING: REFACTORIZAR: MUY MUY IMPORTANTE: ahora no se estan sincronizando el mensaje del shared con el mensaje
    //El problema esta en que seria un thread detacheado el que corre el handler, tal vez en un thread hacer se cree la conexion y que mientras la conexion sea diferente de nula que espera hasta que sea nula (o sea, que espere hasta que se haya muerto la conexion)
    //Igual no recibiria el codigo de error,
    //IDEA: PONERLE EL FLAG DE "TODAVIA NO LO MANDES" en la MG_EV_CONNECT y agrego this a la user data, despues me bloqueo, le saco el flag y que la conexion me desbloquee, pasandome el codigo de salida, y el mensaje
    //EDIT: ese flag parece no existir mas, otra posible solucion seria tener dos managers uno con MT el otro no pero creo que lo haria mas lento todo....
    //La version de ver si es NULL podria servir pero no obtendria el codigo
    (*(this->listaUsuarios))[usuario] = password;
    this->respuesta = "HTTP/1.1 200 Se puedo registrar el usuario "+ usuario + " con contrasenia " + password +"\r\n\r\n";
}


void servicioRegistro::desbloquear(){
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
                //((servicioRegistro*)conexion->user_data)->desbloquear();
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
