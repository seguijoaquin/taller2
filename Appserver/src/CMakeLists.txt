add_subdirectory(external)
add_subdirectory(servidor)
add_subdirectory(servicios)

add_library(appserv)

# add the executable
add_executable(Appserver main.cpp)

target_link_libraries(appserv external servicios servidor)

target_link_libraries(Appserver appserv)
