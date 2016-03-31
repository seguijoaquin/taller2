#include <cassert>
#include "rocksdb/db.h"
#include <iostream>
#include "json.h"




int main(){
	
	rocksdb::DB* db;
	rocksdb::Options options;
	options.create_if_missing = true;
	
	rocksdb::Status status =
	  rocksdb::DB::Open(options, "./testdb", &db);
	  
	if (!status.ok()) std::cerr << status.ToString() << std::endl;
	assert(status.ok());
	
	std::string value = "Hola";
	std::string key1 = "clave1";
	std::string key2 = "clave2";
	
	rocksdb::Status s;
	
	
	s = db->Put(rocksdb::WriteOptions(), key2, value);
	
	std::string val;
	
	s = db->Get(rocksdb::ReadOptions(), key2, &val);


	std::cout << val << std::endl;
	return 0;
}
