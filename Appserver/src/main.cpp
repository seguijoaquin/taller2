#include "Servidor.h"


using namespace std;


int main(int argc, char *argv[]) {

    //Valores por defecto
    string puerto = "8000";
    string direccionShared = "t2shared.herokuapp.com";
    EstadisticasCandidatos::limiteCandidatos = 3;

    if (argc >= 4){
        string limiteDiario = argv[3];
        EstadisticasCandidatos::limiteCandidatos = StringUtil::str2int(limiteDiario);
    }
    if (argc >= 3){
        direccionShared = argv[2];
    }
    if (argc >= 2){
        puerto = argv[1];
    }



    Logger::Instance(DEBUG,"log.txt");
    Logger::Instance()->log(INFO, "Valores iniciales:\nPuerto:" + puerto + "\nSharedServer: "+direccionShared+"\nLimite de candidatos: " + StringUtil::int2string(EstadisticasCandidatos::limiteCandidatos) );
    Servidor server(puerto, direccionShared);
    server.iniciarServidor();
    Logger::Instance()->KillLogger();
    return 0;

}
