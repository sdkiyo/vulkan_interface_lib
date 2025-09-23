#include "renderer.h"
#include "vertex.h"

int recordCommandBuffer(const LoaderTable *const pTable, const VkDevice *const device, VkCommandBuffer* commandBuffer, const uint32_t imageIndex, const VkPipeline *const graphicsPipeline, const VkRenderPass *const renderPass, const VkExtent2D *const swapchainExtent, const VkFramebuffer *const swapchainFramebuffers, const VkBuffer *const vertexBuffer, const VkBuffer *const indexBuffer)
{
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (pTable->pfn_vkBeginCommandBuffer(*commandBuffer, &beginInfo) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to vkBeginCommandBuffer()'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = *renderPass;
        renderPassInfo.framebuffer = swapchainFramebuffers[imageIndex];
        renderPassInfo.renderArea.offset = (VkOffset2D){0, 0};
        renderPassInfo.renderArea.extent = *swapchainExtent;

        VkClearValue clearColor = {{{0.01f, 0.01f, 0.01f, 1.0f}}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        pTable->pfn_vkCmdBeginRenderPass(*commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        pTable->pfn_vkCmdBindPipeline(*commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, *graphicsPipeline);

        VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)(swapchainExtent->width);
        viewport.height = (float)(swapchainExtent->height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        pTable->pfn_vkCmdSetViewport(*commandBuffer, 0, 1, &viewport);

        VkRect2D scissor = {};
        scissor.offset = (VkOffset2D){0, 0};
        scissor.extent = *swapchainExtent;
        pTable->pfn_vkCmdSetScissor(*commandBuffer, 0, 1, &scissor);


            VkBuffer vertexBuffers[] = {*vertexBuffer};
            VkDeviceSize offsets[] = {0};
            pTable->pfn_vkCmdBindVertexBuffers(*commandBuffer, 0, 1, vertexBuffers, offsets);

            pTable->pfn_vkCmdBindIndexBuffer(*commandBuffer, *indexBuffer, 0, VK_INDEX_TYPE_UINT16);

            pTable->pfn_vkCmdDrawIndexed(*commandBuffer, INDICES_SIZE, 1, 0, 0, 0);


        pTable->pfn_vkCmdEndRenderPass(*commandBuffer);

        if (pTable->pfn_vkEndCommandBuffer(*commandBuffer) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to vkEndCommandBuffer()'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
        }

	return 0;
}
