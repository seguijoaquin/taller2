FROM ubuntu:14.04
ENTRYPOINT /home/taller2-appserver/Appserver/build/src/Appserver $PUERTO $SHARED_DIR $LIMITE_CANDIDATOS

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
 sh ./instalar_dependencias.sh;\
 cd Appserver;\
 mkdir build;\
 cd build;\
 cmake ..;\
 make
