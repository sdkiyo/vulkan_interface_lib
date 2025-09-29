#include "renderer.h"
#include "vertex.h"

int recordCommandBuffer(const LoaderTable *const pTable, const VkDevice *const pDevice, VkCommandBuffer* pCommandBuffer, const uint32_t imageIndex, const VkPipeline *const pGraphicsPipeline, const VkRenderPass *const pRenderPass, const VkExtent2D *const pSwapchainExtent, const VkFramebuffer *const pSwapchainFramebuffers, const VkBuffer *const pVertexBuffer, const VkBuffer *const pIndexBuffer, const VkPipelineLayout *const pPipelineLayout, VkDescriptorSet* pDescriptorSets, const uint32_t currentFrame, const uint32_t indices_size)
{
	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	if (pTable->pfn_vkBeginCommandBuffer(*pCommandBuffer, &beginInfo) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to vkBeginCommandBuffer()'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = *pRenderPass;
	renderPassInfo.framebuffer = pSwapchainFramebuffers[imageIndex];
	renderPassInfo.renderArea.offset = (VkOffset2D){0, 0};
	renderPassInfo.renderArea.extent = *pSwapchainExtent;

	VkClearValue clearColor = {{{0.01f, 0.01f, 0.01f, 1.0f}}};
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	pTable->pfn_vkCmdBeginRenderPass(*pCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	pTable->pfn_vkCmdBindPipeline(*pCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, *pGraphicsPipeline);

	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)(pSwapchainExtent->width);
	viewport.height = (float)(pSwapchainExtent->height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	pTable->pfn_vkCmdSetViewport(*pCommandBuffer, 0, 1, &viewport);

	VkRect2D scissor = {};
	scissor.offset = (VkOffset2D){0, 0};
	scissor.extent = *pSwapchainExtent;

	pTable->pfn_vkCmdSetScissor(*pCommandBuffer, 0, 1, &scissor);

	VkBuffer vertexBuffers[] = {*pVertexBuffer};
	VkDeviceSize offsets[] = {0};

	pTable->pfn_vkCmdBindVertexBuffers(*pCommandBuffer, 0, 1, vertexBuffers, offsets);
	pTable->pfn_vkCmdBindIndexBuffer(*pCommandBuffer, *pIndexBuffer, 0, VK_INDEX_TYPE_UINT16);

	pTable->pfn_vkCmdBindDescriptorSets(*pCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, *pPipelineLayout, 0, 1, &pDescriptorSets[currentFrame], 0, nullptr);

	pTable->pfn_vkCmdDrawIndexed(*pCommandBuffer, indices_size, 1, 0, 0, 0);

	pTable->pfn_vkCmdEndRenderPass(*pCommandBuffer);

	if (pTable->pfn_vkEndCommandBuffer(*pCommandBuffer) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to vkEndCommandBuffer()'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	return 0;
}
