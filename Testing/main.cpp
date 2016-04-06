#include "mongoose.h"
#include <iostream>
#include <fstream>
#include <map>
#include "atendedorGET.h"

using namespace std;

//const char* PATHLOGIN = "/login"; //LA PASO AL atendedorGET.h
//ESTO LO VOY A TENER QUE GUARDAR EN OTRO LUGAR O LO MANEJO CON ROCKSDB
map<string,string> listaUsuarios;



char* atenderPOST(struct http_message* mensajeHTTP){

/*  char nombre[100], password[100];

    //Esto va a ser con un JSON
    mg_get_http_var(&mensajeHTTP->body, "\"usuario\"", nombre, sizeof(nombre));
    mg_get_http_var(&mensajeHTTP->body, "password", password, sizeof(password));

    //cout<<"NOMBRE:"<<nombre<<"\n";
    //cout<<"PASSWORD:"<<nombre<<"\n";
*/
    /*
    mensajeHTTP->resp_code = 200;
    mensajeHTTP->resp_status_msg = mg_mk_str("Se logueo el usuario, se envia el token");
    */

    char* respuesta = "HTTP/1.1 200 Se logueo el usuario, se envia respuesta al POST\r\n\r\nbodybodybodybodybody";

    return respuesta;

}


char* atenderMesajeHTTP(struct http_message* mensajeHTTP){

   /* printf("Metodo:\n%.*s\n", mensajeHTTP->method.len,mensajeHTTP->method.p);
    printf("URI:\n%.*s\n",mensajeHTTP->uri.len, mensajeHTTP->uri.p);
    printf("Version del protocolo:\n%.*s\n",mensajeHTTP->proto.len,mensajeHTTP->proto.p);
    printf("Header[0]:Valor[0]:\n%.*s:%.*s\n", mensajeHTTP->header_names[0].len, mensajeHTTP->header_names[0].p, mensajeHTTP->header_values[0].len,mensajeHTTP->header_values[0].p);
    printf("Header[1]:Valor[1]:\n%.*s:%.*s\n", mensajeHTTP->header_names[1].len, mensajeHTTP->header_names[1].p, mensajeHTTP->header_values[1].len,mensajeHTTP->header_values[1].p);
    printf("Header[1]:Valor[1]:\n%.*s:%.*s\n", mensajeHTTP->header_names[2].len, mensajeHTTP->header_names[2].p, mensajeHTTP->header_values[2].len,mensajeHTTP->header_values[2].p);
    printf("Header[1]:Valor[1]:\n%.*s:%.*s\n", mensajeHTTP->header_names[3].len, mensajeHTTP->header_names[3].p, mensajeHTTP->header_values[3].len,mensajeHTTP->header_values[3].p);
    printf("Header[1]:Valor[1]:\n%.*s:%.*s\n", mensajeHTTP->header_names[4].len, mensajeHTTP->header_names[4].p, mensajeHTTP->header_values[4].len,mensajeHTTP->header_values[4].p);
    printf("Body:\n%s\n", mensajeHTTP->body.p);
*/

    printf("mensaje entero:\n%s\n", mensajeHTTP->message.p);
    char* respuesta;

    //Refactorizar: Podria hacer una funcion "compararMetodo(mensajeHttP,POST/GET/ETC")
    if (mg_vcmp(&(mensajeHTTP->method), "POST") == 0){
        respuesta = atenderPOST(mensajeHTTP);
    }
    else if (mg_vcmp(&(mensajeHTTP->method), "GET") == 0){
        cout<<"ENTA A atenderGET\n";
        respuesta = atenderGET(mensajeHTTP);
        cout<<"RESPUESTA DEL GET:\n"<<respuesta<<"\n";
    }

    return respuesta;

}

static void ev_handler(struct mg_connection* conexion, int evento, void* ev_data) {


    struct mbuf* recvBuffer = &(conexion->recv_mbuf);
    struct mbuf* sendBuffer = &(conexion->send_mbuf);

    //cout<<"Evento:"<<evento<<"\n";


    switch (evento) {
        case MG_EV_HTTP_REQUEST:
            {

                struct http_message* mensajeHTTP = (struct http_message *) ev_data;

                char* respuesta = atenderMesajeHTTP(mensajeHTTP);


                //cout<<"Respuesta:\n"<<respuesta<<"\n";
                //mg_printf(conexion,"HTTP/1.1 202 Mensaje de informacion sobre el vnbjsdfo\r\n\r\nbody sfdvdfb\0");//, respuesta);
                //respuesta = "HTTP/1.1 200 Se logueo correctamente\r\n\Token:1234567899\r\n\r\nbody\0";

                cout<<"ESTO ES LO QUE SE VA PRINTEAR EN EL BUFFER\n"<<respuesta<<"\n";

                mg_printf(conexion,"%s",respuesta);

                //printf("Lo que hay en el buffer es:\n%.*s\n", sendBuffer->len,sendBuffer->buf);
                mbuf_remove(recvBuffer, recvBuffer->len);
            }
            break;
        case MG_EV_SEND:
            {
                cout<<"SE MANDO EL BUFFER\n";
            }
            break;
        default:
            break;

    }

}

int main(void) {

    struct mg_mgr manager;
    struct mg_connection* managerConexion;

    //Refactorizar: iniciarManager(...);
    mg_mgr_init(&manager, NULL);
    // Se bindea al localhost 8000 y se guarda la conexion
    managerConexion = mg_bind(&manager, "8000", ev_handler);
    // Configuro al manager como http
    mg_set_protocol_http_websocket(managerConexion);
    /////////////////////////////////////////////////////////////////////

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
