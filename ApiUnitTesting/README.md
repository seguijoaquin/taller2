# Tests Unitarios para probar la API

## Correr Tests
1) Hacer el cmake + make como siempre en build. Se generan los .gcno en build/CMakeFiles/AppServer.dir/
2) En build/ correr el ./AppServer normalmente. Correr las pruebas. Mandarle un mensaje con el método DELETE por cualquier otro medio (esto se podria agregar a las TEST). Se generan los .gcda en build/CMakeFiles/AppServer.dir/ luego de que se cierra el server
3) En build crear un directorio "Coverage"
4) En build/ correr "lcov --directory ./CMakeFiles --capture --output-file Coverage/coverage.info" para que se genere el coverage.info
5) Moverse a Coverage
5) Correr "genhtml coverage.info"
6) Se tienen los .html con los reportes de cobertura

https://groups.google.com/forum/#!searchin/7552tallerdeprogramacionii/coverage/7552tallerdeprogramacionii/vqZjIbPUg74/qT07aUTRo9gJ


## Agregar pruebas
Para agregar nuevas pruebas:
Crear un archivo python con las clases de prueba
En el archivo del main hacer "from +archivo+ import *"
