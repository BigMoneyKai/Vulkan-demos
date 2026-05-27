# basic global settings for all demos in "src" directory
add_library(engine
    engine.cpp
)


add_executable(triangle
    ${PROJECT_SOURCE_DIR}/src/triangle/triangle.cpp
)
add_executable(msaatriangle
    ${PROJECT_SOURCE_DIR}/src/msaa/msaatriangle.cpp
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine PUBLIC
    Vulkan::Vulkan
)
target_link_libraries(triangle PRIVATE
    engine
    glfw
    glm::glm
)
target_link_libraries(msaatriangle PRIVATE
    engine
    glfw
    glm::glm
)

# find glslangValidator
find_program(GLSLANG_VALIDATOR
    NAMES 
        glslangValidator 
        glslang
    HINTS 
        $ENV{VULKAN_SDK}/bin 
        $ENV{VULKAN_SDK}/Bin 
        $ENV{GLSLANG_INSTALL_DIR}/bin
)

if(GLSLANG_VALIDATOR)
    message(STATUS "glslangValidator found: ${GLSLANG_VALIDATOR}")
else()
    message(FATAL_ERROR "glslangValidator not found!")
endif()

# compile shaders
set(GLSL_DIR ${PROJECT_SOURCE_DIR}/shaders/glsl)
set(SPIRV_DIR  ${PROJECT_SOURCE_DIR}/shaders/spv)

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "${GLSL_DIR}/*.vert"
    "${GLSL_DIR}/*.frag"
    "${GLSL_DIR}/*.comp"
)
set(SPIRV_BINARY_FILES)

foreach(GLSL_SHADER ${GLSL_SOURCE_FILES})
    file(RELATIVE_PATH REL_PATH ${GLSL_DIR} ${GLSL_SHADER})
    set(SPIRV_FILE_PATH "${SPIRV_DIR}/${REL_PATH}.spv")
    get_filename_component(SPIRV_DIRNAME ${SPIRV_FILE_PATH} DIRECTORY)
    file(MAKE_DIRECTORY ${SPIRV_DIRNAME})

    add_custom_command(
        OUTPUT ${SPIRV_FILE_PATH}
        COMMAND ${GLSLANG_VALIDATOR}
                -V
                ${GLSL_SHADER}
                -o ${SPIRV_FILE_PATH}
        DEPENDS ${GLSL_SHADER}
        COMMENT "Compiling shader: ${REL_PATH}"
        VERBATIM
    )
    list(APPEND SPIRV_BINARY_FILES ${SPIRV_FILE_PATH})

endforeach()

add_custom_target(shaders ALL
    DEPENDS ${SPIRV_BINARY_FILES}
)
