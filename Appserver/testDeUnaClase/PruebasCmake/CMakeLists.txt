cmake_minimum_required (VERSION 2.6)
project (Pruebas C CXX)

# rocksdb usa pthread agrego el flag -pthread a la compilacion y linkeo.
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pthread -std=c++11 -Wall -Wextra -O0 -g -lcppunit -lstdc++" ) 
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pthread -std=c++11 -Wall -Wextra -lsnappy -lgflags -lz -lbz2  -lcppunit -lstdc++")

# Con este #define funciona el multithreading de Mongoose
ADD_DEFINITIONS(-DMG_ENABLE_THREADS)


#adds directories with headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/servidor)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/json/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/mongoose)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/rocksdb)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/rocksdb/utilities)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/StringUtil)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/v7)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/servicios)

#adds the source files recursively
#file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.c")
file(GLOB_RECURSE SOURCES "./*.cpp" "./*.c")

#list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp" )
#list(REMOVE_ITEM SOURCES "./HttpMessageRequestTest.cpp" )

# add the executable

get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

add_executable(Pruebas ${SOURCES})



#Adds static libraries
add_library(rocksdb STATIC IMPORTED)
set_property(TARGET rocksdb PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../src/external/lib/librocksdb.a)

target_link_libraries(Pruebas rocksdb snappy gflags z bz2 cppunit stdc++)
