list(APPEND SOURCES
    ${PROJECT_SOURCE_DIR}/include/vec_math.h
    # math_test.cpp
    # math_test_c.c
    # math_test_glm.cpp

    ${PROJECT_SOURCE_DIR}/include/akmath.h
    math-test.cpp
    math-test-glm.cpp

    catch-output.h
)

if(MSVC)
    list(APPEND SOURCES
        # math_test_dx.cpp
        math-test-dx.cpp
    )
endif()

ak_add_catchtest(math-test ${SOURCES})

target_include_directories(math-test
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(math-test
    PRIVATE
        glm
        eigen
)
