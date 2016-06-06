
file(GLOB_RECURSE EXTERNAL_SOURCE "./*.cpp" "./*.c")

add_library(external
	 ${EXTERNAL_SOURCE})


# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories(external PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/json)
target_include_directories(external PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_include_directories(external PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/mongoose)
target_include_directories(external PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/rocksdb)
target_include_directories(external PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/rocksdb/utilities)
target_include_directories(external PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/StringUtil)
target_include_directories(external PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#Adds static libraries
add_library(rocksdb STATIC IMPORTED)
set_property(TARGET rocksdb PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/librocksdb.a)


target_link_libraries(external rocksdb snappy gflags z bz2 gcov)
