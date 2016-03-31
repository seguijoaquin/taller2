#Añade una librería llamada WebServer (libWbServer.a bajo linux) a partir del fichero fuente WebServer.cpp
ADD_LIBRARY(WebServer WebServer)

###### Main

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()


# rocksdb usa pthread agrego el flag -pthread a la compilacion y linkeo.
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pthread -std=c++11 -Wall -Wextra" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pthread -std=c++11 -Wall -Wextra" )

#Asegurarse de que el compilador puede encontrar los ficheros de nuestra librería Hello
#include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])
#Add the given directories to those the compiler uses to search for include files.
#https://cmake.org/cmake/help/v3.0/command/include_directories.html
INCLUDE_DIRECTORIES(${APPSERVER_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${APPSERVER_SOURCE_DIR}/lib/mongoose)
INCLUDE_DIRECTORIES(${APPSERVER_SOURCE_DIR}/lib)
INCLUDE_DIRECTORIES(${APPSERVER_SOURCE_DIR}/lib/rocksdb/utilities)
INCLUDE_DIRECTORIES(${APPSERVER_SOURCE_DIR}/lib/json)

#Specify the paths in which the linker should search for libraries. The command will apply only to targets created after it is called.
#https://cmake.org/cmake/help/v3.0/command/link_directories.html
LINK_DIRECTORIES(${APPSERVER_SOURCE_DIR}/lib)

#Añade un binario llamado "helloWorld" que es construido del fichero fuente "main.cpp"
#La extensión se encuentra automáticamente
ADD_EXECUTABLE(appserver main)
 
#Enlaza el ejecutable con la librería WebServer
#Specify libraries or flags to use when linking a given target.
#https://cmake.org/cmake/help/v3.0/command/target_link_libraries.html
TARGET_LINK_LIBRARIES(appserver WebServer)

#rocksdb y sus dependencias
TARGET_LINK_LIBRARIES(appserver librocksdb.a) 
TARGET_LINK_LIBRARIES(appserver gflags )
TARGET_LINK_LIBRARIES(appserver snappy )
TARGET_LINK_LIBRARIES(appserver bz2 )
TARGET_LINK_LIBRARIES(appserver z)



