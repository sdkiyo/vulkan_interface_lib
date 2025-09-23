#pragma once
#ifndef _LAVA_FUNC_LOADER_H_
#define _LAVA_FUNC_LOADER_H_

#include "base_includes.h"

typedef struct LoaderTable {
//----------PRE------------
	void* vkLib;
	PFN_vkGetInstanceProcAddr		pfn_vkGetInstanceProcAddr;
	PFN_vkGetDeviceProcAddr			pfn_vkGetDeviceProcAddr;
	PFN_vkCreateInstance			pfn_vkCreateInstance;
//----------INSTANCE------------
	PFN_vkEnumeratePhysicalDevices				pfn_vkEnumeratePhysicalDevices;
	PFN_vkCreateDebugUtilsMessengerEXT			pfn_vkCreateDebugUtilsMessengerEXT;
	PFN_vkCreateDevice					pfn_vkCreateDevice;
	PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR		pfn_vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
	PFN_vkGetPhysicalDeviceMemoryProperties			pfn_vkGetPhysicalDeviceMemoryProperties;
	PFN_vkDestroySurfaceKHR					pfn_vkDestroySurfaceKHR;
	PFN_vkDestroyDebugUtilsMessengerEXT			pfn_vkDestroyDebugUtilsMessengerEXT;
	PFN_vkDestroyInstance					pfn_vkDestroyInstance;
//----------DEVICE------------
	PFN_vkCreatePipelineLayout		pfn_vkCreatePipelineLayout;
	PFN_vkCreateGraphicsPipelines		pfn_vkCreateGraphicsPipelines;
	PFN_vkDestroyShaderModule		pfn_vkDestroyShaderModule;
	PFN_vkCreateRenderPass			pfn_vkCreateRenderPass;
	PFN_vkQueuePresentKHR			pfn_vkQueuePresentKHR;
	PFN_vkQueueSubmit			pfn_vkQueueSubmit;
	PFN_vkResetCommandBuffer		pfn_vkResetCommandBuffer;
	PFN_vkAcquireNextImageKHR		pfn_vkAcquireNextImageKHR;
	PFN_vkWaitForFences			pfn_vkWaitForFences;
	PFN_vkResetFences			pfn_vkResetFences;
	PFN_vkCmdBindVertexBuffers		pfn_vkCmdBindVertexBuffers;
	PFN_vkCmdBindIndexBuffer		pfn_vkCmdBindIndexBuffer;
	PFN_vkCmdDrawIndexed			pfn_vkCmdDrawIndexed;
	PFN_vkEndCommandBuffer			pfn_vkEndCommandBuffer;
	PFN_vkCmdEndRenderPass			pfn_vkCmdEndRenderPass;
	PFN_vkCmdSetViewport			pfn_vkCmdSetViewport;
	PFN_vkCmdSetScissor			pfn_vkCmdSetScissor;
	PFN_vkCmdBeginRenderPass		pfn_vkCmdBeginRenderPass;
	PFN_vkBeginCommandBuffer		pfn_vkBeginCommandBuffer;
	PFN_vkCmdBindPipeline			pfn_vkCmdBindPipeline;
	PFN_vkCreateSemaphore			pfn_vkCreateSemaphore;
	PFN_vkCreateFence			pfn_vkCreateFence;
	PFN_vkCreateCommandPool			pfn_vkCreateCommandPool;
	PFN_vkAllocateCommandBuffers		pfn_vkAllocateCommandBuffers;
	PFN_vkCreateShaderModule		pfn_vkCreateShaderModule;
	PFN_vkCreateFramebuffer			pfn_vkCreateFramebuffer;
	PFN_vkCreateImageView			pfn_vkCreateImageView;
	PFN_vkCreateSwapchainKHR		pfn_vkCreateSwapchainKHR;
	PFN_vkGetSwapchainImagesKHR		pfn_vkGetSwapchainImagesKHR;
	PFN_vkUnmapMemory			pfn_vkUnmapMemory;
	PFN_vkMapMemory				pfn_vkMapMemory;
	PFN_vkDestroyBuffer			pfn_vkDestroyBuffer;
	PFN_vkFreeMemory			pfn_vkFreeMemory;
	PFN_vkBindBufferMemory			pfn_vkBindBufferMemory;
	PFN_vkAllocateMemory			pfn_vkAllocateMemory;
	PFN_vkGetBufferMemoryRequirements	pfn_vkGetBufferMemoryRequirements;
	PFN_vkCreateBuffer			pfn_vkCreateBuffer;
	PFN_vkCmdCopyBuffer			pfn_vkCmdCopyBuffer;
	PFN_vkFreeCommandBuffers		pfn_vkFreeCommandBuffers;
	PFN_vkQueueWaitIdle			pfn_vkQueueWaitIdle;
	PFN_vkDestroySemaphore			pfn_vkDestroySemaphore;
	PFN_vkDestroyFence			pfn_vkDestroyFence;
	PFN_vkDestroyCommandPool		pfn_vkDestroyCommandPool;
	PFN_vkDestroyFramebuffer		pfn_vkDestroyFramebuffer;
	PFN_vkDestroyPipeline			pfn_vkDestroyPipeline;
	PFN_vkDestroyRenderPass			pfn_vkDestroyRenderPass;
	PFN_vkDestroyPipelineLayout		pfn_vkDestroyPipelineLayout;
	PFN_vkDestroyImageView			pfn_vkDestroyImageView;
	PFN_vkDestroySwapchainKHR		pfn_vkDestroySwapchainKHR;
	PFN_vkDestroyDevice			pfn_vkDestroyDevice;
} LoaderTable;

int funcPreLoader(
	LoaderTable *const pTable);

int funcInstanceLoader(
	LoaderTable *const pTable,
	const VkInstance *const instance);

int funcDeviceLoader(
	LoaderTable *const pTable,
	const VkDevice *const device);


#endif
