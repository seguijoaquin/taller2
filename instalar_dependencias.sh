# INSTALO ROCKSDB
sudo apt-get install -y libsnappy-dev
sudo apt-get install -y libgflags-dev
sudo apt-get install -y zlib1g-dev
sudo apt-get install -y libbz2-dev
sudo apt-get install -y libcppunit-dev
sudo apt-get install -y libpthread-stubs0-dev
echo '--------------------------'
echo -e '\e[0;32mDEPENDENCIAS INSTALADAS\e[0m'
echo '--------------------------'
echo -e '\e[0;31mInstalando libreria RocksDB\e[0m'
cd Appserver/utilities/rocksdb-master/
echo -e '\e[0;34mcd Appserver/lib/rocksdb-master/\e[0m'
make static_lib
echo -e '\e[0;34mmake static_lib\e[0m'
mkdir ../../src/external/lib
mv -i librocksdb.a ../../src/external/lib
echo -e '\e[0;34mmv -i librocksdb.a ../../src/external\e[0m'
cp -r include/* ../../src/external/
echo -e '\e[0;34mcp -r include/* ../../src/external/\e[0m'
echo -e '\e[0;32mROCKSDB INSTALADA\e[0m'
cd ../../../


#INSTALO GOOGLE TEST Y GOOGLE MOCK
cd Appserver/utilities/GoogleTest
mkdir -p build
cd build
cmake ../
sudo make install
sudo ldconfig
cd ../../../../
