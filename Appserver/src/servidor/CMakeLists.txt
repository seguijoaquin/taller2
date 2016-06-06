
file(GLOB_RECURSE SERVIDOR_SOURCE "./*.cpp")

add_library(servidor
	 ${SERVIDOR_SOURCE})


# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories(servidor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(servidor external servicios)
