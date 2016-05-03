#!/bin/bash

gcc -Wall -c ../src/external/mongoose/mongoose.c -o aca/mongoose.o
gcc -Wall -c ../src/external/mongoose/mongoose.c -o aca/rocksdb.o


g++ -o out ../src/servicios/MensajeHTTPRequest.cpp mongoose.o ../src/external/StringUtil/StringUtil.cpp HttpMessageRequestTest.cpp -lcppunit -std=c++11 -lstdc++ -I../src/external/ -I../src/external/StringUtil/ -I../src/external/mongoose/ -I../src/servicios -I./aca ../src/external/json/jsoncpp.cpp
