#Añade una librería llamada WebServer (libWbServer.a bajo linux) a partir del fichero fuente WebServer.cpp
ADD_LIBRARY(WebServer WebServer)

###### Main

#Asegurarse de que el compilador puede encontrar los ficheros de nuestra librería Hello
INCLUDE_DIRECTORIES(${APPSERVER_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${APPSERVER_SOURCE_DIR}/lib/mongoose)

#Añade un binario llamado "helloWorld" que es construido del fichero fuente "main.cpp"
#La extensión se encuentra automáticamente
ADD_EXECUTABLE(helloWorld main)
 
#Enlaza el ejecutable con la librería Hello
TARGET_LINK_LIBRARIES(helloWorld WebServer)
