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
cd app_server/lib/rocksdb-master/
echo -e '\e[0;34mcd app_server/lib/rocksdb-master/\e[0m'
make static_lib
echo -e '\e[0;34mmake static_lib\e[0m'
mv -i librocksdb.a ../
echo -e '\e[0;34mmv -i librocksdb.a ../\e[0m'
cp -r include/* ../
echo -e '\e[0;34mcp -r include/* ../\e[0m'
echo -e '\e[0;32mROCKSDB INSTALADA\e[0m'
cd ../../../
