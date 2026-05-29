cmake_minimum_required(VERSION 3.26)

# project settings
project(VulkanDemos)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# thirdparty libs
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/glfw)

find_package(Vulkan REQUIRED)
message(STATUS "Vulkan include dirs: ${Vulkan_INCLUDE_DIRS}")
message(STATUS "Vulkan libraries: ${Vulkan_LIBRARIES}")
add_subdirectory(engine)
add_subdirectory(src)
