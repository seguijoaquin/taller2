#include "mongoose/mongoose.h"
#include <iostream>
#include <fstream>
#include <map>
#include <thread>
#include "servicioRegistro.h"
#include "servicioLogin.h"


using namespace std;


/*  CON ESTO ESTUVE PROBANDO SI HAY MULTITHREADING EN LAS CONEXIONES OUTBOUND
int tiempo;
*/

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

    cout<<"Conexion en el main direccion: "<<conexion<<"-----------------------\n";

    switch (evento) {
        case MG_EV_HTTP_REPLY:
            {
                cout<<"Esto se dispara?\n";
                printf("Lo que hay en el buffer es:\n%.*s\n", recvBuffer->len,recvBuffer->buf);
                mbuf_remove(recvBuffer, recvBuffer->len);
                //conexion->flags |= MG_F_CLOSE_IMMEDIATELY;
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
                /*  CON ESTO ESTUVE PROBANDO SI HAY MULTITHREADING EN LAS CONEXIONES OUTBOUND
                cout<<"El indice de CONNECT es: "<<(int)(conexion->user_data)<<"\n";
                //mbuf_remove(sendBuffer, sendBuffer->len);
                int i = 0;
                while (i < 10){
                    i++;
                    tiempo++;
                    cout<<"Tiempo en la conexion nro "<<(int)conexion->user_data<<" "<<tiempo<<" segundo\n";
                    sleep(1);
                }
                */
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

                cout<<"SE CERRO LA CONEXION en el main\n";// a los "<<tiempo<<" segundos\n";
                /*  CON ESTO ESTUVE PROBANDO SI HAY MULTITHREADING EN LAS CONEXIONES OUTBOUND
                cout<<"El indice de CLOSE es: "<<(int)conexion->user_data<<"\n";
                */

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
    mg_enable_multithreading(conexionListening);
    /////////////////////////////////////////////////////////////////////

    //Esto asi no funciona, sin el :5000 me tira conexion NULL
    //EDIT: puerto :80, en vez de :5000 y funciona
    //Con esta forma
/*  CON ESTO ESTUVE PROBANDO SI HAY MULTITHREADING EN LAS CONEXIONES OUTBOUND
    mg_connection* nc = mg_connect(&manager,"t2shared.herokuapp.com:80", handlerServer); //SI
    mg_set_protocol_http_websocket(nc);
    //mg_printf(nc, "GET /users/18 HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\nContent-Length: 0\r\n\r\n"); //Funciona
    mg_printf(nc, "GET /users/18 HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\n\r\n"); //Funciona


    mg_connection* nc2 = mg_connect(&manager,"t2shared.herokuapp.com:80", handlerServer); //SI
    mg_set_protocol_http_websocket(nc2);
    mg_printf(nc2, "GET /users/42 HTTP/1.1\r\nHost: t2shared.herokuapp.com\r\n\r\n"); //Funcio


    tiempo = 0;

//Le pongo user data y veo que pasa....
    nc->user_data = (void*) 1;
    nc2->user_data = (void*) 2;
*/

    //mg_printf(nc, "GET /users/18 HTTP/1.1\r\n\r\n"); //NO funciona, conclusion: necesita si o si el host
    //mg_printf(nc, "GET https://t2shared.herokuapp.com/users/18 HTTP/1.1\r\n\r\n"); // Tmapoco

    //Con esta forma se puede mandar un GET o un POST de una
    //mg_connection* nc = mg_connect_http(&manager, handlerServer, "t2shared.herokuapp.com/users/18", NULL, NULL);
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
        //cout<<"POLL----------------------------------------------------\n";
    }


    mg_mgr_free(&manager);
    return 0;

}
