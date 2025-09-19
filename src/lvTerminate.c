#include "../include/vk.h"

int lvTerminate(lvData *const lvdata)
{
	for (int i = 0; i < IMAGE_COUNT; i++)
	{
		vkDestroySemaphore(lvdata->device, lvdata->renderFinishedSemaphore[i], nullptr);

		vkDestroySemaphore(lvdata->device, lvdata->imageAvailableSemaphore[i], nullptr);

		vkDestroyFence(lvdata->device, lvdata->inFlightFence[i], nullptr);
	}
	printf("destroy " YELLOW "syncObjects" RESET_COLOR "\n");

	vkDestroyCommandPool(lvdata->device, lvdata->commandPool, nullptr);
	printf("destroy " YELLOW "commandPool" RESET_COLOR "\n");

	for (int i = 0; i < IMAGE_COUNT; i++)
	{
		vkDestroyFramebuffer(lvdata->device, lvdata->swapchainFramebuffers[i], nullptr);
	}
	printf("destroy " YELLOW "framebuffer" RESET_COLOR "\n");

	vkDestroyPipeline(lvdata->device, lvdata->graphicsPipeline, nullptr);
	printf("destroy " YELLOW "graphicsPipeline" RESET_COLOR "\n");

	vkDestroyPipelineLayout(lvdata->device, lvdata->pipelineLayout, nullptr);
	printf("destroy " YELLOW "pipelineLayout" RESET_COLOR "\n");

	vkDestroyRenderPass(lvdata->device, lvdata->renderPass, nullptr);
	printf("destroy " YELLOW "renderPass" RESET_COLOR "\n");

	for (int i = 0; i < IMAGE_COUNT; i++)
	{
		vkDestroyImageView(lvdata->device, lvdata->swapchainImageViews[i], nullptr);
	}
	printf("destroy " YELLOW "imageViews" RESET_COLOR "\n");

	vkDestroySwapchainKHR(lvdata->device, lvdata->swapchain, nullptr);
	printf("destroy " YELLOW "swapchain" RESET_COLOR "\n");

	vkDestroyDevice(lvdata->device, nullptr);
	printf("destroy " YELLOW "device" RESET_COLOR "\n");

	vkDestroySurfaceKHR(lvdata->instance, lvdata->surface, nullptr);
	printf("destroy " YELLOW "surface" RESET_COLOR "\n");

	destroyDebugUtilsMessenger(&lvdata->instance, &lvdata->debugMessenger);
	printf("destroy " YELLOW "debugUtilsMessenger" RESET_COLOR "\n");

	vkDestroyInstance(lvdata->instance, nullptr);
	printf("destroy " YELLOW "instance" RESET_COLOR "\n");
	return 0;
}
