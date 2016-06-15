cp -r ./UnitTests/limpiarEntorno.sh ../build/Test
cp -r ./UnitTests/generarCoverage.sh ../build
cd ../build/Test/UnitTests
mkdir -p Entorno
./unitTests

#Capturo si las lineas en las que fallaron tests
ERROR=$(./unitTests | grep "FAILED")

#Si hay alguna linea, es decir, la variable no esta
#vacia hago un exit 1 para que travis falle el build
#y avise.
if [ -n "$ERROR" ]; then
    exit 1
fi
