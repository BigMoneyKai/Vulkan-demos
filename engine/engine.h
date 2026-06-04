#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <stdexcept>
#include <iostream>

#define WINDOW_WIDTH   1280
#define WINDOW_HEIGHT  960

#ifndef NDEBUG
#define VK_CHECK_RESULT(func)\
    do {\
        VkResult result = func;\
        if(result != VK_SUCCESS) {\
            throw std::runtime_error(#func " failed");\
        }\
        std::cout << #func << " succeeded" << std::endl;\
    } while(0);
#else
#define VK_CHECK_RESULT(func) (func)
#endif

std::vector<uint32_t> readShader(const char* filePath);
uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags propertiesFlags);
VkSampleCountFlagBits GetMaxUsableSampleCount(VkPhysicalDevice physicalDevice);
VkCommandBuffer beginSingleTimeCommands(VkDevice device, VkCommandPool commandPool);
void endSingleTimeCommands(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkCommandBuffer commandBuffer);
