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
#include "CreatorBusquedaCandidato.h"
#include "CreatorModificarFoto.h"
#include "CreatorVotacion.h"
#include "CreatorEliminacion.h"
#include "CreatorActualizarPosicion.h"
#include "CreatorPedirIntereses.h"
#include "CreatorPedirInformacion.h"

/** Clase que implementa el patron de diseño Factory
 * https://es.wikipedia.org/wiki/Factory_Method_(patr%C3%B3n_de_dise%C3%B1o)
 */

class FactoryServicios
{
    public:
        FactoryServicios(ManejadorDeConexiones* conexiones);
        virtual ~FactoryServicios();

        Servicio* fabricarServicio(MensajeHTTPRequest);
        void cambiarShared(string direccion);
    protected:
    private:
        Conversaciones* conversaciones;
        SesionesDeUsuarios* sesiones;
        CredencialesDeUsuarios* credenciales;
        ManejadorDeConexiones* conexiones;
        SharedDataBase* shared;
        Mensajero* mensajero;

        AdministradorCandidatos* administradorCandidatos;

        bool compararMetodoHTTP(MensajeHTTPRequest& httpRequest, string metodo);
        bool compararUriHTTP(MensajeHTTPRequest& httpRequest, string uri);
};

#endif // FACTORYSERVICIOS_H
