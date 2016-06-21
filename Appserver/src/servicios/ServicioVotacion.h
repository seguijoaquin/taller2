#ifndef SERVICIOVOTACION_H
#define SERVICIOVOTACION_H

#include <Servicio.h>

#include "SharedDataBase.h"
#include "MensajeHTTPRequest.h"
#include "AdministradorCandidatos.h"
#include "RespuestaDeLaVotacion.h"

/** Clase que gestiona el servicio
 * de votacion que brinda el sistema
 */

class ServicioVotacion : public Servicio
{
    public:
        ServicioVotacion(SharedDataBase* shared, MensajeHTTPRequest* mensajeHTTP, AdministradorCandidatos* administradorCandidatos, Mensajero* mensajero);
        virtual ~ServicioVotacion();
    protected:
    private:
        void atenderVotacion();
        MensajeHTTPRequest* mensajeHTTP;
        AdministradorCandidatos* administradorCandidatos;
        SharedDataBase* shared;
        Mensajero* mensajero;
};

#endif // SERVICIOVOTACION_H
