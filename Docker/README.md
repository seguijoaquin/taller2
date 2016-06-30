# Taller de programacion II - Docker Application server

## Descripcion

Para evitar problemas con la portabilidad del programa se ofrece la posibilidad de correrlo en un Container de Docker que virtualiza ubuntu 14.04

## Instalacion
Para utilizar esta feature es necesario tener docker instalado y corriendo en nuestro ordenador. En caso de no poseerlo ingresar a la pagina de [Docker](https://www.docker.com/) e instalarlo.

## Utilizacion
1. Pararse en la carpeta Docker del proyecto.

2. Utilizar el siguiente comando:

        > docker build -t appserver .

3. Correr el container con:

        > docker run -i -t --name appserver -e PUERTO='3000' -e SHARED_DIR='direccion del shared' -e LIMITE_CANDIDATOS='numero entero positivo' -p 8000:3000 appserver

     Donde se deben completar:

        PUERTO='Puerto del App server', el cual debe ser el mismo que el segundo puerto de -p PUERTO_HOST:PUERTO_APP

        SHARED_DIR: Es la URL del Shared Server.

        .. warning:: La URL no debe incluir http o https. Por ejemplo: t2shared.herokuapp.com

        LIMITE_CANDIDATOS: Limite diario maximo de candidatos que puede pedir un usuario.


4. Para cerrar el servidor o cambiar el shared debemos abrir otra consola, ingresar al container

        > docker exec -it appserver bash

    Una vez ahi utilizamos vi (editor de texto) para modificar el archivo comandos.txt

        > vi comandos.txt

    warning:: Se recomienda antes de esto aprender a utilizar vi en el caso de no haber trabajado con el anteriormente.

    Una vez dentro de este archivo seguir los pasos mecionados en las secciones anteriores
 correspondientes a estas acciones.
