#include "CreatorPedirInformacion.h"

CreatorPedirInformacion::CreatorPedirInformacion(SharedDataBase* shared, MensajeHTTPRequest* mensaje, CredencialesDeUsuarios* credenciales, SesionesDeUsuarios* sesiones){
    //Sacar Usuario, sacar Token, verificar
    if (true /*hay match con el usuario pedido || es el mismo usuario*//*&& el token es correcto*/){
        this->servicio = new ServicioPedirInformacion(shared, mensaje, credenciales);
    }
    else{
        this->servicio = new ServicioInexistente();
    }
}

CreatorPedirInformacion::~CreatorPedirInformacion()
{
    //dtor
}
