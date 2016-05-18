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
    //cout<<"############################################\n";
    //Posible refactorizacion: pasar el string, solo Mensajes sabe el formato JSON, Conversaciones solo maneja strings
    JsonArray* todosLosMensajes = new JsonArray(this->obtenerTodosLosMensajesEntre(usuario1,usuario2));

    int cantidadMensajesTotales = todosLosMensajes->size();
    /*if(cantidad >= cantidadMensajesTotales && desde == 1){
        //Si se piden mas mensajes de los que hay, entrego todos
        return Mensajes(todosLosMensajes);
    }
    else{
    */
        JsonArray* mensajesPedidos = new JsonArray();
        int limite = cantidadMensajesTotales - desde - cantidad + 1;
        if (limite < 0 ){
            limite = 0;
        }
        for (int i = ( cantidadMensajesTotales - desde); i >= limite ; i--){
            JsonValor mensaje = (*todosLosMensajes)[i];
        //    cout<<mensaje.toString();
            mensajesPedidos->agregar( mensaje );
        }

      //  cout<<"############################################\n";
        delete todosLosMensajes;
        return Mensajes(mensajesPedidos);
    //}
}

















//void Conversaciones::iniciarConversacionEntre(string& usuario1, string& usuario2){
//    if (this->noExisteConversacionEntre(usuario1,usuario2)){
//        //string conversacion;
//        Json::Value* conversacionJson = this->armarConversacionVacia(/*conversacion*/);
//        //this->guardarConversacion(claveConversacion, conversacion);
//        this->guardarConversacion(usuario1, usuario2, conversacionJson);
//        delete conversacionJson;
//    }
//}

/*
bool Conversaciones::noExisteConversacionEntre(string& usuario1, string& usuario2){
    string claveConversacion;
    this->armarClaveDeLaConversacion(usuario1,usuario2, claveConversacion);
    return (!this->conversaciones->existe(claveConversacion));
}
*/

void Conversaciones::armarClaveDeLaConversacion(string& usuario1, string& usuario2, string& claveConversacion){
    if (usuario1 < usuario2){
        claveConversacion = usuario1 + " " + usuario2;
    }
    else{
        claveConversacion = usuario2 + " " + usuario1;
    }
}

/*
Json::Value* Conversaciones::armarConversacionVacia(){//string& conversacion){
    Json::Value* conversacionVacia = new Json::Value;
    *conversacionVacia = Json::objectValue;
    Json::Value mensajes = Json::arrayValue;
    (*conversacionVacia)["mensajes"] = mensajes;

    return conversacionVacia;
}
*/

//void Conversaciones::guardarConversacion(string& claveConversacion, string& conversacion){
/*void Conversaciones::guardarConversacion(string& usuario1, string&usuario2, Json::Value* conversacion){

    string claveConversacion;
    this->armarClaveDeLaConversacion(usuario1,usuario2,claveConversacion);

    //cout<<"Size de mensajes:"<<mensajes.size()<<" \n";
    Json::FastWriter fastWritter;
    //string mensajeAlta = fastWritter.write(conversacionVacia);
    //cout<<mensajeAlta;
  // conversacion = fastWritter.write(*conversacionVacia);

    //this->conversaciones->put(claveConversacion, conversacion);
    this->conversaciones->put(claveConversacion, fastWritter.write(*conversacion));
}
*/
void Conversaciones::guardarConversacion(string& usuario1, string&usuario2, JsonArray& conversacion){

    string claveConversacion;
    this->armarClaveDeLaConversacion(usuario1,usuario2,claveConversacion);

    //cout<<"Size de mensajes:"<<mensajes.size()<<" \n";
    //Json::FastWriter fastWritter;
    //string mensajeAlta = fastWritter.write(conversacionVacia);
    //cout<<mensajeAlta;
  // conversacion = fastWritter.write(*conversacionVacia);

    //this->conversaciones->put(claveConversacion, conversacion);
    this->conversaciones->put(claveConversacion, conversacion.toString());
}

/*
Json::Value* Conversaciones::obtenerCoversacionEntre(string& usuario1, string& usuario2){
    //Refactorizar:tal vez necesite que se devuelva un OBJETO Conversacion
    string claveConversacion;
    this->armarClaveDeLaConversacion(usuario1,usuario2,claveConversacion);

    Json::Value* conversacion = new Json::Value;
    Json::Reader reader;
    reader.parse(this->conversaciones->get(claveConversacion), *conversacion);
    if (*conversacion == Json::nullValue ){
        *conversacion = Json::objectValue;
    }


    return conversacion;
}
*/



//el dummy esta por ahora
/*
Conversacion* Conversaciones::obtenerCoversacionEntre(string& usuario1, string& usuario2, int dummy){

    string claveConversacion;
    this->armarClaveDeLaConversacion(usuario1,usuario2,claveConversacion);

    Json::Value* conversacion = new Json::Value;
    Json::Reader reader;
    reader.parse(this->conversaciones->get(claveConversacion), *conversacion);
    if (*conversacion == Json::nullValue ){
        *conversacion = Json::objectValue;
    }

    cout<<"------------------------------SEPARADOR------------------------\n";
    Json::StyledWriter fastWritter;
    string mensajeAlta = fastWritter.write(*conversacion);
    cout<<mensajeAlta;


    return new Conversacion(conversacion);
}
*/














void Conversaciones::agregarMensajeDePara(string& emisor, string& receptor, string& mensaje){
    //IMPORTANTE: aca puede haber problemas de performance, si todo el tiempo esta accediendo a la base de datos
    //Se podria hacer que Conversaciones o alguien tenga una lista de conversaciones de gente que esta logueada
    //La modificacion podria hacerse en this->guardarConversacion

    JsonArray todosLosMensajes(this->obtenerTodosLosMensajesEntre(emisor,receptor));

    //Json::Value* conversacion = this->obtenerCoversacionEntre(emisor, receptor);
    //Json::Value mensajes;

    JsonObject nuevoMensaje;
    nuevoMensaje.agregarClaveValor("emisor",emisor);
    nuevoMensaje.agregarClaveValor("mensaje",mensaje);
    //((*conversacion)["mensajes"]).append(nuevoMensaje);
    todosLosMensajes.agregar(nuevoMensaje);

    //this->guardarConversacion(emisor,receptor,conversacion);
    this->guardarConversacion(emisor,receptor,todosLosMensajes);

    //delete conversacion;
}


