cp -r ApiUnitTesting/BaseDeDatosInicial/usuariosRegistrados ApiUnitTesting/EntornoDeTesting
cd ApiUnitTesting/EntornoDeTesting
./../../../build/src/Appserver &
sleep 5
python ../AppServerApiUnitTests.py
#echo -e "DELETE /registro HTTP/1.1\r\n\r\n\0" | nc localhost 8000
echo "cerrar" >> comandos.txt
