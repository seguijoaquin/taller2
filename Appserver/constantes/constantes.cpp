#include "constantes.hpp"


//Singleton que contiene las constantes.

Constantes* Constantes::instance = NULL;



Constantes* Constantes::Instance(){

  if (!instance)
    instance = new Constantes();

  return instance;
}


std::string Constantes::getLoginHeaderUsuario(){
  return "Usuario";
}
