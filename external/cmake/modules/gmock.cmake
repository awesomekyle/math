set(GMOCK_DIR "external/gmock-1.7.0"
	CACHE PATH "The path to the Google Mock framework.")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # force this option to ON so that Google Test will use /MD instead of /MT
    # /MD is now the default for Visual Studio, so it should be our default, too
    option(gtest_force_shared_crt
           "Use shared (DLL) run-time lib even when Google Test is built as static lib."
           ON)
	if (MSVC_VERSION EQUAL 1700)
		add_definitions(/D _VARIADIC_MAX=10)
	endif()
endif()

add_subdirectory(${GMOCK_DIR} ${CMAKE_BINARY_DIR}/gmock)


set_property(TARGET gmock PROPERTY FOLDER "GTest")
set_property(TARGET gtest PROPERTY FOLDER "GTest")
set_property(TARGET gmock_main PROPERTY FOLDER "GTest")
set_property(TARGET gtest_main PROPERTY FOLDER "GTest")

set_target_properties(gmock PROPERTIES COMPILE_FLAGS "-w")
set_target_properties(gtest PROPERTIES COMPILE_FLAGS "-w")
set_target_properties(gmock_main PROPERTIES COMPILE_FLAGS "-w")
set_target_properties(gtest_main PROPERTIES COMPILE_FLAGS "-w")

include_directories(SYSTEM ${GMOCK_DIR}/gtest/include
						   ${GMOCK_DIR}/include)

#
# add_gmock_test(<target> <sources>...)
#
#  Adds a Google Mock based test executable, <target>, built from <sources> and
#  adds the test so that CTest will run it. Both the executable and the test
#  will be named <target>.
#
function(add_gmock_test target)
    add_executable(${target} ${ARGN})
    target_link_libraries(${target} gmock_main)

    add_test(${target} ${target})
	
    add_custom_command(TARGET ${target}
                       POST_BUILD
                       COMMAND ${target}
                       WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                       COMMENT "Running ${target}" VERBATIM)
endfunction()