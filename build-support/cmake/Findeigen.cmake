set(EIGEN_PATH "3rd-party/eigen-3.3.4")

add_library (eigen INTERFACE)

target_compile_definitions (eigen INTERFACE ${EIGEN_DEFINITIONS})
target_include_directories (eigen INTERFACE
    ${EIGEN_PATH}
)