#include "Servidor.h"



using namespace std;



int main(void) {
    Logger::Instance(DEBUG,"log.txt");
    Servidor server;
    server.iniciarServidor();

    return 0;

}
