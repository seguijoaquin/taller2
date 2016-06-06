
file(GLOB_RECURSE SERVICIOS_SOURCE "./*.cpp")

add_library(servicios
	 ${SERVICIOS_SOURCE})


# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories(servicios PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(servicios external servidor)
