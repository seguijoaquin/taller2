file(GLOB_RECURSE SOURCES  "./TestCases/*.cpp")

# add the executable
get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

add_executable(unitTests gtest_main.cc ${SOURCES})


target_link_libraries(unitTests external servidor servicios gtest)
