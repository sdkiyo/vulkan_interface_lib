#include "vk.h"

int lvTerminate(lvData *const lvdata)
{
	printf(YELLOW "vulkanTerminate() " RESET_COLOR GRAY "start" RESET_COLOR "\n");


	const PFN_vkDestroySemaphore pfn_vkDestroySemaphore = (PFN_vkDestroySemaphore) lvdata->pfn_vkGetDeviceProcAddr(lvdata->device, "vkDestroySemaphore");
	const PFN_vkDestroyFence pfn_vkDestroyFence = (PFN_vkDestroyFence) lvdata->pfn_vkGetDeviceProcAddr(lvdata->device, "vkDestroyFence");
	for (uint32_t i = 0; i < IMAGE_COUNT; i++)
	{
		pfn_vkDestroySemaphore(lvdata->device, lvdata->renderFinishedSemaphore[i], nullptr);

		pfn_vkDestroySemaphore(lvdata->device, lvdata->imageAvailableSemaphore[i], nullptr);

		pfn_vkDestroyFence(lvdata->device, lvdata->inFlightFence[i], nullptr);
	}
	printf("- destroy " YELLOW "syncObjects" RESET_COLOR "\n");

	const PFN_vkDestroyCommandPool pfn_vkDestroyCommandPool = (PFN_vkDestroyCommandPool) lvdata->pfn_vkGetDeviceProcAddr(lvdata->device, "vkDestroyCommandPool");
	pfn_vkDestroyCommandPool(lvdata->device, lvdata->commandPool, nullptr);
	printf(YELLOW "- vkDestroyCommandPool()" RESET_COLOR "\n");

	const PFN_vkDestroyFramebuffer pfn_vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer) lvdata->pfn_vkGetDeviceProcAddr(lvdata->device, "vkDestroyFramebuffer");
	for (uint32_t i = 0; i < IMAGE_COUNT; i++)
	{
		pfn_vkDestroyFramebuffer(lvdata->device, lvdata->swapchainFramebuffers[i], nullptr);
	}
	printf("- destroy " YELLOW "framebuffer" RESET_COLOR "\n");

	const PFN_vkDestroyPipeline pfn_vkDestroyPipeline = (PFN_vkDestroyPipeline) lvdata->pfn_vkGetDeviceProcAddr(lvdata->device, "vkDestroyPipeline");
	pfn_vkDestroyPipeline(lvdata->device, lvdata->graphicsPipeline, nullptr);
	printf(YELLOW "- vkDestroyPipeline()" RESET_COLOR "\n");

	const PFN_vkDestroyPipelineLayout pfn_vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout) lvdata->pfn_vkGetDeviceProcAddr(lvdata->device, "vkDestroyPipelineLayout");
	pfn_vkDestroyPipelineLayout(lvdata->device, lvdata->pipelineLayout, nullptr);
	printf(YELLOW "- vkDestroyPipelineLayout()" RESET_COLOR "\n");

	const PFN_vkDestroyRenderPass pfn_vkDestroyRenderPass = (PFN_vkDestroyRenderPass) lvdata->pfn_vkGetDeviceProcAddr(lvdata->device, "vkDestroyRenderPass");
	pfn_vkDestroyRenderPass(lvdata->device, lvdata->renderPass, nullptr);
	printf(YELLOW "- vkDestroyRenderPass()" RESET_COLOR "\n");

	const PFN_vkDestroyBuffer pfn_vkDestroyBuffer = (PFN_vkDestroyBuffer) lvdata->pfn_vkGetDeviceProcAddr(lvdata->device, "vkDestroyBuffer");
	const PFN_vkFreeMemory pfn_vkFreeMemory = (PFN_vkFreeMemory) lvdata->pfn_vkGetDeviceProcAddr(lvdata->device, "vkFreeMemory");
	pfn_vkDestroyBuffer(lvdata->device, lvdata->vertexBuffer, nullptr);
	printf(YELLOW "- vkDestroyBuffer() vertex" RESET_COLOR "\n");
	pfn_vkFreeMemory(lvdata->device, lvdata->vertexBufferMemory, nullptr);
	printf(YELLOW "- vkFreeMemory() vertex" RESET_COLOR "\n");

	pfn_vkDestroyBuffer(lvdata->device, lvdata->indexBuffer, nullptr);
	printf(YELLOW "- vkDestroyBuffer() index" RESET_COLOR "\n");
	pfn_vkFreeMemory(lvdata->device, lvdata->indexBufferMemory, nullptr);
	printf(YELLOW "- vkFreeMemory() index" RESET_COLOR "\n");

	const PFN_vkDestroyImageView pfn_vkDestroyImageView = (PFN_vkDestroyImageView) lvdata->pfn_vkGetDeviceProcAddr(lvdata->device, "vkDestroyImageView");
	for (int i = 0; i < IMAGE_COUNT; i++)
	{
		pfn_vkDestroyImageView(lvdata->device, lvdata->swapchainImageViews[i], nullptr);
	}
	printf("- destroy " YELLOW "imageViews" RESET_COLOR "\n");

	const PFN_vkDestroySwapchainKHR pfn_vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR) lvdata->pfn_vkGetDeviceProcAddr(lvdata->device, "vkDestroySwapchainKHR");
	pfn_vkDestroySwapchainKHR(lvdata->device, lvdata->swapchain, nullptr);
	printf(YELLOW "- vkDestroySwapchainKHR()" RESET_COLOR "\n");

	const PFN_vkDestroyDevice pfn_vkDestroyDevice = (PFN_vkDestroyDevice) lvdata->pfn_vkGetDeviceProcAddr(lvdata->device, "vkDestroyDevice");
	pfn_vkDestroyDevice(lvdata->device, nullptr);
	printf(YELLOW "- vkDestroyDevice()" RESET_COLOR "\n");

	const PFN_vkDestroySurfaceKHR pfn_vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR) lvdata->pfn_vkGetInstanceProcAddr(lvdata->instance, "vkDestroySurfaceKHR");
	pfn_vkDestroySurfaceKHR(lvdata->instance, lvdata->surface, nullptr);
	printf(YELLOW "- vkDestroySurfaceKHR()" RESET_COLOR "\n");

	const PFN_vkDestroyDebugUtilsMessengerEXT pfn_vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT) lvdata->pfn_vkGetInstanceProcAddr(lvdata->instance, "vkDestroyDebugUtilsMessengerEXT");
   	pfn_vkDestroyDebugUtilsMessengerEXT(lvdata->instance, lvdata->debugMessenger, nullptr);
	printf(YELLOW "- destroyDebugUtilsMessenger()" RESET_COLOR "\n");

	const PFN_vkDestroyInstance pfn_vkDestroyInstance = (PFN_vkDestroyInstance) lvdata->pfn_vkGetInstanceProcAddr(lvdata->instance, "vkDestroyInstance");
	pfn_vkDestroyInstance(lvdata->instance, nullptr);
	printf(YELLOW "- vkDestroyInstance()" RESET_COLOR "\n");

	printf(YELLOW "vulkanTerminate() " RESET_COLOR GRAY "end" RESET_COLOR "\n");
	return 0;
}
