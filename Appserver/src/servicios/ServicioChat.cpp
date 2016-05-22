#include "ServicioChat.h"

ServicioChat::ServicioChat(ManejadorDeConexiones* manejadorDeConexiones, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones){
    this->manejadorDeConexiones = manejadorDeConexiones;
    this->mensajeHTTP = mensajeHTTP;
    this->sesiones = sesiones;
    this->conversaciones = conversaciones;

    this->atenderChat();
}


void ServicioChat::atenderChat(){
    string usuarioEmisor = this->mensajeHTTP->getHeader("Usuario");
    string tokenIngresado = this->mensajeHTTP->getHeader("Token");

    //if (this->sesiones->validarTokenConUsuario(usuarioEmisor, tokenIngresado)){
    if (true){
        if (true){//Ahora me tengo que fijar si hubo match
            //aca SI hubo match y tengo el token correcto
            string usuarioReceptor = this->mensajeHTTP->getHeader("Receptor");
            string mensaje = this->mensajeHTTP->getBody();
            //GUARDAR EL MENSAJE EN LAS CONVERSASIONES
            //ANALIZAR SI CONVIENE TENER EN LAS SESIONES DE USUARIO U PTERO A UNA "Conversacion" Y SOLO GUARDARLO EN DISCO CUANDO SE DESCONECTEN LOS DOS USUARIOS DE LA CONVERSACION

            //si la respuesta de GCM fue buena mando mensaje de confirmacion?
            //si la respuesta fue mala igual lo deberia guardar, total al otro le va a llegar enalgun momento
            //Tal vez convenga tener dos mensajes separados 200 Se pudo enviar, 200 se guardo la conv pero no se pudo enviar


            this->conversaciones->agregarMensajeDePara(usuarioEmisor,usuarioReceptor,mensaje);


            //if ( this->sesiones->existeSesionDe(usuarioReceptor) ){
            if(true){
                //ADEMAS ENVIAR EL MENSAJE A GCM
                //Crear el Mensaje HTTP Request y mandarselo al manejador de conexiones
                //TODO: deberia agregar el token del cliente.
                MensajeHTTPRequestGCM requestGCM;
                ////////////////////////////////REFACTORIZAR//////////////////////////////////////
                Json::Value bodyJson = Json::objectValue;
                Json::Value dataJson = Json::objectValue;
                //Hardcodeado el cluente de mi comopu
                //bodyJson["to"] = "APA91bFundy4qQCiRnhUbMOcsZEwUBpbuPjBm-wnyBv600MNetW5rp-5Cg32_UA0rY_gmqqQ8pf0Cn-nyqoYrAl6BQTPT3dXNYFuHeWYEIdLz0RwAhN2lGqdoiYnCM2V_O8MonYn3rL6hAtYaIz_b0Jl2xojcKIOqQ";
                bodyJson["to"] = "APA91bFundy4qQCiRnhUbMOcsZEwUBpbuPjBm-wnyBv600MNetW5rp-5Cg32_UA0rY_gmqqQ8pf0Cn-nyqoYrAl6BQTPT3dXNYFuHeWYEIdLz0RwAhN2lGqdoiYnCM2V_O8MonYn3rL6hAtYaIz_b0Jl2xojcKIOqQ";
                dataJson["Emisor"] = usuarioEmisor;
                dataJson["Mensaje"] = mensaje;
                bodyJson["data"] = dataJson;
                Json::FastWriter escritor;
                requestGCM.setBody( escritor.write(bodyJson) );
                MensajeHTTPReply reply = this->manejadorDeConexiones->enviarMensajeHTTP(&requestGCM,"80");
                cout<<"Mensaje de respuesta de GCM:\n"<<reply.toString();
                ////////////////////////////////////////////////////////////////////////////////////
                this->respuesta = reply.toString();
            }
        }
        else{
            this->respuesta = "HTTP/1.1 400 No hubo match\r\n\r\n";
        }
    }
    else{
        this->respuesta = "HTTP/1.1 400 No tiene autorizacion\r\n\r\n";
    }
}

string ServicioChat::getRespuesta(){
    return this->respuesta;
}



ServicioChat::~ServicioChat()
{
    //dtor
}
