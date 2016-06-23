#ifndef CREATORBUSQUEDACANDIDATO_H
#define CREATORBUSQUEDACANDIDATO_H

#include <CreatorServicio.h>


#include "ServicioBusquedaCandidatos.h"
#include "ServicioInexistente.h"

class CreatorBusquedaCandidato : public CreatorServicio
{
    public:
        CreatorBusquedaCandidato(AdministradorCandidatos* administradorCandidatos, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones);
        virtual ~CreatorBusquedaCandidato();
    protected:
    private:
};

#endif // CREATORBUSQUEDACANDIDATO_H
