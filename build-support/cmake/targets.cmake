# Set some global compile flags
set(ALL_C_FLAGS CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
set(ALL_CXX_FLAGS CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
if(MSVC AND NOT ${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    foreach(flag_var ${ALL_C_FLAGS} ${ALL_CXX_FLAGS})
        # Disable RTTI
        string(REPLACE "/GR" "/GR-" ${flag_var} "${${flag_var}}")

        # Disable exceptions
        string(REGEX REPLACE "/EH[a-z]+" "" ${flag_var} "${${flag_var}}")
    endforeach()
endif()
if(${CMAKE_CXX_COMPILER_ID} MATCHES GNU OR ${CMAKE_CXX_COMPILER_ID} MATCHES Clang)

    # Some options need to be specified for only C or C++
    foreach(flag_var ${ALL_CXX_FLAGS})
        # -fno-rtti         Disable RTTI
        # -fno-exceptions   Disable exceptions
        set(${flag_var} "${${flag_var}} -std=c++11  -fno-rtti -fno-exceptions")
    endforeach()
    foreach(flag_var ${ALL_C_FLAGS})
        # -std=c99          MSVC only supports c99
        set(${flag_var} "${${flag_var}} -std=c99")
    endforeach()
endif()

set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/release")
set(RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug")
set(RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/relwithdebinfo")
set(RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release")

################################################################################
function(set_source_folder GENERATED FILE ABSOLUTE_NAME ABSOLUTE_PATH)
    file(RELATIVE_PATH RELATIVE_NAME ${ABSOLUTE_PATH} ${ABSOLUTE_NAME})
    get_filename_component(RELATIVE_PATH ${RELATIVE_NAME} PATH)

    if(RELATIVE_PATH)
        string(REPLACE "/" "\\" GROUP ${RELATIVE_PATH})
        if(${GENERATED})
            source_group("${GROUP}\\gen" FILES ${FILE})
        else()
            source_group(${GROUP} FILES ${FILE})
        endif()
    else()
        if(${GENERATED})
            source_group("gen" FILES ${FILE})
        else()
            source_group("" FILES ${FILE})
        endif()
    endif()
endfunction()

################################################################################
function(set_source_folders)
    cmake_parse_arguments(
        AK                  # Save arguments with this prefix
        ""                  # Options with no arguments
        ""                  # Options with a single argument
        "FOLDERS;SOURCES"   # Options with multiple arguments
        ${ARGN}             # Arguments to parse
    )

    foreach(FILE ${AK_SOURCES})
        string(FIND ${FILE} ${CMAKE_CURRENT_BINARY_DIR} MANUAL) # if found, MANUAL will be 0
        if(NOT MANUAL)
            set(GENERATED TRUE)
        else()
            set(GENERATED FALSE)
        endif()
        foreach(FOLDER ${AK_FOLDERS})
            if(IS_ABSOLUTE ${FILE})
                file(RELATIVE_PATH RELATIVE_NAME ${FOLDER} ${FILE})
                if(NOT RELATIVE_NAME MATCHES "\\.\\..*")
                    set_source_folder(${GENERATED} ${FILE} ${FILE} ${FOLDER})
                endif()
            elseif(EXISTS ${FOLDER}/${FILE})
                set_source_folder(${GENERATED} ${FILE} ${FOLDER}/${FILE} ${FOLDER})
            endif()
        endforeach()
    endforeach()
endfunction()

################################################################################
function(set_default_target_folder TARGET)
    set(FILE ${CMAKE_CURRENT_LIST_FILE})
    file(RELATIVE_PATH RELATIVE_NAME ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_FILE})
    get_filename_component(RELATIVE_PATH ${RELATIVE_NAME} PATH)
    string(REGEX REPLACE "\/[^\/]+$" "" RELATIVE_PATH ${RELATIVE_PATH})
    set_target_properties(${TARGET} PROPERTIES FOLDER ${RELATIVE_PATH})
endfunction(set_default_target_folder)

################################################################################
# Set compile options
function(setup_compile_options target)
    # Set up compiler options
    if(MSVC)
        if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
            target_compile_options(${target}
                PRIVATE
                    /W4
                    /WX
                    /MP
                    /sdl
                    # VS2017
                    # /diagnostics:caret # Of course CMake doesn't work with this
                    /Zc:rvalueCast
                    /std:c++14
            )
            target_compile_definitions(${target}
                PRIVATE
                    # Automatically call secure versions of unsecure methods (such as strncpy)
                    -D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT=1
                    -D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES=1
                    -D_CRT_SECURE_NO_WARNINGS=1
            )
        elseif(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
            target_compile_options(${target}
                PRIVATE
                    -Wall               # Enable (almost) all warnings
                    -Wextra             # Enable additional warnings
                    -Werror             # Warnings as errors
                    -Wtype-limits       # Warn if a comparison is always true or always false due to the limited range of the data type
                    -Wno-missing-field-initializers # Disable warning when all struct members are not initialized
                    -Wunused-parameter
                    -Woverloaded-virtual
                    -Wpedantic          # Warn when using unstandard language extensions
                    -Wpointer-bool-conversion   # Warn when implicitly using an address as a bool
            )
        endif()

        if(${CMAKE_SYSTEM_NAME} STREQUAL WindowsStore)
            target_compile_options(${TARGET}
                PRIVATE
                    /ZW     # Allow MSVC extensions
                    /wd4530 # C++ exception handler used
            )
        endif()
        target_compile_definitions(${target}
            PRIVATE
                # Enable Unicode
                -D_UNICODE -DUNICODE
                # Do not define min and max macros
                -DNOMINMAX
                # Skip rarely-used Windows headers
                -DWIN32_LEAN_AND_MEAN
                # disable STL exceptions
                -D_HAS_EXCEPTIONS=0
        )

        # Add properties CMake can't handle natively
        set_target_properties(${target} PROPERTIES
            VS_USER_PROPS
                "${CMAKE_SOURCE_DIR}/build-support/vs2017/extra-compile-options.props"
        )
    elseif(${CMAKE_CXX_COMPILER_ID} MATCHES GNU OR ${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
        target_compile_options(${target}
            PRIVATE
                -Wall               # Enable (almost) all warnings
                -Wextra             # Enable additional warnings
                -Werror             # Warnings as errors
                -Wtype-limits       # Warn if a comparison is always true or always false due to the limited range of the data type
                -Wno-missing-field-initializers # Disable warning when all struct members are not initialized
                -Wunused-parameter
                -Woverloaded-virtual
                -Wpedantic          # Warn when using unstandard language extensions
        )

        # Add specific clang options
        if(${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
            target_compile_options(${target}
                PRIVATE
                    -Wpointer-bool-conversion   # Warn when implicitly using an address as a bool
                    #-fobjc-arc #Enable Objective-C ARC # TODO: Figure out how to work with GLFW
            )
        endif()
    endif()
endfunction()

################################################################################
function(set_output_directories target)
    set_target_properties( ${target}
        PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/release"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/release"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/release"
            ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib/debug"
            LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug"
            ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/lib/relwithdebinfo"
            LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/relwithdebinfo"
            RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/relwithdebinfo"
            ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib/release"
            LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release"
    )
endfunction()

################################################################################
function(ak_add_executable AK_TARGET)
    cmake_parse_arguments(
        AK        # Save arguments with this prefix
        "WIN32"     # Options with no arguments
        "FOLDER"    # Options with a single argument
        "SOURCES"   # Options with multiple arguments
        ${ARGN}     # Arguments to parse
    )

    # Add the target using the given executable type.
    if(AK_WIN32)
        add_executable(${AK_TARGET} WIN32 ${AK_SOURCES} ${AK_UNPARSED_ARGUMENTS})
    else()
        add_executable(${AK_TARGET} ${AK_SOURCES} ${AK_UNPARSED_ARGUMENTS})
    endif()

    # Set project folder, defaults to match physical layout.
    if(AK_FOLDER)
        set_target_properties(${AK_TARGET} PROPERTIES FOLDER ${AK_FOLDER})
    else()
        set_default_target_folder(${AK_TARGET})
    endif()

    # Set default compile options.
    setup_compile_options(${AK_TARGET})

    get_property(TARGET_SOURCES TARGET ${AK_TARGET} PROPERTY SOURCES)

    # Organize project to match physical layout.
    set_source_folders(
        FOLDERS
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_BINARY_DIR}
        SOURCES
            ${TARGET_SOURCES}
    )

    # set output directories
    set_output_directories(${AK_TARGET})
endfunction()

################################################################################
function(ak_add_library AK_TARGET)
    cmake_parse_arguments(
        AK                        # Save arguments with this prefix
        "NO_FORMAT;STATIC;SHARED"   # Options with no arguments
        "FOLDER"                    # Options with a single argument
        "SOURCES;GENERATED_SOURCES" # Options with multiple arguments
        ${ARGN}                     # Arguments to parse
    )

    # Add the target using the given library type.
    if(AK_STATIC)
        add_library(${AK_TARGET} STATIC ${AK_SOURCES} ${AK_GENERATED_SOURCES} ${AK_UNPARSED_ARGUMENTS})
    elseif(AK_SHARED)
        add_library(${AK_TARGET} SHARED ${AK_SOURCES} ${AK_GENERATED_SOURCES} ${AK_UNPARSED_ARGUMENTS})
    else()
        add_library(${AK_TARGET} ${AK_SOURCES} ${AK_GENERATED_SOURCES} ${AK_UNPARSED_ARGUMENTS})
    endif()

    # Set project folder, defaults to match physical layout.
    if(AK_FOLDER)
        set_target_properties(${AK_TARGET} PROPERTIES FOLDER ${AK_FOLDER})
    else()
        set_default_target_folder(${AK_TARGET})
    endif()

    # Set default compile options.
    setup_compile_options(${AK_TARGET})

    get_property(TARGET_SOURCES TARGET ${AK_TARGET} PROPERTY SOURCES)

    # Organize project to match physical layout.
    set_source_folders(
        FOLDERS
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_BINARY_DIR}
        SOURCES
            ${TARGET_SOURCES}
    )

    # set output directories
    set_output_directories(${AK_TARGET})
endfunction()
