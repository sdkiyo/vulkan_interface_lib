#include "../include/vk.h"

int drawFrame(lvData *const lv)
{
	fprintf(stderr, "hel\n");
        vkWaitForFences(lv->device, 1, &lv->inFlightFence[lv->currentFrame], VK_TRUE, UINT64_MAX);
	fprintf(stderr, "hel2\n");
        vkResetFences(lv->device, 1, &lv->inFlightFence[lv->currentFrame]);

        uint32_t imageIndex;
        vkAcquireNextImageKHR(lv->device, lv->swapchain, UINT64_MAX, lv->imageAvailableSemaphore[lv->currentFrame], VK_NULL_HANDLE, &imageIndex);

        vkResetCommandBuffer(lv->commandBuffers[lv->currentFrame], 0);
        recordCommandBuffer(&lv->commandBuffers[lv->currentFrame], imageIndex, &lv->graphicsPipeline, &lv->renderPass, &lv->swapchainExtent, lv->swapchainFramebuffers);

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

        if (vkQueueSubmit(lv->queue, 1, &submitInfo, lv->inFlightFence[lv->currentFrame]) != VK_SUCCESS)
	{
		printf("df\n");
        }

        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapchains[] = {lv->swapchain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapchains;

        presentInfo.pImageIndices = &imageIndex;

        vkQueuePresentKHR(lv->queue, &presentInfo);

	lv->currentFrame = (lv->currentFrame == IMAGE_COUNT - 1) ? 0 : lv->currentFrame + 1;
	printf("drawFrame()\n");
}
