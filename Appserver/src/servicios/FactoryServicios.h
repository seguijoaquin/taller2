#ifndef FACTORYSERVICIOS_H
#define FACTORYSERVICIOS_H

#include "servicioRegistro.h"
#include "servicioLogin.h"
#include "ServicioChat.h"
#include "ServicioMensajes.h"


class FactoryServicios
{
    public:
        FactoryServicios(ManejadorDeConexiones* conexiones);
        virtual ~FactoryServicios();

        Servicio* fabricarServicio(MensajeHTTPRequest);
    protected:
    private:
        Conversaciones conversaciones = Conversaciones("./ConversacionesFACT");
        SesionesDeUsuarios sesiones;
        CredencialesDeUsuarios credenciales = CredencialesDeUsuarios("./usuariosRegistradosFACT");
        ManejadorDeConexiones* conexiones;

        bool compararMetodoHTTP(MensajeHTTPRequest& httpRequest, string metodo);
        bool compararUriHTTP(MensajeHTTPRequest& httpRequest, string uri);
};

#endif // FACTORYSERVICIOS_H
