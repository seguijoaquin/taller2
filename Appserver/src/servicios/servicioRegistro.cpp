#include "servicioRegistro.h"

//PARA PROBAR SI LAS CONEXIONES OUTBOUNDS SE MANEJAN EN UN MISMO THREAD
//int servicioRegistro::tiempo = 0;


/*servicioRegistro::servicioRegistro(mg_mgr* manager, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales){
    this->manager = manager;
    this->mensajeHTTP = mensajeHTTP;
    this->usuariosRegistrados = credenciales;
    this->codigoRespuesta = 0;
    //Para testear
    this->espera = 0;
    this->atenderRegistro();
}
*/

servicioRegistro::servicioRegistro(ManejadorDeConexiones* manejadorDeConexiones, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales){
    //this->manager = manager;
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

    //struct mg_connection* conexionParaRegistrarse;

    //Aca tal vez no se mande inmediantamente, tal vez la respuesta no le llegue en seguida, lo bloqueo y espero a que llegue la respuesta
    //Refactorizar: agregarle un timeout???
    //Refactorizar: darDeAlta(...) ademas debe agregarlo al archivo
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
//    conexionParaRegistrarse = mg_connect(this->manager,"t2shared.herokuapp.com:80", this->handlerResgistro); //SI
//    mg_set_protocol_http_websocket(conexionParaRegistrarse);
//
//    conexionParaRegistrarse->user_data = this;
//    this->esperandoRespuesta = true;
//
//    mg_printf(conexionParaRegistrarse, "POST /users/ HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\nContent-Length: %lu\r\nContent-Type: application/json\r\n\r\n%s", bodyJson.length(), bodyJson.c_str()); //Funciona


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


//void servicioRegistro::handlerResgistro(struct mg_connection* conexion, int evento, void* ev_data){
//
//    struct mbuf* recvBuffer = &(conexion->recv_mbuf);
//    struct mbuf* sendBuffer = &(conexion->send_mbuf);
//
//
//    switch (evento) {
//        case MG_EV_CONNECT:
//            {
//                cout<<"EL REGISTRO SE CONECTO AL SERVER\n";
//                cout<<"El indice de CONNECT es: "<<conexion<<"\n";
//                //PARA PROBAR SI LAS CONEXIONES OUTBOUNDS SE MANEJAN EN UN MISMO THREAD
//                /*int i = 0;
//                while (i < 5){ //con 10seg y dos conexiones tira segmentation faults
//                    i++;
//                    tiempo++;
//                    cout<<"Tiempo en la conexion con direccion "<<conexion<<" "<<tiempo<<" segundos\n";
//                    sleep(1);
//                }*/
//            }
//            break;
//
//        case MG_EV_HTTP_REPLY:
//            {
//                cout<<"EL SERVER TIRO EL REPLY\n";
//                //NOTA: castear el ev_data a http_message* se puede hacer aca porque el caso MG_EV_HTTP_REPLY garantiza que haya un http_message en el ev_data
//                //TODO: Aca es en donde se tiene que setear el codigo de retorno
//                ((servicioRegistro*)conexion->user_data)->setCodigoResuesta( ((http_message*) ev_data)->resp_code  );
//                //((servicioRegistro*)conexion->user_data)->desbloquear( ((http_message*) ev_data)->resp_code );
//                printf("Lo que hay en el buffer DEL REGISTRO en RECV es:\n%.*s\n", (int)recvBuffer->len,recvBuffer->buf);
//                mbuf_remove(recvBuffer, recvBuffer->len);
//                //Esto es porque ya no tiene sentido que esa conexion siga activa luego de recibir la respuesta
//                conexion->flags |= MG_F_CLOSE_IMMEDIATELY;
//            }
//            break;
//        case MG_EV_SEND:
//            {
//                cout<<"Se envio algo\n";
//                printf("Lo que hay en el buffer DEL REGISTRO en SEND es:\n%.*s\n", (int)sendBuffer->len,sendBuffer->buf);
//            }
//            break;
//        case MG_EV_CLOSE:
//            {
//                //cout<<"SE CERRO LA CONEXION\n";
//                //Deberia setearse arriba el codigo y aca nada mas ->desbloquear()
//                ((servicioRegistro*)conexion->user_data)->desbloquear();
//                //cout<<"SE CERRO LA CONEXION a los "<<tiempo<<" segundos "<<"El indice de CLOSE es: "<<conexion<<"\n";
//            }
//            break;
//    }
//}


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
