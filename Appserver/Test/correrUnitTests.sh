cp -r ./UnitTests/TestCases/ArchivosTests ../build/Test/UnitTests
cp -r ./UnitTests/limpiarEntorno.sh ../build/Test
cp -r ./UnitTests/generarCoverage.sh ../build
cd ../build/Test/UnitTests
mkdir -p Entorno
./unitTests
exit $?
