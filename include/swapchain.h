#pragma once
#ifndef _LAVA_SWAPCHAIN_H_
#define _LAVA_SWAPCHAIN_H_

#include "vk.h"


int createSwapchain(
	const LoaderTable *const		pTable,
	const VkInstance *const			pInstance,
	const VkPhysicalDevice *const		pPhysicalDevice,
	const VkSurfaceKHR *const		pSurface,
	const VkDevice *const			pDevice,
	VkSwapchainKHR*				pSwapchain,
	VkImage*				pSwapchainImages,
	VkFormat*				pSwapchainImageFormat,
	VkExtent2D*				pSwapchainExtent);

int createImageViews(
	const LoaderTable *const		pTable,
	const VkDevice *const			pDevice,
	const VkFormat *const			pSwapchainImageFormat,
	const VkImage *const			pSwapchainImages,
	VkImageView*				pSwapchainImageViews);

int createFramebuffers(
	const LoaderTable *const		pTable,
	const VkDevice *const			pDevice,
	const VkExtent2D *const			pSwapchainExtent,
	const VkRenderPass *const		pRenderPass,
	const VkImageView *const		pSwapchainImageViews,
	VkFramebuffer*				pSwapchainFramebuffers);


#endif
