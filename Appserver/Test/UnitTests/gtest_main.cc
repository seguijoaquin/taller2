#include "gtest/gtest.h"
#include "Logger.h"

int main(int argc, char **argv) {
  Logger::Instance(DEBUG, "logTests.txt");
  ::testing::InitGoogleTest(&argc, argv);
  int resultadoPruebas = RUN_ALL_TESTS();
  Logger::Instance()->KillLogger();
  return resultadoPruebas;
}
