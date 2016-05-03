#!/bin/bash

#-I. incluye al directory actual al path para buscar includes
#cambiarlo para que busque en el src
#por ahora solo funciona si la carpeta json estuviera en el mism directorio
#g++ -o out constantes.cpp constantesTests.cpp -lcppunit -std=c++11 -lstdc++ json/jsoncpp.cpp -I.

g++ -o out constantes.cpp constantesTests.cpp -lcppunit -std=c++11 -lstdc++ -I../src/external/ ../src/external/json/jsoncpp.cpp



