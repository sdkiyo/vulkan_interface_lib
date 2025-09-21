#pragma once
#ifndef _LAVA_VK_H_
#define _LAVA_VK_H_

#include "base_includes.h"

#define IMAGE_COUNT 4

typedef struct lvParam{
	struct lvData* lvdata;
	uint32_t validationLayersCount;
	const char* const* validationLayers;
	uint32_t instanceExtensionsCount;
	const char* const* instanceExtensions;
	uint32_t deviceExtensionsCount;
	const char* const* deviceExtensions;
	uint32_t imageCount;
} lvParam;

typedef struct lvData{
	PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr;
	PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr;

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
	VkCommandBuffer commandBuffers[IMAGE_COUNT];

	VkSemaphore imageAvailableSemaphore[IMAGE_COUNT];
	VkSemaphore renderFinishedSemaphore[IMAGE_COUNT];
	VkFence inFlightFence[IMAGE_COUNT];

	uint32_t currentFrame;
} lvData;


int vkGetFuncAddr();

int lvCreateInstance(PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, const char* const* validationLayers, const uint32_t validationLayersCount, const char* const* extensions, const uint32_t extensionsCount, VkInstance *const instance);

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* userData);
void fillDebugUtilsMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* debugCreateInfo);
int createDebugUtilsMessenger(PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, const VkInstance *const instance, VkDebugUtilsMessengerEXT *const debugMessenger);

int lvCreateSurface(GLFWwindow *const window, const VkInstance *const instance, VkSurfaceKHR *const surface);

int lvPickPhysicalDevice(PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, const VkInstance *const instance, VkPhysicalDevice *const physicalDevice);
int createLogicalDevice(PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkInstance *const instance, const char* const* deviceExtensions, uint32_t deviceExtensionsCount, const VkPhysicalDevice *const physicalDevice, VkDevice *const device, VkQueue *const queue);

int createSwapchain(PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkSurfaceKHR *const surface, const VkDevice *const device, VkSwapchainKHR *swapchain, VkImage* swapchainImages, VkFormat* swapchainImageFormat, VkExtent2D* swapchainExtent);
int createImageViews(PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, const VkFormat *const swapchainImageFormat, const VkImage *const swapchainImages, VkImageView* swapchainImageViews);
int createRenderPass(PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, const VkFormat *const swapchainImageFormat, VkRenderPass* renderPass);

int createFramebuffers(PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, const VkExtent2D *const swapchainExtent, const VkRenderPass *const renderPass, const VkImageView *const swapchainImageViews, VkFramebuffer* swapchainFramebuffers);
int createGraphicsPipeline(PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, VkPipelineLayout* pipelineLayout, VkPipeline* graphicsPipeline, const VkRenderPass *const renderPass);
int createCommandPool(PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, VkCommandPool* commandPool);
int createCommandBuffer(PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, VkCommandPool* commandPool, VkCommandBuffer* commandBuffers);

int createSyncObjects(PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, VkSemaphore *const imageAvailableSemaphore, VkSemaphore *const renderFinishedSemaphore, VkFence *const inFlightFence);
int recordCommandBuffer(PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, VkCommandBuffer* commandBuffer, const uint32_t imageIndex, const VkPipeline *const graphicsPipeline, const VkRenderPass *const renderPass, const VkExtent2D *const swapchainExtent, const VkFramebuffer *const swapchainFramebuffers);

char* getShaderCode(const char *const fileName, uint32_t *const pShaderSize);
VkShaderModule createShaderModule(PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, const char *const shader_code, const uint32_t shader_code_size);


int lvInitVulkan(lvParam *const lvparam, GLFWwindow *const window);

int drawFrame(lvData *const lvdata);

int lvTerminate(lvData *const lvdata);

#endif
