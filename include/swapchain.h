#pragma once
#ifndef _LAVA_SWAPCHAIN_H_
#define _LAVA_SWAPCHAIN_H_

#include "vk.h"


int createSwapchain(
	const LoaderTable *const		pTable,
	const VkInstance *const			instance,
	const VkPhysicalDevice *const		physicalDevice,
	const VkSurfaceKHR *const		surface,
	const VkDevice *const			device,
	VkSwapchainKHR*				swapchain,
	VkImage*				swapchainImages,
	VkFormat*				swapchainImageFormat,
	VkExtent2D*				swapchainExtent);

int createImageViews(
	const LoaderTable *const		pTable,
	const VkDevice *const			device,
	const VkFormat *const			swapchainImageFormat,
	const VkImage *const			swapchainImages,
	VkImageView*				swapchainImageViews);

int createFramebuffers(
	const LoaderTable *const		pTable,
	const VkDevice *const			device,
	const VkExtent2D *const			swapchainExtent,
	const VkRenderPass *const		renderPass,
	const VkImageView *const		swapchainImageViews,
	VkFramebuffer*				swapchainFramebuffers);


#endif
