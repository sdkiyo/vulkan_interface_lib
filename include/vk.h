#pragma once
#ifndef _LAVA_VK_H_
#define _LAVA_VK_H_

#include "base_includes.h"
#include "header.h"

#include "loader.h"

#define IMAGE_COUNT 4



typedef struct Vertex {
	vec3 pos;
	vec3 color;
} Vertex;


typedef struct lvParam {
	GLFWwindow*			pWindow;
	const char* const*		ppValidationLayers;
	const char* const*		ppInstanceExtensions;
	const char* const*		ppDeviceExtensions;
	uint32_t			validationLayersCount;
	uint32_t			instanceExtensionsCount;
	uint32_t			deviceExtensionsCount;
	uint32_t			imageCount;
	const Vertex*			pVertices;
	uint32_t			vertices_size;
	const uint16_t*			pIndices;
	uint32_t			indices_size;
	vec3*				pCam_pos;
	vec3*				pCam_target;
	vec3*				pCam_up;
	float				fov;
	float				near;
	float				far;
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


int createDescriptorSetLayout(const LoaderTable *const pTable, const VkDevice *const device, VkDescriptorSetLayout *const descriptorSetLayout);
int createUniformBuffers(const LoaderTable *const pTable, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkDevice *const device, VkBuffer *const uniformBuffers, VkDeviceMemory *const uniformBuffersMemory, void* *const uniformBuffersMapped);
int updateUniformBuffer(uint32_t currentImage, void** pUniformBuffersMapped, const VkExtent2D *const pSwapchainExtent, const vec3 *const pCam_pos, const vec3 *const pCam_target, const vec3 *const pCam_up, const float fov, const float near, const float far);

int createDescriptorPool(const LoaderTable *const pTable, const VkDevice *const device, VkDescriptorPool* descriptorPool);
int createDescriptorSets(const LoaderTable *const pTable, const VkDevice *const device, const VkDescriptorPool *const descriptorPool, const VkDescriptorSetLayout *const descriptorSetLayout, const VkBuffer *const uniformBuffers, VkDescriptorSet* descriptorSets);



typedef VkResult (*PFN_glfwCreateWindowSurface)(VkInstance instance, GLFWwindow* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);

typedef int (*PFN_initVulkan)(lvParam *const lvparam, lvData *const lvdata, LoaderTable *const pTable);
typedef int (*PFN_drawFrame)(lvData *const lvdata, const LoaderTable *const pTable, const lvParam *const lvparam);
typedef int (*PFN_lvTerminate)(lvData *const lvdata, const LoaderTable *const pTable);


#endif
