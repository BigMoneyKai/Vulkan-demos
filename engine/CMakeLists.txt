add_library(engine
    engine.cpp
)

target_include_directories(engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(engine PUBLIC
    glfw
    glm
    Vulkan::Vulkan
)
