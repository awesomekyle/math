list(APPEND SOURCES
    main.cpp
    math-benchmark.cpp
)

ak_add_executable(math-benchmark ${SOURCES})
target_link_libraries(math-benchmark
    PRIVATE
        benchmark
        glm
        eigen
)
target_include_directories(math-benchmark
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

add_dependencies(math-benchmark math-test)
