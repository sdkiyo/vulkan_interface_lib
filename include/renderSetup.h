#pragma once
#ifndef _LAVA_RENDER_INFO_H_
#define _LAVA_RENDER_INFO_H_

#include "vk.h"


int createRenderPass(
	const LoaderTable *const		pTable,
	const VkDevice *const			pDevice,
	const VkFormat *const			pSwapchainImageFormat,
	VkRenderPass*				pRenderPass);

int createGraphicsPipeline(
	const LoaderTable *const		pTable,
	const VkDevice *const			pDevice,
	VkPipelineLayout*			pPipelineLayout,
	VkPipeline*				pGraphicsPipeline,
	const VkRenderPass *const		pRenderPass,
	const VkDescriptorSetLayout *const	pDescriptorSetLayout);

#endif
