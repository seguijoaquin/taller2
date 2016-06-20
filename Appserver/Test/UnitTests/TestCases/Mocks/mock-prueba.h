#include <gmock/gmock.h>
#include "SharedDataBase.h"
#include "ListadoDeUsuarios.h"


class MockPrueba: public SharedDataBase {

 public:

  MOCK_METHOD0(obtenerListadoDeUsuarios,ListadoDeUsuarios());

 MockPrueba(ManejadorDeConexiones* conex, string dir):SharedDataBase(conex,dir){}

};
