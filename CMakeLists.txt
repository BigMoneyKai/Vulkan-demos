cmake_minimum_required(VERSION 3.26)

project(VulkanDemos)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


find_package(Vulkan REQUIRED)
message(STATUS "Vulkan include: ${Vulkan_INCLUDE_DIRS}")
message(STATUS "Vulkan library: ${Vulkan_LIBRARIES}")

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

find_program(GLSLANG_VALIDATOR
    NAMES glslangValidator
    HINTS
    $ENV{VULKAN_SDK}/bin
    /usr/bin
    /usr/local/bin
)
if(NOT GLSLANG_VALIDATOR)
    message(FATAL_ERROR "glslangValidator not found")
endif()

#glfw
add_subdirectory(thirdparty/glfw EXCLUDE_FROM_ALL)

add_subdirectory(src/triangle)


