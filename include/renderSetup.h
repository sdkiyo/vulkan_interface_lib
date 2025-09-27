#pragma once
#ifndef _LAVA_RENDER_INFO_H_
#define _LAVA_RENDER_INFO_H_

#include "vk.h"


int createRenderPass(
	const LoaderTable *const		pTable,
	const VkDevice *const			device,
	const VkFormat *const			swapchainImageFormat,
	VkRenderPass*				renderPass);

int createGraphicsPipeline(
	const LoaderTable *const		pTable,
	const VkDevice *const			device,
	VkPipelineLayout*			pipelineLayout,
	VkPipeline*				graphicsPipeline,
	const VkRenderPass *const		renderPass,
	const VkDescriptorSetLayout *const	descriptorSetLayout);

#endif
