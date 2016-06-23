#ifndef CREATORVOTACION_H
#define CREATORVOTACION_H

#include <CreatorServicio.h>

#include "ServicioVotacion.h"

class CreatorVotacion : public CreatorServicio
{
    public:
        CreatorVotacion(SharedDataBase* shared, Mensajero* mensajero, MensajeHTTPRequest* mensajeHTTP,SesionesDeUsuarios* sesiones,AdministradorCandidatos* administradorCandidatos, CredencialesDeUsuarios* credenciales);
        virtual ~CreatorVotacion();
    protected:
    private:
        bool validarNotificacion(MensajeHTTPRequest* mensajeHTTP,AdministradorCandidatos* administradorCandidatos);
};

#endif // CREATORVOTACION_H
