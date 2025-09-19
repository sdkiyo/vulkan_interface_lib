#pragma once
#ifndef _LAVA_VK_H_
#define _LAVA_VK_H_

#include "base_includes.h"

#define IMAGE_COUNT 5

typedef struct lvData{
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

	uint8_t currentFrame;
} lvData;

int lvCreateInstance(VkInstance *const instance);

void createDebugUtilsMessenger(const VkInstance *const instance, VkDebugUtilsMessengerEXT *const debugMessenger);

void destroyDebugUtilsMessenger(const VkInstance *const instance, VkDebugUtilsMessengerEXT *const debugMessenger);

int lvCreateSurface(GLFWwindow *const window, const VkInstance *const instance, VkSurfaceKHR *const surface);

int lvPickPhysicalDevice(const VkInstance *const instance, VkPhysicalDevice *const physicalDevice);

int createLogicalDevice(const VkPhysicalDevice *const physicalDevice, VkDevice *const device, VkQueue* queue);

int createSwapchain(VkPhysicalDevice* physicalDevice, VkSurfaceKHR* surface, VkDevice* device, VkSwapchainKHR *swapchain, VkImage* swapchainImages, VkFormat* swapchainImageFormat, VkExtent2D* swapchainExtent);

int createImageViews(VkDevice* device, VkFormat* swapchainImageFormat, VkImage* swapchainImages, VkImageView* swapchainImageViews);

int createRenderPass(VkDevice* device, VkFormat* swapchainImageFormat, VkRenderPass* renderPass);

int createFramebuffers(VkDevice* device, VkExtent2D* swapchainExtent, VkRenderPass* renderPass, VkImageView* swapchainImageViews, VkFramebuffer* swapchainFramebuffers);

char* getShaderCode(const char *const fileName, uint32_t *const pShaderSize);

VkShaderModule createShaderModule(const VkDevice *const device, const char* shader_code, const uint32_t shader_code_size);

int createGraphicsPipeline(const VkDevice *const device, VkPipelineLayout* pipelineLayout, VkPipeline* graphicsPipeline, VkRenderPass* renderPass);

int createCommandPool(const VkDevice *const device, VkCommandPool* commandPool);

int createCommandBuffer(const VkDevice *const device, VkCommandPool* commandPool, VkCommandBuffer* commandBuffer);

int createSyncObjects(const VkDevice *const device, VkSemaphore* imageAvailableSemaphore, VkSemaphore* renderFinishedSemaphore, VkFence* inFlightFence);

int recordCommandBuffer(VkCommandBuffer* commandBuffer, uint32_t imageIndex, VkPipeline* graphicsPipeline, VkRenderPass* renderPass, VkExtent2D* swapchainExtent, VkFramebuffer* swapchainFramebuffers);

int drawFrame(lvData *const lvdata);

void lvInitVulkan(lvData *const lvdata, GLFWwindow *const window);

int lvTerminate(lvData *const lvdata);

#endif
