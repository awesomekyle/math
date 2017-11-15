set(GLM_PATH "3rd-party/glm-0.9.8.5")

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${GLM_PATH})

target_compile_options(glm
    INTERFACE
        /wd4201 # MSVC: nameless struct/union used
)
