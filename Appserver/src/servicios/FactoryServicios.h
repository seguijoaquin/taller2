#ifndef FACTORYSERVICIOS_H
#define FACTORYSERVICIOS_H
/*
#include "servicioRegistro.h"
#include "servicioLogin.h"
#include "ServicioChat.h"
#include "ServicioMensajes.h"


#include "SharedDataBase.h"
#include "Mensajero.h"
*/

#include "CreatorChat.h"
#include "CreatorServicioMensajes.h"
#include "CreatorLogin.h"
#include "CreatorRegistro.h"

class FactoryServicios
{
    public:
        FactoryServicios(ManejadorDeConexiones* conexiones);
        virtual ~FactoryServicios();

        Servicio* fabricarServicio(MensajeHTTPRequest);
    protected:
    private:
        Conversaciones* conversaciones;
        SesionesDeUsuarios* sesiones;
        CredencialesDeUsuarios* credenciales;
        ManejadorDeConexiones* conexiones;
        SharedDataBase* shared;
        Mensajero* mensajero;

        bool compararMetodoHTTP(MensajeHTTPRequest& httpRequest, string metodo);
        bool compararUriHTTP(MensajeHTTPRequest& httpRequest, string uri);
};

#endif // FACTORYSERVICIOS_H
