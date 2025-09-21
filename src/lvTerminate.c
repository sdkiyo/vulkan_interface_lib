#include "../include/vk.h"

int lvTerminate(lvData *const lvdata)
{
	printf(YELLOW "vulkanTerminate() " RESET_COLOR GRAY "start" RESET_COLOR "\n");

	for (uint32_t i = 0; i < IMAGE_COUNT; i++)
	{
		vkDestroySemaphore(lvdata->device, lvdata->renderFinishedSemaphore[i], nullptr);

		vkDestroySemaphore(lvdata->device, lvdata->imageAvailableSemaphore[i], nullptr);

		vkDestroyFence(lvdata->device, lvdata->inFlightFence[i], nullptr);
	}
	printf("- destroy " YELLOW "syncObjects" RESET_COLOR "\n");

	vkDestroyCommandPool(lvdata->device, lvdata->commandPool, nullptr);
	printf(YELLOW "- vkDestroyCommandPool()" RESET_COLOR "\n");

	for (uint32_t i = 0; i < IMAGE_COUNT; i++)
	{
		vkDestroyFramebuffer(lvdata->device, lvdata->swapchainFramebuffers[i], nullptr);
	}
	printf("- destroy " YELLOW "framebuffer" RESET_COLOR "\n");

	vkDestroyPipeline(lvdata->device, lvdata->graphicsPipeline, nullptr);
	printf(YELLOW "- vkDestroyPipeline()" RESET_COLOR "\n");

	vkDestroyPipelineLayout(lvdata->device, lvdata->pipelineLayout, nullptr);
	printf(YELLOW "- vkDestroyPipelineLayout()" RESET_COLOR "\n");

	vkDestroyRenderPass(lvdata->device, lvdata->renderPass, nullptr);
	printf(YELLOW "- vkDestroyRenderPass()" RESET_COLOR "\n");

	for (int i = 0; i < IMAGE_COUNT; i++)
	{
		vkDestroyImageView(lvdata->device, lvdata->swapchainImageViews[i], nullptr);
	}
	printf("- destroy " YELLOW "imageViews" RESET_COLOR "\n");

	vkDestroySwapchainKHR(lvdata->device, lvdata->swapchain, nullptr);
	printf(YELLOW "- vkDestroySwapchainKHR()" RESET_COLOR "\n");

	vkDestroyDevice(lvdata->device, nullptr);
	printf(YELLOW "- vkDestroyDevice()" RESET_COLOR "\n");

	vkDestroySurfaceKHR(lvdata->instance, lvdata->surface, nullptr);
	printf(YELLOW "- vkDestroySurfaceKHR()" RESET_COLOR "\n");

	destroyDebugUtilsMessenger(&lvdata->instance, &lvdata->debugMessenger);
	printf(YELLOW "- destroyDebugUtilsMessenger()" RESET_COLOR "\n");

	vkDestroyInstance(lvdata->instance, nullptr);
	printf(YELLOW "- vkDestroyInstance()" RESET_COLOR "\n");

	printf(YELLOW "vulkanTerminate() " RESET_COLOR GRAY "end" RESET_COLOR "\n");
	return 0;
}
