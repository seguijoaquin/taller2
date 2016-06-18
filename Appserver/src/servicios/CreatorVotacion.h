#ifndef CREATORVOTACION_H
#define CREATORVOTACION_H

#include <CreatorServicio.h>

#include "ServicioVotacion.h"
#include "SesionesDeUsuarios.h"
#include "ServicioInexistente.h"

class CreatorVotacion : public CreatorServicio
{
    public:
        CreatorVotacion(SharedDataBase* shared, Mensajero* mensajero, MensajeHTTPRequest* mensajeHTTP,SesionesDeUsuarios* sesiones,AdministradorCandidatos* administradorCandidatos);
        virtual ~CreatorVotacion();
    protected:
    private:
};

#endif // CREATORVOTACION_H
