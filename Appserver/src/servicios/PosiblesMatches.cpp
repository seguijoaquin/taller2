#include "PosiblesMatches.h"

PosiblesMatches::PosiblesMatches(Usuario* usuarioPrincipal){
    this->usuarioPrincipal = usuarioPrincipal;
}

PosiblesMatches::~PosiblesMatches()
{
    //dtor
}

void PosiblesMatches::agregarPosibleMatch(Usuario* usuario){
    this->posiblesMatches.push(usuario);
}

Usuario PosiblesMatches::obtenerUnPosibleMatch(){
    if (!this->posiblesMatches.empty()){
        Usuario* posibleMatch = this->posiblesMatches.top();
        this->posiblesMatches.pop();
        return posibleMatch;
    }
    else{
        return nullptr;
    }
}
