cp -r ApiUnitTesting/BaseDeDatosInicial/usuariosRegistrados ApiUnitTesting/EntornoDeTesting
cd ApiUnitTesting/EntornoDeTesting
./../../Appserver/build/Appserver &
python ../AppServerApiUnitTests.py
echo -e "DELETE /registro HTTP/1.1\r\n\r\n\0" | nc localhost 8000
