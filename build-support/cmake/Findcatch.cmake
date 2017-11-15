set(CATCH_PATH "${CMAKE_SOURCE_DIR}/3rd-party/catch-2.0.0-d5")

# Prepare "Catch" library for other executables
add_library(Catch STATIC ${CATCH_PATH}/main.cpp)
target_include_directories(Catch PUBLIC ${CATCH_PATH})

function(ak_add_catchtest target)
    if(MSVC)
         # Enable RTTI
        string(REGEX REPLACE "/GR-" "/GR" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
         # Enable C++ exceptions
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc" PARENT_SCOPE)
        add_definitions(-D_HAS_EXCEPTIONS=1)
    else()
         # Enable RTTI
        string(REGEX REPLACE "-fno-rtti" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} )
         # Enable C++ exceptions
        string(REGEX REPLACE "-fno-exceptions" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" PARENT_SCOPE)
    endif()

    ak_add_executable(${target} ${ARGN})
    target_link_libraries(${target} PRIVATE Catch)

    if(CI_BUILD)
        add_test(NAME ${target}
                 COMMAND ${target}  "--out=${CMAKE_BINARY_DIR}/catch_${target}_results.xml")
        set_target_properties(${target}
            PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/tests"
                RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/tests"
                RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/tests"
                RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
        )
    else()
        add_custom_command(TARGET ${target}
            POST_BUILD
            COMMAND ${target}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Running ${target}..." VERBATIM
        )
    endif()
endfunction()
