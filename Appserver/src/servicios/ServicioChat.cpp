#include "ServicioChat.h"

ServicioChat::ServicioChat(Mensajero* mensajero, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones){
    this->mensajero = mensajero;
    this->mensajeHTTP = mensajeHTTP;
    //this->sesiones = sesiones;
    this->conversaciones = conversaciones;

    this->atenderChat();
}


void ServicioChat::atenderChat(){
    string usuarioEmisor = this->mensajeHTTP->getHeader("Usuario");
 /*   //string tokenIngresado = this->mensajeHTTP->getHeader("Token");

    //if (this->sesiones->validarTokenConUsuario(usuarioEmisor, tokenIngresado)){
    if (true){
        if (true){//Ahora me tengo que fijar si hubo match
            //aca SI hubo match y tengo el token correcto
*/
    string usuarioReceptor = this->mensajeHTTP->getHeader("Receptor");
    string mensaje = this->mensajeHTTP->getBody();
    //GUARDAR EL MENSAJE EN LAS CONVERSASIONES
    //ANALIZAR SI CONVIENE TENER EN LAS SESIONES DE USUARIO U PTERO A UNA "Conversacion" Y SOLO GUARDARLO EN DISCO CUANDO SE DESCONECTEN LOS DOS USUARIOS DE LA CONVERSACION

    //si la respuesta de GCM fue buena mando mensaje de confirmacion?
    //si la respuesta fue mala igual lo deberia guardar, total al otro le va a llegar enalgun momento
    //Tal vez convenga tener dos mensajes separados 200 Se pudo enviar, 200 se guardo la conv pero no se pudo enviar

    this->conversaciones->agregarMensajeDePara(usuarioEmisor,usuarioReceptor,mensaje);


    //if ( this->sesiones->existeSesionDe(usuarioReceptor) ){
    //Esto se podria verificar en el mensajero

    //ADEMAS ENVIAR EL MENSAJE A GCM
    this->mensajero->enviarMensaje(usuarioEmisor,usuarioReceptor,mensaje);

    //Tengo que interpretar la respuesta del "Shared" o del "RepositorioDeMensajes" o algo asi, abstraerlo
    /*
        servicioChat---->BaseDeDatosDelServidor----->Conexiones
                                                ---->Credenciales

    */
    RespuestaDelChat* respuestaChat = new RespuestaDelChat();
    respuestaChat->setRespuestaGCM();
    this->respuesta = respuestaChat;
    //this->respuesta = GCMreply.toString();
/*
        }
        else{
            //this->respuesta = "HTTP/1.1 400 No hubo match\r\n\r\n";
        }
    }
    else{
        //this->respuesta = "HTTP/1.1 400 No tiene autorizacion\r\n\r\n";
    }
    */
}



ServicioChat::~ServicioChat()
{
    //dtor
}
