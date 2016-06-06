./correrUnitTests.sh

cd ContenidoParaLasPruebas

./generarCoverage.sh

cd build/Coverage

firefox "index.html"
