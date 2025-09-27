#pragma once
#ifndef _LAVA_VK_H_
#define _LAVA_VK_H_

#include "base_includes.h"
#include "header.h"

#include "loader.h"

#define IMAGE_COUNT 4

typedef struct lvParam {
	GLFWwindow*		window;
	const char* const*	validationLayers;
	const char* const*	instanceExtensions;
	const char* const*	deviceExtensions;
	uint32_t		validationLayersCount;
	uint32_t		instanceExtensionsCount;
	uint32_t		deviceExtensionsCount;
	uint32_t		imageCount;
} lvParam;

typedef struct lvData {
	VkInstance			instance;
   	VkDebugUtilsMessengerEXT	debugMessenger;
	VkSurfaceKHR			surface;
	VkPhysicalDevice		physicalDevice;
	VkDevice			device;
	VkQueue				queue;
	VkSwapchainKHR			swapchain;
	VkImage				swapchainImages[IMAGE_COUNT];
	VkFormat			swapchainImageFormat;
	VkExtent2D			swapchainExtent;
	VkImageView			swapchainImageViews[IMAGE_COUNT];
	VkFramebuffer			swapchainFramebuffers[IMAGE_COUNT];
	VkRenderPass			renderPass;
	VkDescriptorSetLayout		descriptorSetLayout;
	VkPipelineLayout		pipelineLayout;
	VkPipeline			graphicsPipeline;

	VkCommandPool			commandPool;

	VkBuffer			vertexBuffer;
	VkDeviceMemory			vertexBufferMemory;
	VkBuffer			indexBuffer;
	VkDeviceMemory			indexBufferMemory;

	VkBuffer			uniformBuffers[IMAGE_COUNT];
	VkDeviceMemory			uniformBuffersMemory[IMAGE_COUNT];
	void*				uniformBuffersMapped[IMAGE_COUNT];

	VkDescriptorPool		descriptorPool;
	VkDescriptorSet			descriptorSets[IMAGE_COUNT];

	VkCommandBuffer			commandBuffers[IMAGE_COUNT];

	VkSemaphore			imageAvailableSemaphore[IMAGE_COUNT];
	VkSemaphore			renderFinishedSemaphore[IMAGE_COUNT];
	VkFence				inFlightFence[IMAGE_COUNT];

	uint32_t			currentFrame;
} lvData;

typedef struct UniformBufferObject {
	float model[4][4];
	float view[4][4];
	float proj[4][4];
} UniformBufferObject;

static float f = 0.0f;

int createDescriptorSetLayout(const LoaderTable *const pTable, const VkDevice *const device, VkDescriptorSetLayout *const descriptorSetLayout);
int createUniformBuffers(const LoaderTable *const pTable, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkDevice *const device, VkBuffer *const uniformBuffers, VkDeviceMemory *const uniformBuffersMemory, void* *const uniformBuffersMapped);
int updateUniformBuffer(uint32_t currentImage, void** uniformBuffersMapped, const VkExtent2D *const swapchainExtent);

int createDescriptorPool(const LoaderTable *const pTable, const VkDevice *const device, VkDescriptorPool* descriptorPool);
int createDescriptorSets(const LoaderTable *const pTable, const VkDevice *const device, const VkDescriptorPool *const descriptorPool, const VkDescriptorSetLayout *const descriptorSetLayout, const VkBuffer *const uniformBuffers, VkDescriptorSet* descriptorSets);



typedef VkResult (*PFN_glfwCreateWindowSurface)(VkInstance instance, GLFWwindow* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);

typedef int (*PFN_lvInitVulkan)(lvParam *const lvparam, lvData *const lvdata, LoaderTable *const pTable);
typedef int (*PFN_drawFrame)(lvData *const lvdata, const LoaderTable *const pTable);
typedef int (*PFN_lvTerminate)(lvData *const lvdata, const LoaderTable *const pTable);


#endif
