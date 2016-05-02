#!/bin/bash


g++ -o out "./servicios/MensajeHTTPRequest.cpp" "./external/mongoose/mongoose.o" "./external/StringUtil/StringUtil.cpp"  HttpMessageRequestTest.cpp -lcppunit -std=c++11 -lstdc++ -ljsoncpp