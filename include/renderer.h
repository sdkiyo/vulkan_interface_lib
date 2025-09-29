#pragma once
#ifndef _LAVA_RENDERER_H_
#define _LAVA_RENDERER_H_

#include "vk.h"


int createCommandPool(
	const LoaderTable *const		pTable,
	const VkDevice *const			pDevice,
	VkCommandPool*				pCommandPool);

int createCommandBuffer(
	const LoaderTable *const		pTable,
	const VkDevice *const			pDevice,
	VkCommandPool*				pCommandPool,
	VkCommandBuffer*			pCommandBuffers);

int createSyncObjects(
	const LoaderTable *const		pTable,
	const VkDevice *const			pDevice,
	VkSemaphore *const			pImageAvailableSemaphore,
	VkSemaphore *const			pRenderFinishedSemaphore,
	VkFence *const				pInFlightFence);

int recordCommandBuffer(
	const LoaderTable *const		pTable,
	const VkDevice *const			pDevice,
	VkCommandBuffer*			pCommandBuffer,
	const uint32_t				imageIndex,
	const VkPipeline *const			pGraphicsPipeline,
	const VkRenderPass *const		pRenderPass,
	const VkExtent2D *const			pSwapchainExtent,
	const VkFramebuffer *const		pSwapchainFramebuffers,
	const VkBuffer *const			pVertexBuffer,
	const VkBuffer *const			pIndexBuffer,
	const VkPipelineLayout *const		pPipelineLayout,
	VkDescriptorSet*			pDescriptorSets,
	const uint32_t				currentFrame,
	const uint32_t				indices_size);


#endif
