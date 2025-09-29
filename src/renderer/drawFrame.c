#include "vk.h"
#include "renderer.h"

int drawFrame(lvData *const lv, const LoaderTable *const pTable, const lvParam *const lvparam)
{
	pTable->pfn_vkWaitForFences(lv->device, 1, &lv->inFlightFence[lv->currentFrame], VK_TRUE, UINT64_MAX);
	pTable->pfn_vkResetFences(lv->device, 1, &lv->inFlightFence[lv->currentFrame]);

	uint32_t imageIndex = 0;
	pTable->pfn_vkAcquireNextImageKHR(lv->device, lv->swapchain, UINT64_MAX, lv->imageAvailableSemaphore[lv->currentFrame], VK_NULL_HANDLE, &imageIndex);

	updateUniformBuffer(lv->currentFrame, lv->uniformBuffersMapped, &lv->swapchainExtent, lvparam->pCam_pos, lvparam->pCam_target, lvparam->pCam_up, lvparam->fov, lvparam->near, lvparam->far);

	pTable->pfn_vkResetCommandBuffer(lv->commandBuffers[lv->currentFrame], 0);

	recordCommandBuffer(pTable, &lv->device, &lv->commandBuffers[lv->currentFrame], imageIndex, &lv->graphicsPipeline, &lv->renderPass, &lv->swapchainExtent, lv->swapchainFramebuffers, &lv->vertexBuffer, &lv->indexBuffer, &lv->pipelineLayout, lv->descriptorSets, lv->currentFrame, lvparam->indices_size);

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

	if (pTable->pfn_vkQueueSubmit(lv->queue, 1, &submitInfo, lv->inFlightFence[lv->currentFrame]) != VK_SUCCESS)
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

	pTable->pfn_vkQueuePresentKHR(lv->queue, &presentInfo);

	//lv->currentFrame = (lv->currentFrame == IMAGE_COUNT - 1) ? 0 : lv->currentFrame + 1;
	lv->currentFrame = (lv->currentFrame + 1) % IMAGE_COUNT;

	return 0;
}
