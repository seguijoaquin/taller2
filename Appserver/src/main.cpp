#include "mongoose/mongoose.h"
#include <iostream>
#include <fstream>
#include <map>
#include <thread>
#include "servicioRegistro.h"
#include "servicioLogin.h"

using namespace std;

//const char* PATHLOGIN = "/login";
//ESTO LO VOY A TENER QUE GUARDAR EN OTRO LUGAR O LO MANEJO CON ROCKSDB
map<string,string> listaUsuarios;
struct mg_mgr manager;

bool compararMetodoHTTP(struct http_message* mensajeHTTP, char* metodo){

    if (mg_vcmp(&(mensajeHTTP->method), metodo) == 0){
        return true;
    }
    else{
        return false;
    }

}

bool compararUriHTTP(struct http_message* mensajeHTTP, char* uri){

    if (mg_vcmp(&(mensajeHTTP->uri), uri) == 0){
        return true;
    }
    else{
        return false;
    }
}

string atenderMesajeHTTP(struct http_message* mensajeHTTP){
    string respuesta;

    if (compararMetodoHTTP(mensajeHTTP,"POST")){
        //respuesta = atenderPOST(mensajeHTTP);
    }
    else if (compararMetodoHTTP(mensajeHTTP,"GET")){
        if (compararUriHTTP(mensajeHTTP, "/login")){
            servicioLogin logginer(mensajeHTTP, &listaUsuarios);
            respuesta = logginer.getRespuesta();
            cout<<"RESPUESTA DEL SERVICIO LOGIN:\n"<<respuesta<<"\n";
        }
    }
    else if (compararMetodoHTTP(mensajeHTTP, "PUT")){
        if (compararUriHTTP(mensajeHTTP, "/registro")){
            servicioRegistro registrador(&manager, mensajeHTTP, &listaUsuarios);
            respuesta = registrador.getRespuesta();
            cout<<"RESPUESTA DEL SERVICIO REGISTRO:\n"<<respuesta<<"\n";
        }
    }
    return respuesta;
}

static void handlerServer(struct mg_connection* conexion, int evento, void* ev_data) {

    struct mbuf* recvBuffer = &(conexion->recv_mbuf);
    struct mbuf* sendBuffer = &(conexion->send_mbuf);

    /*if (evento!=0){
        cout<<"EL evento de no se quien es: "<<evento<<" \n";
    }*/

    switch (evento) {
        case MG_EV_HTTP_REPLY:
            {
                cout<<"Esto se dispara?\n";
                printf("Lo que hay en el buffer es:\n%.*s\n", recvBuffer->len,recvBuffer->buf);
                mbuf_remove(recvBuffer, recvBuffer->len);
            }
        break;
        case MG_EV_HTTP_REQUEST:
            {
                struct http_message* mensajeHTTP = (struct http_message *) ev_data;

                printf("Mensaje de llegada al server:\n%.*s\n", recvBuffer->len,recvBuffer->buf);

                string respuesta = atenderMesajeHTTP(mensajeHTTP);

                //cout<<"Respuesta:\n"<<respuesta<<"\n";
                //mg_printf(conexion,"HTTP/1.1 202 Mensaje de informacion sobre el vnbjsdfo\r\n\r\nbody sfdvdfb\0");//, respuesta);
                //respuesta = "HTTP/1.1 200 Se logueo correctamente\r\n\Token:1234567899\r\n\r\nbody\0";

                cout<<"ESTO ES LO QUE SE VA PRINTEAR EN EL BUFFER\n"<<respuesta<<"\n";

                mg_printf(conexion,"%s",respuesta.c_str());
                printf("Lo que hay en el sendBuffer del HTTP_REQUEST es:\n%.*s\n", sendBuffer->len,sendBuffer->buf);
                conexion->flags |= MG_F_SEND_AND_CLOSE;
                //Refactorizar: limpiarElBuffer(...)
                mbuf_remove(recvBuffer, recvBuffer->len);
            }
            break;
        case MG_EV_SEND:
            {
                cout<<"SE MANDO EL BUFFER\n";
                //printf("Lo que hay en el buffer es:\n%s\n\0", sendBuffer->len,sendBuffer->buf);
            }
            break;

        case MG_EV_CONNECT:
            {
                cout<<"SE CONECTO AL SISTEMA, le escribo aca lo que tiene que mandar\n";
                //mbuf_remove(sendBuffer, sendBuffer->len);
            }
            break;
        /*WARNING IMPORTANTE: SI ESTA EL CASE MG_EV_RECV ENTONCES SE USA ESTE EN VEZ DEL MG_EV_HTTP_REPLY
        case MG_EV_RECV:
            {
                cout<<"Se recibio algo\n";
                printf("Lo que hay en el buffer es:\n%.*s\n", recvBuffer->len,recvBuffer->buf);
                mbuf_remove(recvBuffer, recvBuffer->len);
                //mg_printf(conexion, "GET /users/18 HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\nContent-Length: 0\r\n\r\n");
            }
            break;
        */
        case MG_EV_CLOSE:
            {
                cout<<"SE CERRO LA CONEXION\n";
            }
            break;
        default:
                /*if (evento!=0){
                    cout<<"EL evento de no se quien es: "<<evento<<" \n";
                }*/

            break;
    }
}

int main(void) {

    struct mg_connection* conexionListening;

    //Refactorizar: iniciarManager(...);
    mg_mgr_init(&manager, NULL);
    // Se bindea al localhost 8000 y se guarda la conexion
    conexionListening = mg_bind(&manager, "8000", handlerServer);
    // Configuro al manager como http
    mg_set_protocol_http_websocket(conexionListening);
    //Cada conexion que entra se va a manejar en un thread deatacheado distinto usando el handlerServer
    //SOLUCION TEMPORAL AL PROBLEMA DEL CMAKE
    //mg_enable_multithreading(conexionListening);
    /////////////////////////////////////////////////////////////////////

    //Esto asi no funciona, sin el :5000 me tira conexion NULL
    //mg_connection* nc = mg_connect(&manager,"t2shared.herokuapp.com:5000", handlerServer); //SI
    //mg_set_protocol_http_websocket(nc);
    //mg_printf(nc, "GET /users/18 HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\nContent-Length: 0\r\n\r\n");

    //PARA ARRIBA NO FUNCIONA
    //mg_connection* nc = mg_connect_http(&manager, handlerServer, "t2shared.herokuapp.com/users/18", NULL, NULL); //SI SI SI ES ESTA, THIS IS THE ONE
    /*if (nc == NULL){
        cout<<"corta\n";
    }*/


    //Refactorizar: cargarDatosDeUsuario(....)
    fstream archivoLogin;
    archivoLogin.open("login.txt");
    string usuarioActual;
    string passwordActual;
    while (archivoLogin>>usuarioActual){
        archivoLogin>>passwordActual;
        listaUsuarios[usuarioActual] = passwordActual;
    }
    //O PONERLO AL FINAL PORQUE SI ALGUNO SE REGISTRA SE VA A TENER QUE VOLVER A ABRIR
    archivoLogin.close();


    for (;;) {
        mg_mgr_poll(&manager, 1000);
    }


    mg_mgr_free(&manager);
    return 0;

}
