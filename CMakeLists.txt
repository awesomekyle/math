#####################
# Global config     #
#####################
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project("akmath" VERSION 0.0.1)


# determine whether this is a standalone project or included by other projects
set(AKMATH_STANDALONE_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(AKMATH_STANDALONE_PROJECT ON)
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/build-support/cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(targets)

######################
# 3rd party source   #
######################
include(CTest)

if(AKMATH_STANDALONE_PROJECT)
    find_package(catch)
    find_package(glm)
    find_package(benchmark)
    find_package(eigen)
endif()

######################
# Source             #
######################
if(AKMATH_STANDALONE_PROJECT)
    add_subdirectory(test)
    add_subdirectory(benchmark)
endif()

add_library(akmath INTERFACE)
target_include_directories(akmath INTERFACE include)
