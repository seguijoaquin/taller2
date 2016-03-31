PROJECT(APPSERVER)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


#add_subdirectory(source_dir [binary_dir][EXCLUDE_FROM_ALL])
# The source_dir specifies the directory in which the source CMakeLists.txt and code files are located.
# The binary_dir specifies the directory in which to place the output files
#https://cmake.org/cmake/help/v3.0/command/add_subdirectory.html
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(lib/mongoose)
ADD_SUBDIRECTORY(lib/json)
