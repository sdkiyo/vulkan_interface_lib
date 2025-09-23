#include "vk.h"

int lvTerminate(lvData *const lvdata, const LoaderTable *const pTable)
{
	printf(YELLOW "vulkanTerminate() " RESET_COLOR GRAY "start" RESET_COLOR "\n");


	for (uint32_t i = 0; i < IMAGE_COUNT; i++)
	{
		pTable->pfn_vkDestroySemaphore(lvdata->device, lvdata->renderFinishedSemaphore[i], nullptr);

		pTable->pfn_vkDestroySemaphore(lvdata->device, lvdata->imageAvailableSemaphore[i], nullptr);

		pTable->pfn_vkDestroyFence(lvdata->device, lvdata->inFlightFence[i], nullptr);
	}
	printf("- destroy " YELLOW "syncObjects" RESET_COLOR "\n");

	pTable->pfn_vkDestroyCommandPool(lvdata->device, lvdata->commandPool, nullptr);
	printf(YELLOW "- vkDestroyCommandPool()" RESET_COLOR "\n");

	for (uint32_t i = 0; i < IMAGE_COUNT; i++)
	{
		pTable->pfn_vkDestroyFramebuffer(lvdata->device, lvdata->swapchainFramebuffers[i], nullptr);
	}
	printf("- destroy " YELLOW "framebuffer" RESET_COLOR "\n");

	pTable->pfn_vkDestroyPipeline(lvdata->device, lvdata->graphicsPipeline, nullptr);
	printf(YELLOW "- vkDestroyPipeline()" RESET_COLOR "\n");

	pTable->pfn_vkDestroyPipelineLayout(lvdata->device, lvdata->pipelineLayout, nullptr);
	printf(YELLOW "- vkDestroyPipelineLayout()" RESET_COLOR "\n");

	pTable->pfn_vkDestroyRenderPass(lvdata->device, lvdata->renderPass, nullptr);
	printf(YELLOW "- vkDestroyRenderPass()" RESET_COLOR "\n");

	pTable->pfn_vkDestroyBuffer(lvdata->device, lvdata->vertexBuffer, nullptr);
	printf(YELLOW "- vkDestroyBuffer() vertex" RESET_COLOR "\n");
	pTable->pfn_vkFreeMemory(lvdata->device, lvdata->vertexBufferMemory, nullptr);
	printf(YELLOW "- vkFreeMemory() vertex" RESET_COLOR "\n");

	pTable->pfn_vkDestroyBuffer(lvdata->device, lvdata->indexBuffer, nullptr);
	printf(YELLOW "- vkDestroyBuffer() index" RESET_COLOR "\n");
	pTable->pfn_vkFreeMemory(lvdata->device, lvdata->indexBufferMemory, nullptr);
	printf(YELLOW "- vkFreeMemory() index" RESET_COLOR "\n");

	for (int i = 0; i < IMAGE_COUNT; i++)
	{
		pTable->pfn_vkDestroyImageView(lvdata->device, lvdata->swapchainImageViews[i], nullptr);
	}
	printf("- destroy " YELLOW "imageViews" RESET_COLOR "\n");

	pTable->pfn_vkDestroySwapchainKHR(lvdata->device, lvdata->swapchain, nullptr);
	printf(YELLOW "- vkDestroySwapchainKHR()" RESET_COLOR "\n");

	pTable->pfn_vkDestroyDevice(lvdata->device, nullptr);
	printf(YELLOW "- vkDestroyDevice()" RESET_COLOR "\n");

	pTable->pfn_vkDestroySurfaceKHR(lvdata->instance, lvdata->surface, nullptr);
	printf(YELLOW "- vkDestroySurfaceKHR()" RESET_COLOR "\n");

   	pTable->pfn_vkDestroyDebugUtilsMessengerEXT(lvdata->instance, lvdata->debugMessenger, nullptr);
	printf(YELLOW "- destroyDebugUtilsMessenger()" RESET_COLOR "\n");

	pTable->pfn_vkDestroyInstance(lvdata->instance, nullptr);
	printf(YELLOW "- vkDestroyInstance()" RESET_COLOR "\n");

	dlclose(pTable->vkLib);
	printf(YELLOW "- close libvulkan.so" RESET_COLOR "\n");

	printf(YELLOW "vulkanTerminate() " RESET_COLOR GRAY "end" RESET_COLOR "\n");
	return 0;
}
