#ifndef CREATORLOGIN_H
#define CREATORLOGIN_H

#include <CreatorServicio.h>
#include "SesionesDeUsuarios.h"
#include "MensajeHTTPRequest.h"
#include "CredencialesDeUsuarios.h"
#include "ServicioInexistente.h"
#include "servicioLogin.h"

class CreatorLogin : public CreatorServicio{
    public:
        CreatorLogin(SesionesDeUsuarios* sesionesDeUsuarios, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales, SharedDataBase* shared);
        virtual ~CreatorLogin();
    protected:
    private:
};

#endif // CREATORLOGIN_H
