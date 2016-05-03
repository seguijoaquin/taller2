cmake_minimum_required (VERSION 2.6)
project (Appserver C CXX)

# rocksdb usa pthread agrego el flag -pthread a la compilacion y linkeo.
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pthread -std=c++11 -Wall -Wextra -O0 -g -ftest-coverage -fprofile-arcs" ) 
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pthread -std=c++11 -Wall -Wextra -lsnappy -lgflags -lz -lbz2 -ftest-coverage -fprofile-arcs")

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
file(GLOB_RECURSE SOURCES "./*.cpp" "./*.c")

# add the executable
add_executable(Appserver ${SOURCES})

#Adds static libraries
add_library(rocksdb STATIC IMPORTED)
set_property(TARGET rocksdb PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/librocksdb.a)

target_link_libraries(Appserver rocksdb snappy gflags z bz2 gcov)
