cp -r ApiUnitTesting/BaseDeDatosInicial/usuariosRegistrados ApiUnitTesting/EntornoDeTesting
cp  ApiUnitTesting/usuario.json ApiUnitTesting/EntornoDeTesting
cp  ApiUnitTesting/usuarioCompleto.json ApiUnitTesting/EntornoDeTesting
cd ApiUnitTesting/EntornoDeTesting
./../../../build/src/Appserver &
sleep 5
python ../AppServerApiUnitTests.py
#echo -e "DELETE /registro HTTP/1.1\r\n\r\n\0" | nc localhost 8000
echo "cerrar" >> comandos.txt
#Esto es para que se borre el entorno y se puedan volver a correr las pruebas
#sleep 3
#rm -r *
