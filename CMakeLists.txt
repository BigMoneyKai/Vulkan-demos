cmake_minimum_required(VERSION 3.26)

# project settings
project(VulkanDemos)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${PR{PROJECT_SOURCE_DIR/bin)
endforeach()

# packages
find_package(Vulkan REQUIRED)

# thirdparty libs
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/glfw)

# engine of basic global settings
add_subdirectory(engine)
