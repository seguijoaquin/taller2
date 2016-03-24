FROM ubuntu:14.04

#el update lo pongo porque asi lo pone el ejemplo
#instalo las bibliotecas que necesita el rocksdb, cmake, g++ y git
RUN apt-get -y update;\
 sudo apt-get install -y libgflags-dev;\
 sudo apt-get install -y libsnappy-dev;\
 sudo apt-get install -y zlib1g-dev;\
 sudo apt-get install -y libpthread-stubs0-dev;\
 apt-get install -y cmake;\
 apt-get install -y g++;\
 sudo apt-get install -y libbz2-dev;\
 sudo apt-get install -y git


#aca no deja hacer el:  sudo rm -r !(librocksdb.a|include);\ tira este error: /bin/bash: -c: line 0: syntax error near unexpected token `('
#Este RUN baja el repo y compila la libreria del rocksdb
RUN ["/bin/bash", "-c", "cd /home/;\
 git clone https://github.com/seguijoaquin/taller2-appserver.git;\
 cd /home/taller2-appserver/app_server/lib/rocksdb/;\
 make static_lib;\
 cd ../../../;\
 cd app_server/build/;\
 cmake .. ;\
 make"]


#este es el comando que corre en el contenedor si no se le pasa ningun comando como parametro
CMD /bin/bash
