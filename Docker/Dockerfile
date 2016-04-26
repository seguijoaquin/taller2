FROM ubuntu:14.04

#el update lo pongo porque asi lo pone el ejemplo
#instalo las bibliotecas que necesita el rocksdb, cmake, g++ y git
RUN apt-get -y update;\
 apt-get install -y cmake;\
 apt-get install -y g++;\
 sudo apt-get install -y git;\
 sudo apt-get install -y python;\
 sudo apt-get install -y lcov;\
 sudo apt-get install -y valgrind


#Este RUN baja el repo y compila la libreria del rocksdb
RUN cd /home/;\
 git clone https://github.com/seguijoaquin/taller2-appserver.git;\
 cd /home/taller2-appserver/;\
 ./instalar_rocksdb.sh;\
 ./instalar_cppunit.sh;\
 cd Appserver;\
 mkdir build;\
 cd build;\
 cmake ../src;\
 make





#este es el comando que corre en el contenedor si no se le pasa ningun comando como parametro
CMD /bin/bash
