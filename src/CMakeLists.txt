include(${PROJECT_SOURCE_DIR}/cmake/compile_shaders.cmake)

set(EXE_FILES
    triangle
    rectangle
    msaatriangle
    stagingbuffer
    uniformbuffer
)
foreach(EXE ${EXE_FILES})
    add_executable(${EXE}
        ${CMAKE_CURRENT_SOURCE_DIR}/${EXE}/${EXE}.cpp
    )
    target_include_directories(${EXE} PRIVATE 
        ${PROJECT_SOURCE_DIR}/engine
        ${Vulkan_INCLUDE_DIRS}
    )
    target_link_libraries(${EXE} PRIVATE
        glfw
        glm
        Vulkan::Vulkan
        engine
    )
    add_dependencies(${EXE} shaders)
endforeach()

compile_shaders()
