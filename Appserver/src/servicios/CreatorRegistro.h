#ifndef CREATORREGISTRO_H
#define CREATORREGISTRO_H


#include "CreatorServicio.h"
#include "servicioRegistro.h"
#include "ServicioInexistente.h"

class CreatorRegistro : public CreatorServicio
{
    public:
        CreatorRegistro(SharedDataBase* shared, MensajeHTTPRequest mensajeHTTP, CredencialesDeUsuarios* credenciales, AdministradorCandidatos* administradorCandidatos );
        virtual ~CreatorRegistro();
    protected:
    private:
};

#endif // CREATORREGISTRO_H
