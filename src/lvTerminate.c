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

	pTable->pfn_vkDestroyCommandPool(lvdata->device, lvdata->commandPool, nullptr);

	for (uint32_t i = 0; i < IMAGE_COUNT; i++)
	{
		pTable->pfn_vkDestroyFramebuffer(lvdata->device, lvdata->swapchainFramebuffers[i], nullptr);
	}

	pTable->pfn_vkDestroyPipeline(lvdata->device, lvdata->graphicsPipeline, nullptr);

	pTable->pfn_vkDestroyPipelineLayout(lvdata->device, lvdata->pipelineLayout, nullptr);

	pTable->pfn_vkDestroyRenderPass(lvdata->device, lvdata->renderPass, nullptr);

	for (uint32_t i = 0; i < IMAGE_COUNT; i++)
	{
		pTable->pfn_vkDestroyBuffer(lvdata->device, lvdata->uniformBuffers[i], nullptr);
		pTable->pfn_vkFreeMemory(lvdata->device, lvdata->uniformBuffersMemory[i], nullptr);
	}


        pTable->pfn_vkDestroyDescriptorPool(lvdata->device, lvdata->descriptorPool, nullptr);


	pTable->pfn_vkDestroyDescriptorSetLayout(lvdata->device, lvdata->descriptorSetLayout, nullptr);

	pTable->pfn_vkDestroyBuffer(lvdata->device, lvdata->vertexBuffer, nullptr);

	pTable->pfn_vkFreeMemory(lvdata->device, lvdata->vertexBufferMemory, nullptr);

	pTable->pfn_vkDestroyBuffer(lvdata->device, lvdata->indexBuffer, nullptr);

	pTable->pfn_vkFreeMemory(lvdata->device, lvdata->indexBufferMemory, nullptr);

	for (int i = 0; i < IMAGE_COUNT; i++)
	{
		pTable->pfn_vkDestroyImageView(lvdata->device, lvdata->swapchainImageViews[i], nullptr);
	}

	pTable->pfn_vkDestroySwapchainKHR(lvdata->device, lvdata->swapchain, nullptr);

	pTable->pfn_vkDestroyDevice(lvdata->device, nullptr);

	pTable->pfn_vkDestroySurfaceKHR(lvdata->instance, lvdata->surface, nullptr);

   	pTable->pfn_vkDestroyDebugUtilsMessengerEXT(lvdata->instance, lvdata->debugMessenger, nullptr);

	pTable->pfn_vkDestroyInstance(lvdata->instance, nullptr);

	dlclose(pTable->vkLib);

	printf(YELLOW "vulkanTerminate() " RESET_COLOR GRAY "end" RESET_COLOR "\n");
	return 0;
}
