#include "ConversacionesTests.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION( ConversacionesTests );

ConversacionesTests::ConversacionesTests(){

}
ConversacionesTests::~ConversacionesTests(){

}

void ConversacionesTests::setUp(){
  this->conversaciones = new Conversaciones("./ConversacionesDePrueba");
}
void ConversacionesTests::tearDown(){
  delete this->conversaciones;
}


void ConversacionesTests::testObtenerMensajesEntreUsuariosQueNoConversaronDevuelveUnaConversacionVacia(){
    string usuario1,usuario2;
    usuario1 = "testObtenerMensajesEntreUsuariosQueNoConversaronDevuelveUnaConversacionVacia1";
    usuario2 = "testObtenerMensajesEntreUsuariosQueNoConversaronDevuelveUnaConversacionVacia2";
    //Pido UN mensaje desde el PRIMERO mas antiguo entre usuario1 y usuario2
    Mensajes mensajes = this->conversaciones->obtenerCantidadMensajesDesdeEntre(1,1,usuario1,usuario2);
    CPPUNIT_ASSERT( verificarMensajeVacio(mensajes,1) );
}

bool ConversacionesTests::verificarMensajeVacio(Mensajes& mensajes, int indice){
    return ( (mensajes.getEmisor(indice).empty()) && (mensajes.getMensaje(indice).empty()) );
}

void ConversacionesTests::testObtenerElMensajeDeUnaConversacionConUnUnicoMensaje(){
    string usuario1, usuario2;
    usuario1 = "testObtenerElMensajeMasAntiguoDeUnaConversacionConUnUnicoMensaje1";
    usuario2 = "testObtenerElMensajeMasAntiguoDeUnaConversacionConUnUnicoMensaje2";

    //Mando un mensaje del usuario1 al usuario2
    string mensajeDeUsuario1aUsuario2 = "Sos inimputable hermano, en diez dias salis";
    this->conversaciones->agregarMensajeDePara(usuario1,usuario2, mensajeDeUsuario1aUsuario2);

    //Pido UN mensaje desde el PRIMERO mas antiguo entre usuario1 y usuario2
    Mensajes mensajes = this->conversaciones->obtenerCantidadMensajesDesdeEntre(1,1,usuario1,usuario2);
    CPPUNIT_ASSERT_EQUAL(mensajes.getEmisor(1), usuario1);
    CPPUNIT_ASSERT_EQUAL(mensajes.getMensaje(1), mensajeDeUsuario1aUsuario2);
}


void ConversacionesTests::testElMensajeDeMenorIndiceEsElMensajeMasNuevo(){
    string usuario1, usuario2;
    usuario1 = "testElMensajeDeMenorIndiceEsElMensajeMasNuevo1";
    usuario2 = "testElMensajeDeMenorIndiceEsElMensajeMasNuevo2";

    //Mando varios mensajes
    vector<pair<string,string>> listaMensajes = this->crearListaDeMensajes(usuario1,usuario2,4);
    this->agregarMensajesAConversaciones(usuario1,usuario2,listaMensajes);

    //4 mensajes desde el primero mas nuevo (el primero mas nuevo es el cuarto mensaje, el ultimo en agregarse)
    Mensajes mensajes = this->conversaciones->obtenerCantidadMensajesDesdeEntre(4,1,usuario1,usuario2);

    CPPUNIT_ASSERT(compararMensajeConLista(mensajes,1,listaMensajes,4));
    CPPUNIT_ASSERT(compararMensajeConLista(mensajes,2,listaMensajes,3));
    CPPUNIT_ASSERT(compararMensajeConLista(mensajes,3,listaMensajes,2));
    CPPUNIT_ASSERT(compararMensajeConLista(mensajes,4,listaMensajes,1));
}

bool ConversacionesTests::compararMensajeConLista(Mensajes& mensajes, int indiceMensajes, vector<pair<string,string>>& listaMensajes, int indiceLista){
    return ( (mensajes.getEmisor(indiceMensajes) ==  listaMensajes[indiceLista-1].first) &&
             (mensajes.getMensaje(indiceMensajes) == listaMensajes[indiceLista-1].second) );
}








void ConversacionesTests::testSiSePidenMasMensajesDeLosQueHaySeDevuelvenTodosLosMensajes(){
    string usuario1, usuario2;
    usuario1 = "testSiSePidenMasMensajesDeLosQueHaySeDevuelvenTodosLosMensajes1";
    usuario2 = "testSiSePidenMasMensajesDeLosQueHaySeDevuelvenTodosLosMensajes2";

    vector<pair<string,string>> listaMensajes = this->crearListaDeMensajes(usuario1,usuario2,3);
    this->agregarMensajesAConversaciones(usuario1,usuario2,listaMensajes);

    //Pido 4 mensajes, pero hay tres
    Mensajes mensajes = this->conversaciones->obtenerCantidadMensajesDesdeEntre(4,1,usuario1,usuario2);


    CPPUNIT_ASSERT(compararMensajeConLista(mensajes,1,listaMensajes,3));
    CPPUNIT_ASSERT(compararMensajeConLista(mensajes,2,listaMensajes,2));
    CPPUNIT_ASSERT(compararMensajeConLista(mensajes,3,listaMensajes,1));
    //No hay 4to mensaje
    CPPUNIT_ASSERT( verificarMensajeVacio(mensajes,4) );
}




void ConversacionesTests::testPedirUnaCantidadDeMensajesDesdeUnMensajeQueNoSeaElPrimero(){
    string usuario1, usuario2;

    usuario1 = "testPedirUnaCantidadDeMensajesDesdeUnMensajeQueNoSeaElPrimero1";
    usuario2 = "testPedirUnaCantidadDeMensajesDesdeUnMensajeQueNoSeaElPrimero2";

    //Mando 5 mensajes
    vector<pair<string,string>> listaMensajes = this->crearListaDeMensajes(usuario1,usuario2,5);
    this->agregarMensajesAConversaciones(usuario1,usuario2,listaMensajes);

    //Pido 2 mensajes desde el primero mas nuevo
    Mensajes mensajes1 = this->conversaciones->obtenerCantidadMensajesDesdeEntre(2,1,usuario1,usuario2);
    CPPUNIT_ASSERT(compararMensajeConLista(mensajes1,1,listaMensajes,5));
    CPPUNIT_ASSERT(compararMensajeConLista(mensajes1,2,listaMensajes,4));
    //No hay 3er mensaje
    CPPUNIT_ASSERT( verificarMensajeVacio(mensajes1,3) );

    //Pido 3 mensajes desde el segundo mas nuevo ( el 2do mas nuevo es el 4to mensaje enviado)
    Mensajes mensajes2 = this->conversaciones->obtenerCantidadMensajesDesdeEntre(3,2,usuario1,usuario2);
    CPPUNIT_ASSERT(compararMensajeConLista(mensajes2,1,listaMensajes,4));
    CPPUNIT_ASSERT(compararMensajeConLista(mensajes2,2,listaMensajes,3));
    CPPUNIT_ASSERT(compararMensajeConLista(mensajes2,3,listaMensajes,2));
    //No hay 4to mensaje
    CPPUNIT_ASSERT( verificarMensajeVacio(mensajes2,4) );


}



void ConversacionesTests::testSiLaCantidadDeMensajesQueSePideDesdeElNroDeMensajeIndicadoEsMayorALaCantidadDeMensajesAPartirDelNroDeMensajeIndicadoSeDevuelvenTodosLosMensajesAPartirDelNroDeMensajeIndicado(){
    //No se me ocurrio un nombre mas corto...
    string usuario1, usuario2;
    usuario1 = "testSiLaCantidadDeMensajesQueSePideDesdeElNroDeMensajeIndicadoEsMayorALaCantidadDeMensajesAPartirDelNroDeMensajeIndicadoSeDevuelvenTodosLosMensajesAPartirDelNroDeMensajeIndicado1";
    usuario2 = "testSiLaCantidadDeMensajesQueSePideDesdeElNroDeMensajeIndicadoEsMayorALaCantidadDeMensajesAPartirDelNroDeMensajeIndicadoSeDevuelvenTodosLosMensajesAPartirDelNroDeMensajeIndicado2";
    vector<pair<string,string>> listaMensajes = this->crearListaDeMensajes(usuario1,usuario2,5);
    this->agregarMensajesAConversaciones(usuario1,usuario2,listaMensajes);

    //Mando varios mensajes


    /*Pido 3 mensajes desde el cuarto mensaje mas nuevo (me deberia dar el cuarto, quinto y sexto mas nuevo pero solo hay 5 mensajes totales)
      Entonces solo me da el cuarto y quinto mas nuevo (si se enviaron 5 mensajes, el cuato y el quinto mas nuevo son el mensaje 2 y 1 respectivamente)
    */
    Mensajes mensajes = this->conversaciones->obtenerCantidadMensajesDesdeEntre(3,4,usuario1,usuario2);
    CPPUNIT_ASSERT(compararMensajeConLista(mensajes,1,listaMensajes,2));
    CPPUNIT_ASSERT(compararMensajeConLista(mensajes,2,listaMensajes,1));
    //No hay 3er mensaje
    CPPUNIT_ASSERT( verificarMensajeVacio(mensajes,3) );
}

//Crea una conversacion entre dos usuarios con 'cantidad' mensajes
//En la conversacion se alternan para hablar
//La lista se hace en orden cronologico, el ultimo mensaje en agregarse es el mas nuevo
vector<pair<string,string>> ConversacionesTests::crearListaDeMensajes(string usuario1, string usuario2, int cantidad){

    vector<pair<string,string>> listaMensajes;

    string emisor = usuario1;
    for (int i = 0; i < cantidad; i++){
        pair<string,string> mensaje;
        //pasa i a string
        mensaje.second = "mensaje" + to_string(i) + "    mensaje" + to_string(i);
        if ( emisor == usuario1 ){
            emisor = usuario2;
        }
        else{
            emisor = usuario1;
        }
        mensaje.first = emisor;
        listaMensajes.push_back(mensaje);
    }
    return listaMensajes;
}


void ConversacionesTests::agregarMensajesAConversaciones(string usuario1, string usuario2, vector<pair<string,string>>& listaMensajes){
    for(unsigned int i = 0; i < listaMensajes.size(); i++){
        string emisor, receptor;
        emisor = listaMensajes[i].first;
        if (emisor == usuario1){
            receptor = usuario2;
        }
        else{
            receptor = usuario1;
        }
        this->conversaciones->agregarMensajeDePara(emisor,receptor,listaMensajes[i].second);
    }
}




///////////////Posible refactorizacion//////////////////
//Todo esto lo puedo meter en una funcion que reciba el nombre de la test
//vector<par>>crearListaDeMensaje(nombreTest,cantidad mensajes)

/*    string usuario1, usuario2;
    //alumno = "testSiLaCantidadDeMensajesQueSePideDesdeElNroDeMensajeIndicadoEsMayorALaCantidadDeMensajesAPartirDelNroDeMensajeIndicadoSeDevuelvenTodosLosMensajesAPartirDelNroDeMensajeIndicado1";
    //profesor = "testSiLaCantidadDeMensajesQueSePideDesdeElNroDeMensajeIndicadoEsMayorALaCantidadDeMensajesAPartirDelNroDeMensajeIndicadoSeDevuelvenTodosLosMensajesAPartirDelNroDeMensajeIndicado2";
    usuario1 = "testSiLaCantidadDeMensajesQueSePideDesdeElNroDeMensajeIndicadoEsMayorALaCantidadDeMensajesAPartirDelNroDeMensajeIndicadoSeDevuelvenTodosLosMensajesAPartirDelNroDeMensajeIndicado1";
    usuario2 = "testSiLaCantidadDeMensajesQueSePideDesdeElNroDeMensajeIndicadoEsMayorALaCantidadDeMensajesAPartirDelNroDeMensajeIndicadoSeDevuelvenTodosLosMensajesAPartirDelNroDeMensajeIndicado2";


    vector<pair<string,string>> listaMensajes = this->crearListaDeMensajes(usuario1,usuario2,5);
    this->agregarMensajesAConversaciones(usuario1,usuario2,listaMensajes);
*/
