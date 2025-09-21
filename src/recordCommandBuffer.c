#include "../include/vk.h"

int recordCommandBuffer(PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, VkCommandBuffer* commandBuffer, const uint32_t imageIndex, const VkPipeline *const graphicsPipeline, const VkRenderPass *const renderPass, const VkExtent2D *const swapchainExtent, const VkFramebuffer *const swapchainFramebuffers)
{
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	PFN_vkBeginCommandBuffer pfn_vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)pfn_vkGetDeviceProcAddr(*device, "vkBeginCommandBuffer");
        if (pfn_vkBeginCommandBuffer(*commandBuffer, &beginInfo) != VK_SUCCESS)
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

	PFN_vkCmdBeginRenderPass pfn_vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)pfn_vkGetDeviceProcAddr(*device, "vkCmdBeginRenderPass");
        pfn_vkCmdBeginRenderPass(*commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	PFN_vkCmdBindPipeline pfn_vkCmdBindPipeline = (PFN_vkCmdBindPipeline)pfn_vkGetDeviceProcAddr(*device, "vkCmdBindPipeline");
        pfn_vkCmdBindPipeline(*commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, *graphicsPipeline);

        VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)(swapchainExtent->width);
        viewport.height = (float)(swapchainExtent->height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
	PFN_vkCmdSetViewport pfn_vkCmdSetViewport = (PFN_vkCmdSetViewport)pfn_vkGetDeviceProcAddr(*device, "vkCmdSetViewport");
        pfn_vkCmdSetViewport(*commandBuffer, 0, 1, &viewport);

        VkRect2D scissor = {};
        scissor.offset = (VkOffset2D){0, 0};
        scissor.extent = *swapchainExtent;
	PFN_vkCmdSetScissor pfn_vkCmdSetScissor = (PFN_vkCmdSetScissor)pfn_vkGetDeviceProcAddr(*device, "vkCmdSetScissor");
        pfn_vkCmdSetScissor(*commandBuffer, 0, 1, &scissor);

	PFN_vkCmdDraw pfn_vkCmdDraw = (PFN_vkCmdDraw)pfn_vkGetDeviceProcAddr(*device, "vkCmdDraw");
        pfn_vkCmdDraw(*commandBuffer, 3, 1, 0, 0);

	PFN_vkCmdEndRenderPass pfn_vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)pfn_vkGetDeviceProcAddr(*device, "vkCmdEndRenderPass");
        pfn_vkCmdEndRenderPass(*commandBuffer);

	PFN_vkEndCommandBuffer pfn_vkEndCommandBuffer = (PFN_vkEndCommandBuffer)pfn_vkGetDeviceProcAddr(*device, "vkEndCommandBuffer");
        if (pfn_vkEndCommandBuffer(*commandBuffer) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to vkEndCommandBuffer()'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
        }

	return 0;
}
