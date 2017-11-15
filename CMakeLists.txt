#####################
# Global config     #
#####################
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project("akmath" VERSION 0.0.1)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/build-support/cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(targets)

######################
# 3rd party source   #
######################
include(CTest)

find_package(Catch)

######################
# Source             #
######################
add_subdirectory(test)
