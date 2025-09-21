#include "../include/vk.h"

int drawFrame(lvData *const lv)
{
	printf("drawFrame()\n");

	PFN_vkWaitForFences pfn_vkWaitForFences = (PFN_vkWaitForFences)lv->pfn_vkGetDeviceProcAddr(lv->device, "vkWaitForFences");
	PFN_vkResetFences pfn_vkResetFences = (PFN_vkResetFences)lv->pfn_vkGetDeviceProcAddr(lv->device, "vkResetFences");
        pfn_vkWaitForFences(lv->device, 1, &lv->inFlightFence[lv->currentFrame], VK_TRUE, UINT64_MAX);
        pfn_vkResetFences(lv->device, 1, &lv->inFlightFence[lv->currentFrame]);

        uint32_t imageIndex = 0;
	PFN_vkAcquireNextImageKHR pfn_vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)lv->pfn_vkGetDeviceProcAddr(lv->device, "vkAcquireNextImageKHR");
        pfn_vkAcquireNextImageKHR(lv->device, lv->swapchain, UINT64_MAX, lv->imageAvailableSemaphore[lv->currentFrame], VK_NULL_HANDLE, &imageIndex);

	PFN_vkResetCommandBuffer pfn_vkResetCommandBuffer = (PFN_vkResetCommandBuffer)lv->pfn_vkGetDeviceProcAddr(lv->device, "vkResetCommandBuffer");
	pfn_vkResetCommandBuffer(lv->commandBuffers[lv->currentFrame], 0);

        recordCommandBuffer(lv->pfn_vkGetDeviceProcAddr, &lv->device, &lv->commandBuffers[lv->currentFrame], imageIndex, &lv->graphicsPipeline, &lv->renderPass, &lv->swapchainExtent, lv->swapchainFramebuffers);

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {lv->imageAvailableSemaphore[lv->currentFrame]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &lv->commandBuffers[lv->currentFrame];

        VkSemaphore signalSemaphores[] = {lv->renderFinishedSemaphore[lv->currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

	PFN_vkQueueSubmit pfn_vkQueueSubmit = (PFN_vkQueueSubmit)lv->pfn_vkGetDeviceProcAddr(lv->device, "vkQueueSubmit");
        if (pfn_vkQueueSubmit(lv->queue, 1, &submitInfo, lv->inFlightFence[lv->currentFrame]) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to vkQueueSubmit()'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
        }

        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapchains[] = {lv->swapchain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapchains;

        presentInfo.pImageIndices = &imageIndex;

	PFN_vkQueuePresentKHR pfn_vkQueuePresentKHR = (PFN_vkQueuePresentKHR)lv->pfn_vkGetDeviceProcAddr(lv->device, "vkQueuePresentKHR");
        pfn_vkQueuePresentKHR(lv->queue, &presentInfo);

	//lv->currentFrame = (lv->currentFrame == IMAGE_COUNT - 1) ? 0 : lv->currentFrame + 1;
	lv->currentFrame = (lv->currentFrame + 1) % IMAGE_COUNT;

	return 0;
}
