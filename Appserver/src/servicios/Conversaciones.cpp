#include "Conversaciones.h"

using namespace std;

Conversaciones::Conversaciones(string ruta){
    this->conversaciones = new BaseDeDatos(ruta);
}

Conversaciones::~Conversaciones(){
    delete this->conversaciones;
}


string Conversaciones::obtenerTodosLosMensajesEntre(string usuario1, string usuario2){
    string clave;
    this->armarClaveDeLaConversacion(usuario1,usuario2,clave);
    return this->conversaciones->get(clave);
}

Mensajes Conversaciones::obtenerCantidadMensajesDesdeEntre(int cantidad, int desde, string usuario1, string usuario2){

    Mensajes todosLosMensajes(this->obtenerTodosLosMensajesEntre(usuario1,usuario2));
    int cantidadMensajesTotales = todosLosMensajes.getTamanio();

    Mensajes mensajesPedidos;

    int limite = cantidadMensajesTotales - desde - cantidad + 2;
    if (limite < 1 ){
        Logger::Instance()->log(WARNING, "Se limite de mensajes pedidos es menor a 1 ");
        limite = 1;
    }
    for (int i = ( cantidadMensajesTotales - desde + 1); i >= limite ; i--){
        //El formato Json ahra SOLO se maneja adentro de Mensajes
        mensajesPedidos.agregarMensaje(todosLosMensajes.getEmisor(i),todosLosMensajes.getMensaje(i));
    }
    //tal vez convenga devolver un ptero por la eficiencia
    return mensajesPedidos;
}





void Conversaciones::armarClaveDeLaConversacion(string& usuario1, string& usuario2, string& claveConversacion){
    if (usuario1 < usuario2){
        claveConversacion = usuario1 + " " + usuario2;
    }
    else{
        claveConversacion = usuario2 + " " + usuario1;
    }
}

void Conversaciones::guardarConversacion(string& usuario1, string&usuario2, Mensajes& conversacion){
    string claveConversacion;
    this->armarClaveDeLaConversacion(usuario1,usuario2,claveConversacion);
    this->conversaciones->put(claveConversacion, conversacion.toString());
}


void Conversaciones::agregarMensajeDePara(string& emisor, string& receptor, string& mensaje){
    //IMPORTANTE: aca puede haber problemas de performance, si todo el tiempo esta accediendo a la base de datos
    //Se podria hacer que Conversaciones o alguien tenga una lista de conversaciones de gente que esta logueada
    //La modificacion podria hacerse en this->guardarConversacion
    Logger::Instance()->log(INFO, "Se agrega un mensaje de " + emisor + " para " + receptor + "\n" + mensaje);
    Mensajes todosLosMensajes(this->obtenerTodosLosMensajesEntre(emisor,receptor));
    todosLosMensajes.agregarMensaje(emisor,mensaje);
    this->guardarConversacion(emisor,receptor,todosLosMensajes);

}


