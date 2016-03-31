#include "mongoose.h"
#include <iostream>
#include <fstream>

using namespace std;

void atenderMesajeHTTP(struct http_message* mensajeHTTP){

    printf("Metodo:\n%.*s\n", mensajeHTTP->method.len,mensajeHTTP->method.p);
    printf("URI:\n%.*s\n",mensajeHTTP->uri.len, mensajeHTTP->uri.p);
    printf("Version del protocolo:\n%.*s\n",mensajeHTTP->proto.len,mensajeHTTP->proto.p);
    printf("Header[0]:Valor[0]:\n%.*s:%.*s\n", mensajeHTTP->header_names[0].len, mensajeHTTP->header_names[0].p, mensajeHTTP->header_values[0].len,mensajeHTTP->header_values[0].p);
    printf("Header[1]:Valor[1]:\n%.*s:%.*s\n", mensajeHTTP->header_names[1].len, mensajeHTTP->header_names[1].p, mensajeHTTP->header_values[1].len,mensajeHTTP->header_values[1].p);
    printf("Body:\n%s\n", mensajeHTTP->body.p);

}

static void ev_handler(struct mg_connection *conexion, int evento, void *ev_data) {


    struct mbuf* recvBuffer = &(conexion->recv_mbuf);
    //struct mbuf* sendBuffer = &(conexion->send_mbuf);

    switch (evento) {
        case MG_EV_HTTP_REQUEST:
            {
                struct http_message* mensajeHTTP = (struct http_message *) ev_data;
                atenderMesajeHTTP(mensajeHTTP);
                mbuf_remove(recvBuffer, recvBuffer->len);
            }
        default:
            break;

    }

}

int main(void) {

    struct mg_mgr manager;
    struct mg_connection* managerConexion;

    mg_mgr_init(&manager, NULL);

    // Se bindea al localhost 8000 y se guarda la conexion
    managerConexion = mg_bind(&manager, "8000", ev_handler);

    // Configuro al manager como http
    mg_set_protocol_http_websocket(managerConexion);

    for (;;) {
        mg_mgr_poll(&manager, 1000);
    }

    mg_mgr_free(&manager);
    return 0;

}
