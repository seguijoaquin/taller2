add_subdirectory(external)
add_subdirectory(servidor)
add_subdirectory(servicios)

# add the executable
add_executable(Appserver main.cpp)

target_link_libraries(Appserver external servicios servidor)
