#include "Servidor.h"

Servidor::Servidor(){
    iniciarBaseDeDatos();
}

void Servidor::iniciarServidor(){
    this->activo = true;
    thread comandos(escucharComandos, this);
    this->manejadorDeConexiones.iniciarConexionComoServidor("8000", this);
    comandos.join();
}


void Servidor::iniciarBaseDeDatos(){
    //this->credencialesDeUsuarios = new CredencialesDeUsuarios("./usuariosRegistrados");
    //this->conversaciones = new Conversaciones("./Conversaciones");
}





string Servidor::getRespuestaDelServicio(MensajeHTTPRequest mensajeHTTPRequest){

    Servicio* servicio = this->factoryServicios.fabricarServicio(mensajeHTTPRequest);
    string respuesta;
    if (servicio != nullptr){
        respuesta = servicio->getRespuesta()->toString();
        delete servicio->getRespuesta();
        delete servicio;
    }
    else{
        //ESTO ES TEMPORAL PARA PODER OBTENER LOS REPORTES DE COVERTURA, HABRIA QUE VER QUE PASA CON LOS QUE ESTAN CONECTADOS
        respuesta = "HTTP/1.1 200 Se cerrara el server\r\n\r\n";
        this->manejadorDeConexiones.terminarConexionComoServidor();
    }
    return respuesta;
}

Servidor::~Servidor(){
    //delete this->conversaciones;
    //delete this->credencialesDeUsuarios;
}


void Servidor::escucharComandos(Servidor* servidor){
    string ruta = "comandos.txt";
    while (servidor->estaActivo()){

        //interpretar comandos
        queue<string>* comandos = leerComandos(ruta);
        recorrerComandos(comandos,servidor);
        delete comandos;

        sleep(2);

    }
    servidor->getManejador()->terminarConexionComoServidor();

}

using namespace std;
queue<string>* Servidor::leerComandos(string ruta){
    queue<string>* comandos = new queue<string>;
    fstream archivo(ruta);
    string comando;
    while (getline(archivo, comando)){
        comandos->push(comando);
        cout<<comando<<"\n";
    }
    archivo.close();
    //Estos dos metodos borran el contenido del archivo
    archivo.open(ruta, std::fstream::out | std::fstream::trunc);
    archivo.close();
    return comandos;
}

void Servidor::recorrerComandos(queue<string>* comandos,Servidor* servidor){
    while (!comandos->empty() && servidor->estaActivo()){
        servidor->interpretar(comandos->front());
        comandos->pop();
    }
}

void Servidor::interpretar(string entrada){
    istringstream elementos(entrada);
    string comando;
    elementos >> comando;
    if (comando == "cerrar"){
        this->manejadorDeConexiones.terminarConexionComoServidor();
        this->activo = false;
    }
    else if (comando == "cambiarShared"){
        string nuevoShared;
        elementos >> nuevoShared;
        this->factoryServicios.cambiarShared(nuevoShared);
    }

}

bool Servidor::estaActivo(){
    return this->activo;
}

