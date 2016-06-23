#ifndef CREATORCHAT_H
#define CREATORCHAT_H

#include "SesionesDeUsuarios.h"
#include "Conversaciones.h"
#include "Mensajero.h"
#include "MensajeHTTPRequest.h"

#include "ServicioChat.h"
#include "ServicioInexistente.h"

#include "CreatorServicio.h"

class CreatorChat : public CreatorServicio
{
    public:
        CreatorChat(Mensajero* mensajero, MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones, Conversaciones* conversaciones, AdministradorCandidatos* administrador);
        virtual ~CreatorChat();
    protected:
    private:


};

#endif // CREATORCHAT_H
