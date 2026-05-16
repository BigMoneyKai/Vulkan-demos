cmake_minimum_required(VERSION 3.26)

project(VulkanTriangle)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(triangle
    src/triangle.cpp
)

target_link_libraries(
    triangle
    Vulkan::Vulkan
    glfw
)

# =========================
# Shader Compile
# =========================

find_program(
    GLSLANG_VALIDATOR
    glslangValidator
)

set(SHADER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${SHADER_SRC_DIR}/spv)
set(SHADERS 
    triangle.vert
    triangle.frag
)

set(SPIRV_BINARY_FILES)

foreach(SHADER ${SHADERS})

    set(SRC
        ${SHADER_SRC_DIR}/glsl/${SHADER}
    )

    set(DST
        ${SHADER_SRC_DIR}/spv/${SHADER}.spv
    )

    add_custom_command(
        OUTPUT ${DST}

        COMMAND
        ${GLSLANG_VALIDATOR}
        -V
        ${SRC}
        -o
        ${DST}

        DEPENDS ${SRC}

        COMMENT "Compiling shader ${SHADER}"
    )

    list(APPEND SPIRV_BINARY_FILES ${DST})

endforeach()

add_custom_target(
    shaders
    DEPENDS ${SPIRV_BINARY_FILES}
)

add_dependencies(
    triangle
    shaders
)
