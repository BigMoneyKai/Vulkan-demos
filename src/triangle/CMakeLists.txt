add_executable(triangle
    triangle.cpp
)
set_target_properties(triangle PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/bin
)

target_link_libraries(triangle PRIVATE
    glfw
    Vulkan::Vulkan
)
target_include_directories(triangle PRIVATE
    ${PROJECT_SOURCE_DIR}/thirdparty/glfw/include
)

set(SHADERS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(GLSL ${SHADERS_SRC}/glsl)
set(SPV ${SHADERS_SRC}/spv)

set(SHADERS 
    ${GLSL}/triangle.vert
    ${GLSL}/triangle.frag
)
set(SPIRV_BINARY_FILES "")
foreach(SHADER ${SHADERS})
    get_filename_component(FILE_NAME ${SHADER} NAME)
    set(SPIRV "${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}.spv")
    add_custom_command(
        OUTPUT ${SPIRV}
        COMMAND ${GLSLANG_VALIDATOR}
        -V
        ${SHADER}
        -o
        ${SPIRV}
        DEPENDS ${SHADER}
        COMMENT "Compiling shader ${FILE_NAME}"
    )

endforeach()

add_custom_target(shaders ALL
    DEPENDS ${SPIRV_BINARY_FILES}
)
add_dependencies(triangle shaders)
