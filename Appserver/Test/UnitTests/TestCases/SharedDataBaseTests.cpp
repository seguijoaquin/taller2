#include "gmock/gmock.h"
#include "SharedDataBase.h"
#include "Mocks/mock-prueba.h"
#include "AdministradorCandidatos.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;
using ::testing::Return;
using namespace std;

TEST(AdministradorCandidatos, primerPrueba){

  MockPrueba mock(nullptr,"");
  EXPECT_CALL( mock ,obtenerListadoDeUsuarios())
    .Times(AtLeast(1)) 
    .WillOnce(Return(ListadoDeUsuarios()));
  AdministradorCandidatos adm(&mock,nullptr);
  
  ASSERT_EQ(adm.buscarCandidatoPara("asdasd"),nullptr);
  
}
