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
make static_lib
mv -i librocksdb.a ../
cp -r include/* ../
echo -e '\e[0;32mROCKSDB INSTALADA\e[0m'
cd ../../../
