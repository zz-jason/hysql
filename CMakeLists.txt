cmake_minimum_required(VERSION 3.22)
project(hysql VERSION 0.1
              DESCRIPTION "hysql is a data platform for data analysts."
              LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20) # enable c++20

# forbid to build in the source dir
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS ${LOC_PATH})
    message(FATAL_ERROR "You cannot build in a source directory (or any\
    directory with a CMakeLists.txt file). Please make a build subdirectory.\
    Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# add cmake modules, set build type
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(default_build_type "release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "setting build type to ${default_build_type} as none was specified")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "choose the type of build" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "debug" "release" "minsizerel" "relwithdebinfo")
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# update all git submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
endif()

# for googletest
option(PACKAGE_TESTS "build the test" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()

# for thirdpart libs
add_subdirectory(thirdparts)

# for the project
add_subdirectory(hysql)
