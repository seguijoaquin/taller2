#ifndef POSIBLESMATCHES_H
#define POSIBLESMATCHES_H

#include "Usuario.h"

class PosiblesMatches
{
    public:
        PosiblesMatches(Usuario* usuarioPrincipal);
        virtual ~PosiblesMatches();

        void agregarPosibleMatch(Usuario* usuario);
        Usuario* obtenerUnPosibleMatch();
    protected:
    private:
        Usuario* usuarioPrincipal;
        set<Usuario*> posiblesMatches;


};

#endif // POSIBLESMATCHES_H
