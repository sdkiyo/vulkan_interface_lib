#pragma once
#ifndef _LAVA_RENDERER_H_
#define _LAVA_RENDERER_H_

#include "vk.h"


int createCommandPool(
	const LoaderTable *const		pTable,
	const VkDevice *const			device,
	VkCommandPool*				commandPool);

int createCommandBuffer(
	const LoaderTable *const		pTable,
	const VkDevice *const			device,
	VkCommandPool*				commandPool,
	VkCommandBuffer*			commandBuffers);

int createSyncObjects(
	const LoaderTable *const		pTable,
	const VkDevice *const			device,
	VkSemaphore *const			imageAvailableSemaphore,
	VkSemaphore *const			renderFinishedSemaphore,
	VkFence *const				inFlightFence);

int recordCommandBuffer(
	const LoaderTable *const		pTable,
	const VkDevice *const			device,
	VkCommandBuffer*			commandBuffer,
	const uint32_t				imageIndex,
	const VkPipeline *const			graphicsPipeline,
	const VkRenderPass *const		renderPass,
	const VkExtent2D *const			swapchainExtent,
	const VkFramebuffer *const		swapchainFramebuffers,
	const VkBuffer *const			vertexBuffer,
	const VkBuffer *const			indexBuffer,
	const VkPipelineLayout *const		pipelineLayout,
	VkDescriptorSet*			descriptorSets,
	const uint32_t				currentFrame);


#endif
