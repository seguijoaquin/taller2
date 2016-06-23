#ifndef CREATORSERVICIO_H
#define CREATORSERVICIO_H

#include "Servicio.h"
#include "ServicioInexistente.h"

#include "MensajeHTTPRequest.h"
#include "SesionesDeUsuarios.h"
#include "AdministradorCandidatos.h"

class CreatorServicio
{
    public:
        CreatorServicio();
        virtual ~CreatorServicio();
        Servicio* getServicio();

    protected:
        Servicio* servicio;

        //Estas funciones las muevo aca
        bool validarUsuarioYPassword(MensajeHTTPRequest* mensajeHTTP);
        bool validarParametrosDeSesion(MensajeHTTPRequest* mensajeHTTP, SesionesDeUsuarios* sesiones);
        bool validarMatch(MensajeHTTPRequest* mensajeHTTP, AdministradorCandidatos* administrador, string headerUsuario1, string headerUsuario2);
    private:

};

#endif // CREATORSERVICIO_H
