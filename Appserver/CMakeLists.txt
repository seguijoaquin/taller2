cmake_minimum_required (VERSION 2.6)
project (AppServer C CXX)


# Con este #define funciona el multithreading de Mongoose
ADD_DEFINITIONS(-DMG_ENABLE_THREADS)


# rocksdb usa pthread agrego el flag -pthread a la compilacion y linkeo.
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pthread -std=c++11 -Wall -Wextra -O0 -g -lgtest -lstdc++ -ftest-coverage -fprofile-arcs" ) 
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pthread -std=c++11 -Wall -Wextra -lsnappy -lgflags -lz -lbz2  -lcppunit -lstdc++ -ftest-coverage -fprofile-arcs")



add_subdirectory(Test)
add_subdirectory(src)
