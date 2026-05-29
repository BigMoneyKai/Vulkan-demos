#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

std::vector<uint32_t> readShader(const char* filePath);
uint32_t findMemoryType(
    VkPhysicalDevice physicalDevice, 
    uint32_t typeFilter, 
    VkMemoryPropertyFlags propertiesFlags
);
