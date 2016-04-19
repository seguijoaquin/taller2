#include <iostream>


class Constantes{
public:
  static Constantes* Instance();
  std::string getLoginHeaderUsuario();


private:
  Constantes(){};
  Constantes(Constantes const&){};
  static Constantes* instance;

};
