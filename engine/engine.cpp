#include "engine.h"

#include <fstream>
#include <stdexcept>
#include <iostream>

std::vector<uint32_t> readShader(const char* filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if(!file.is_open()) {
        throw std::runtime_error("Failed to open shader file");
    }
    size_t size = static_cast<size_t>(file.tellg());
    if(size % 4 != 0) {
        throw std::runtime_error("The size of spir-v file should be aligned in 4 bytes");
    }
    std::vector<uint32_t> shaderCode(size);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(shaderCode.data()), size);
    file.close();
    
    return shaderCode;
}

uint32_t findMemoryType(
    VkPhysicalDevice physicalDevice, 
    uint32_t typeFilter, 
    VkMemoryPropertyFlags propertiesFlags
) {
    VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &physicalDeviceMemoryProperties);

    for(uint32_t i = 0; i < physicalDeviceMemoryProperties.memoryTypeCount; i++) {
        bool suitable = typeFilter & (1 << i);

        bool hasProperties = (physicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & propertiesFlags) == propertiesFlags;

        if(suitable && hasProperties) {
            return i;
        }
    }
    throw std::runtime_error("Failed to find suitable memory type");
}

VkSampleCountFlagBits GetMaxUsableSampleCount(VkPhysicalDevice physicalDevice) {
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(
        physicalDevice,
        &props);

    VkSampleCountFlags counts =
        props.limits.framebufferColorSampleCounts &
        props.limits.framebufferDepthSampleCounts;

    if (counts & VK_SAMPLE_COUNT_8_BIT)
        return VK_SAMPLE_COUNT_8_BIT;

    if (counts & VK_SAMPLE_COUNT_4_BIT)
        return VK_SAMPLE_COUNT_4_BIT;

    return VK_SAMPLE_COUNT_1_BIT;
}
