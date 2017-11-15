set(BENCHMARK_PATH "${CMAKE_SOURCE_DIR}/3rd-party/benchmark")

option(BENCHMARK_ENABLE_TESTING "Enable testing of the benchmark library." OFF)
option(BENCHMARK_ENABLE_EXCEPTIONS "Enable the use of exceptions in the benchmark library." OFF)
option(BENCHMARK_ENABLE_LTO "Enable link time optimisation of the benchmark library." ON)
option(BENCHMARK_USE_LIBCXX "Build and test using libc++ as the standard library." OFF)
option(BENCHMARK_BUILD_32_BITS "Build a 32 bit version of the library" OFF)

add_subdirectory(${BENCHMARK_PATH})
target_compile_options(benchmark
    PUBLIC
        /wd4141 # MSVC: 'inline' used more than once
        /MP
)
