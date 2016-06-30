#include "SesionesDeUsuarios.h"
using namespace std;

string TOKEN_SESION_CERRADA = "TOKEN SESION CERRADA";
double SEGUNDOS_MAXIMO_SESION = 600; //10 minutos. Poner un numero mucho mas grande para las pruebas
int SEGUNDOS_ESPERA_VERIFICACION_SESIONES_VENCIDAS = 1;

SesionesDeUsuarios::SesionesDeUsuarios(){
    //thread verificarSesionesVencidas(verificarSesionesVecidas, this);
    this->activo = true;
    this->resetear = new thread(verificarSesionesVecidas, this);
}

SesionesDeUsuarios::~SesionesDeUsuarios(){
    this->activo = false;
    this->resetear->join();
    delete this->resetear;
}


void SesionesDeUsuarios::verificarSesionesVecidas(SesionesDeUsuarios* sesiones){
    //while (true){
    while(sesiones->activo){
        std::this_thread::sleep_for( (std::chrono::seconds(SEGUNDOS_ESPERA_VERIFICACION_SESIONES_VENCIDAS)));
        sesiones->terminarSesionesVencidas();
    }
}


void SesionesDeUsuarios::terminarSesionesVencidas(){
    for (map<string,datosDeSesion>::iterator it = this->tokensDeSesionesDeUsuario.begin(); it != this->tokensDeSesionesDeUsuario.end(); ++it){
        if  ( (it->second).token != TOKEN_SESION_CERRADA ) {
                int duracionSesion = (it->second).tiempoSesion;
                //Por alguna razon esto anda mal, devuelve numeros mucho mas chicos que la duracion en segundos
                //double duracionSesion = (   clock() - (it->second).tiempoInicioSesion ) / (double) CLOCKS_PER_SEC;
                if ( duracionSesion >= SEGUNDOS_MAXIMO_SESION){
                    string usuario = it->first;
                    Logger::Instance()->log(INFO, "Se vence la sesion de " + usuario + " a los " + to_string(duracionSesion) );
                    this->terminarSesionDe(it->first);
                }
                else{
                    (it->second).tiempoSesion += 10;
                }
        }
    }
}






bool SesionesDeUsuarios::existeSesionDe(string usuario){
    return (this->tokensDeSesionesDeUsuario.find(usuario) != this->tokensDeSesionesDeUsuario.end() );
}

bool SesionesDeUsuarios::validarTokenConUsuario(string usuario, string token){
    bool esValido = ( (this->existeSesionDe(usuario)) && ((this->tokensDeSesionesDeUsuario)[usuario].token ==  token) && ((this->tokensDeSesionesDeUsuario)[usuario].token != TOKEN_SESION_CERRADA));
    if (!esValido){
        Logger::Instance()->log(WARNING, "Token y Usuario no son validos");
    }
    return esValido;


}

void SesionesDeUsuarios::agregarSesionDe(string usuario, string token, string tokenGCM){
    this->tokensDeSesionesDeUsuario[usuario].token = token;
    this->tokensDeSesionesDeUsuario[usuario].tokenGCM = tokenGCM;
    this->tokensDeSesionesDeUsuario[usuario].tiempoSesion = 0;
    Logger::Instance()->log(INFO, "Se inicio la sesion de "+ usuario);
}


string SesionesDeUsuarios::getTokenGCMDe(string usuario){
    if (this->existeSesionDe(usuario)){
        return this->tokensDeSesionesDeUsuario[usuario].tokenGCM;
    }
    else{
        Logger::Instance()->log(ERROR, "No se tiene el TokenGCM de "+ usuario);
        return "";
    }
}

void SesionesDeUsuarios::eliminarUsuario(string usuario){
    this->tokensDeSesionesDeUsuario.erase(usuario);
    Logger::Instance()->log(INFO, "Se elimino "+ usuario);
}



void SesionesDeUsuarios::terminarSesionDe(string usuario){
    if (this->existeSesionDe(usuario)){
        this->tokensDeSesionesDeUsuario[usuario].token = TOKEN_SESION_CERRADA;
    }
}
