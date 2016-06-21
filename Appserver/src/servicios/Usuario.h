#ifndef USUARIO_H
#define USUARIO_H

#include "JsonObject.h"
#include "ListadoDeIntereses.h"
#include "Localizacion.h"


using namespace std;

class Usuario
{
    public:
        Usuario();
        Usuario(string jsonUsuario);
        virtual ~Usuario();

        string getEmail();
        int getId();


        string toString();
        ListadoDeIntereses getIntereses();

        Localizacion getLocalizacion();
        void actualizarLocalizacion(Localizacion& localizacion);
    protected:
    private:
        JsonObject perfil;
        string email;
};

#endif // USUARIO_H
