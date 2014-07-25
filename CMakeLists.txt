cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project("Math")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/external/cmake/Modules)

enable_testing()
include(gmock)
include(glm)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(compiler_flags "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(compiler_flags "/W4 /WX /EHsc /MP /sdl")
	string(REGEX REPLACE "/EH[a-z]+" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}) # Disable C++ exceptions
    string(REGEX REPLACE "/GR" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}) # Disable RTTI
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${compiler_flags} -fno-exceptions -fno-rtti")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${compiler_flags}")

add_definitions(-D_HAS_EXCEPTIONS=0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)

add_subdirectory(test)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
