
# rocksdb usa pthread agrego el flag -pthread a la compilacion y linkeo.
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pthread -std=c++11 -Wall -Wextra -O0 -g -lgtest -lstdc++ -ftest-coverage -fprofile-arcs" ) 
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pthread -std=c++11 -Wall -Wextra -lsnappy -lgflags -lz -lbz2  -lcppunit -lstdc++ -ftest-coverage -fprofile-arcs")

# Con este #define funciona el multithreading de Mongoose
ADD_DEFINITIONS(-DMG_ENABLE_THREADS)


#adds directories with headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Appserver/src/external/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Appserver/src/external/mongoose)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Appserver/src/external/json)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Appserver/src/servicios)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Appserver/src/external/rocksdb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Appserver/src/external/StringUtil)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Appserver/src/servidor)




# add the executable
get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

add_executable(Pruebas gtest_main.cc)



#Adds static libraries
add_library(rocksdb STATIC IMPORTED)
set_property(TARGET rocksdb PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../Appserver/src/external/lib/librocksdb.a)

target_link_libraries(Pruebas rocksdb snappy gflags z bz2 stdc++ gtest appserv)
