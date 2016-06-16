#include "AdministradorCandidatos.h"

AdministradorCandidatos::AdministradorCandidatos(SharedDataBase* shared, Mensajero* mensajero){
    this->shared = shared;
    this->mensajero = mensajero;
}

AdministradorCandidatos::~AdministradorCandidatos(){
    //dtor
}


Usuario* AdministradorCandidatos::buscarCandidatoPara(string usuario){
    ListadoDeUsuarios usuarios = this->shared->obtenerListadoDeUsuarios();
    Usuario usuarioPrincipal = usuarios.getUsuario(usuario);

    Usuario* candidato = nullptr;
    Usuario candidatoActual;

    usuarios.irAlInicio();
    while ( ( usuarios.getSiguienteUsuario(candidatoActual) ) && (candidato == nullptr) ){
        if((usuarioPrincipal.getEmail() != candidatoActual.getEmail() ) &&
           (!this->candidatos.usuarioFueNotificadoSobreElCandidato(usuario,candidatoActual.getEmail()) ) &&
           ( this->compararIntereses(usuarioPrincipal,candidatoActual) ) /*&&
            this->estaCerca(usuarioPrincipal,*candidatoActual)*/){
            candidato = new Usuario(candidatoActual);
            this->candidatos.registrarNotificacionAUsuarioSobreCandidato(usuarioPrincipal.getEmail(), candidato->getEmail());
        }
    }
    return candidato;
}


bool AdministradorCandidatos::compararIntereses(Usuario& usuario1, Usuario& usuario2){
    ListadoDeIntereses interesesUsuario1 = usuario1.getIntereses();
    ListadoDeIntereses interesesUsuario2 = usuario2.getIntereses();

    int cantidadIntereses1 = interesesUsuario1.size();
    bool interesEnComun = false;
    int i = 1;
    while ( (i <= cantidadIntereses1) && (!interesEnComun) ){
        Interes interesUsuario1 = interesesUsuario1.getInteres(i);
        interesEnComun = interesesUsuario2.tieneInteres(interesUsuario1);
        i++;
    }

    return interesEnComun;
}


