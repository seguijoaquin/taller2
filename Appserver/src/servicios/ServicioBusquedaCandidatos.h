#ifndef SERVICIOBUSQUEDACANDIDATOS_H
#define SERVICIOBUSQUEDACANDIDATOS_H

#include <Servicio.h>
#include "AdministradorCandidatos.h"
#include "RespuestaDeLaBusqueda.h"

class ServicioBusquedaCandidatos : public Servicio
{
    public:
        ServicioBusquedaCandidatos(AdministradorCandidatos* administradorCandidatos, MensajeHTTPRequest* mensajeHTTP);
        virtual ~ServicioBusquedaCandidatos();
    protected:
    private:
        AdministradorCandidatos* administradorCandidatos;
        MensajeHTTPRequest* mensajeHTTP;
        void atenderBusqueda();
};

#endif // SERVICIOBUSQUEDACANDIDATOS_H
