# compile shaders
function(compile_shaders)
    set(GLSL_DIR ${PROJECT_SOURCE_DIR}/shaders/glsl)
    set(SPV_DIR  ${PROJECT_SOURCE_DIR}/shaders/spv)
    find_program(GLSLANG_VALIDATOR glslangValidator REQUIRED)
    file(GLOB_RECURSE GLSL_SOURCES
        CONFIGURE_DEPENDS
        "${GLSL_DIR}/*.vert"
        "${GLSL_DIR}/*.frag"
        "${GLSL_DIR}/*.comp"
        "${GLSL_DIR}/*.geom"
        "${GLSL_DIR}/*.tesc"
        "${GLSL_DIR}/*.tese"
    )

    set(SPIRV_BINARY_FILES)

    foreach(GLSL ${GLSL_SOURCES})
        file(RELATIVE_PATH REL_PATH ${GLSL_DIR} ${GLSL})
        set(SPIRV "${SPV_DIR}/${REL_PATH}.spv")
        get_filename_component(SPIRV_DIR ${SPIRV} DIRECTORY)
        file(MAKE_DIRECTORY ${SPIRV_DIR})
        add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${GLSLANG_VALIDATOR}
                -V
                ${GLSL}
                -o ${SPIRV}
            DEPENDS ${GLSL}
            COMMENT "Compiling shader: ${REL_PATH}"
            VERBATIM
        )
        list(APPEND SPIRV_BINARY_FILES ${SPIRV})
    endforeach()

    add_custom_target(shaders
        DEPENDS ${SPIRV_BINARY_FILES}
    )
endfunction()
