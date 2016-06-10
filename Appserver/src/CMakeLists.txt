
add_library(rocksdb STATIC IMPORTED)
set_property(TARGET rocksdb PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/librocksdb.a)


file(GLOB_RECURSE SERVICIOS_SOURCE "servicios/*.cpp")

file(GLOB_RECURSE SERVIDOR_SOURCE "servidor/*.cpp")

file(GLOB_RECURSE EXTERNAL_SOURCE "external/*.cpp" "external/*.c")

add_library(appserv
  ${EXTERNAL_SOURCE}
  ${SERVICIOS_SOURCE}
  ${SERVIDOR_SOURCE})

# add the executable
add_executable(Appserver main.cpp)


target_link_libraries(appserv rocksdb snappy gflags z bz2 gcov)
target_link_libraries(Appserver appserv)

target_include_directories(appserv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/servicios)

target_include_directories(appserv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/servidor)
target_include_directories(appserv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external)

target_include_directories(appserv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/json)
target_include_directories(appserv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/lib)
target_include_directories(appserv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/mongoose)
target_include_directories(appserv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/rocksdb)

target_include_directories(appserv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/rocksdb/utilities)
target_include_directories(appserv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/StringUtil)

