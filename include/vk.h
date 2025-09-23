#pragma once
#ifndef _LAVA_VK_H_
#define _LAVA_VK_H_

#include "base_includes.h"
#include "cgmath.h"

#include "loader.h"

#define IMAGE_COUNT 4

typedef struct lvParam {
	GLFWwindow* window;

	const char* const* validationLayers;
	const char* const* instanceExtensions;
	const char* const* deviceExtensions;

	uint32_t validationLayersCount;
	uint32_t instanceExtensionsCount;
	uint32_t deviceExtensionsCount;

	uint32_t imageCount;
} lvParam;

typedef struct lvData {
	VkInstance instance;
   	VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR surface;
	VkPhysicalDevice physicalDevice;
	VkDevice device;
	VkQueue queue;
	VkSwapchainKHR swapchain;
	VkImage swapchainImages[IMAGE_COUNT];
	VkFormat swapchainImageFormat;
	VkExtent2D swapchainExtent;
	VkImageView swapchainImageViews[IMAGE_COUNT];
	VkRenderPass renderPass;
	VkFramebuffer swapchainFramebuffers[IMAGE_COUNT];
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkCommandPool commandPool;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	VkCommandBuffer commandBuffers[IMAGE_COUNT];

	VkSemaphore imageAvailableSemaphore[IMAGE_COUNT];
	VkSemaphore renderFinishedSemaphore[IMAGE_COUNT];
	VkFence inFlightFence[IMAGE_COUNT];

	uint32_t currentFrame;
} lvData;


typedef VkResult (*PFN_glfwCreateWindowSurface)(VkInstance instance, GLFWwindow* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);

typedef int (*PFN_lvInitVulkan)(lvParam *const lvparam, lvData *const lvdata, LoaderTable *const pTable);
typedef int (*PFN_drawFrame)(lvData *const lvdata, const LoaderTable *const pTable);
typedef int (*PFN_lvTerminate)(lvData *const lvdata, const LoaderTable *const pTable);


#endif
