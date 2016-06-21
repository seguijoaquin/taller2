#ifndef CLIENTEDELSHAREDSERVER_H
#define CLIENTEDELSHAREDSERVER_H

#include "MensajeHTTPReply.h"


//Importante, no se si el mensaje es muy largo csi MG lo manda todo de una o de a pedazos, para esto voy a usar conexionActiva,
//para guiarme por si la conexion esta prendida en vez de por si recibio la respuesta (en ese caso podria desbloquearse si recibe una rta parcial
//Si efectivamente MG devuelve respuestas parciales para mensajes largos (todavia no lo se) deberia tener un metodo appenRespuesta




class ClienteDelSharedServer
{
    public:
        ClienteDelSharedServer();
        virtual ~ClienteDelSharedServer();

        void terminarConexion();

        void esperarRespuesta();

        void setRespuesta(MensajeHTTPReply respuesta);
        //Tal vez hacer que setRespuesta desbloquee al servicio/cliente
        //void dejarDeEsperar();
        MensajeHTTPReply getRespuesta();

        bool conexionActiva;
    protected:
    private:
        MensajeHTTPReply respuesta;
        //bool esperandoRespuesta;
        //bool recibioRespuesta;
        //LO MUEVO ARRIBA PARA PROBAR EL MANAGER UNICO PARA CADA CLIENTE
        //bool conexionActiva;
};

#endif // CLIENTEDELSHAREDSERVER_H
