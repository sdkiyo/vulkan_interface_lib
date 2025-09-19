#include "../include/vk.h"

int recordCommandBuffer(VkCommandBuffer* commandBuffer, uint32_t imageIndex, VkPipeline* graphicsPipeline, VkRenderPass* renderPass, VkExtent2D* swapchainExtent, VkFramebuffer* swapchainFramebuffers)
{
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(*commandBuffer, &beginInfo) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create instance'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = *renderPass;
        renderPassInfo.framebuffer = swapchainFramebuffers[imageIndex];
        renderPassInfo.renderArea.offset = (VkOffset2D){0, 0};
        renderPassInfo.renderArea.extent = *swapchainExtent;

        VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(*commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(*commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, *graphicsPipeline);

        VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)(swapchainExtent->width);
        viewport.height = (float)(swapchainExtent->height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(*commandBuffer, 0, 1, &viewport);

        VkRect2D scissor = {};
        scissor.offset = (VkOffset2D){0, 0};
        scissor.extent = *swapchainExtent;
        vkCmdSetScissor(*commandBuffer, 0, 1, &scissor);

        vkCmdDraw(*commandBuffer, 3, 1, 0, 0);

        vkCmdEndRenderPass(*commandBuffer);

        if (vkEndCommandBuffer(*commandBuffer) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create instance'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
        }
	return 0;
}
