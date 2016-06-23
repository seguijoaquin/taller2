#include "AdministradorCandidatos.h"

int LIMITE_CERCANIA = 100;

AdministradorCandidatos::AdministradorCandidatos(SharedDataBase* shared){
    this->shared = shared;
}

AdministradorCandidatos::~AdministradorCandidatos(){
    //dtor
}

void AdministradorCandidatos::inicializarCandidato(string usuario){
    this->estadisticas.inicializarUsuario(usuario);
}

bool AdministradorCandidatos::estaCerca(Usuario& usuario1, Usuario& usuario2){
    Localizacion posicion1 = usuario1.getLocalizacion();
    Localizacion posicion2 = usuario2.getLocalizacion();

    return ( posicion1.getDistancia(posicion2) <= LIMITE_CERCANIA );
}


Usuario* AdministradorCandidatos::buscarCandidatoPara(string usuario){

    Usuario* candidato = nullptr;

    if (!this->estadisticas.usuarioSuperoLimiteDeCandidatos(usuario)){
        ListadoDeUsuarios usuarios = this->shared->obtenerListadoDeUsuarios();
        Usuario usuarioPrincipal = usuarios.getUsuario(usuario);


        Usuario candidatoActual;

        usuarios.irAlInicio();
        while ( ( usuarios.getSiguienteUsuario(candidatoActual) ) && (candidato == nullptr) ){
            if((usuarioPrincipal.getEmail() != candidatoActual.getEmail() ) &&
               (!this->candidatos.usuarioFueNotificadoSobreElCandidato(usuario,candidatoActual.getEmail()) ) &&
               ( this->compararIntereses(usuarioPrincipal,candidatoActual) ) &&
               ( this->estaCerca(usuarioPrincipal,candidatoActual))  &&
                !this->estadisticas.usuarioEsPopular(usuario)){

                //Para parchear que se devuelva la foto en vez del link
                //candidato = new Usuario(candidatoActual);
                candidato = new Usuario(shared->obtenerPerfilDelUsuario(candidatoActual.getId()));
                this->candidatos.registrarNotificacionAUsuarioSobreCandidato(usuarioPrincipal.getEmail(), candidato->getEmail());
                this->estadisticas.contabilizarCandidatoPara(usuarioPrincipal.getEmail());
                Logger::Instance()->log(DEBUG, "Se le entrega a "+ usuario + " un candidato:\n" + candidato->toString());
            }
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


void AdministradorCandidatos::usuarioVotaAFavorDe(string usuario1, string usuario2, bool votoAFavor){
    this->candidatos.usuarioVotaAFavorDe(usuario1, usuario2, votoAFavor);
    if (votoAFavor){
        this->estadisticas.contabilizarVotoPara(usuario1);
    }
}

bool AdministradorCandidatos::hayMatchEntre(string usuario1, string usuario2){
    return this->candidatos.hayMatchEntre(usuario1, usuario2);
}



bool AdministradorCandidatos::usuarioFueNotificadoSobreCandidato(string usuario, string candidato){
    return this->candidatos.usuarioFueNotificadoSobreElCandidato(usuario,candidato);
}
