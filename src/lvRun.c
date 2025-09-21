#include "../include/vk.h"

int lvInitVulkan(lvParam *const lvparam, GLFWwindow *const window)
{
	printf(BLUE "initVulkan() " RESET_COLOR GRAY "start" RESET_COLOR "\n");
	printf("- " BLUE "123() " GREEN "success!" RESET_COLOR "\n");

	if (lvCreateInstance(lvparam->validationLayers, lvparam->validationLayersCount, lvparam->instanceExtensions, lvparam->instanceExtensionsCount, &lvparam->lvdata->instance) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'lvCreateInstance() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	if (createDebugUtilsMessenger(&lvparam->lvdata->instance, &lvparam->lvdata->debugMessenger) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createDebugUtilsMessenger() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (lvCreateSurface(window, &lvparam->lvdata->instance, &lvparam->lvdata->surface) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'lvCreateSurface() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	if (lvPickPhysicalDevice(&lvparam->lvdata->instance, &lvparam->lvdata->physicalDevice) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'lvPickPhysicalDevice() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	if (createLogicalDevice(lvparam->deviceExtensions, lvparam->deviceExtensionsCount, &lvparam->lvdata->physicalDevice, &lvparam->lvdata->device, &lvparam->lvdata->queue) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createLogicalDevice() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createSwapchain(&lvparam->lvdata->physicalDevice, &lvparam->lvdata->surface, &lvparam->lvdata->device, &lvparam->lvdata->swapchain, lvparam->lvdata->swapchainImages, &lvparam->lvdata->swapchainImageFormat, &lvparam->lvdata->swapchainExtent) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createSwapchain() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	if (createImageViews(&lvparam->lvdata->device, &lvparam->lvdata->swapchainImageFormat, lvparam->lvdata->swapchainImages, lvparam->lvdata->swapchainImageViews) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createImageViews() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createRenderPass(&lvparam->lvdata->device, &lvparam->lvdata->swapchainImageFormat, &lvparam->lvdata->renderPass) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createRenderPass() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	if (createGraphicsPipeline(&lvparam->lvdata->device, &lvparam->lvdata->pipelineLayout, &lvparam->lvdata->graphicsPipeline, &lvparam->lvdata->renderPass) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createGraphicsPipeline() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	if (createFramebuffers(&lvparam->lvdata->device, &lvparam->lvdata->swapchainExtent, &lvparam->lvdata->renderPass, lvparam->lvdata->swapchainImageViews, lvparam->lvdata->swapchainFramebuffers) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createFramebuffers() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createCommandPool(&lvparam->lvdata->device, &lvparam->lvdata->commandPool) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createCommandPool() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	if (createCommandBuffer(&lvparam->lvdata->device, &lvparam->lvdata->commandPool, lvparam->lvdata->commandBuffers) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createCommandBuffer() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createSyncObjects(&lvparam->lvdata->device, lvparam->lvdata->imageAvailableSemaphore, lvparam->lvdata->renderFinishedSemaphore, lvparam->lvdata->inFlightFence) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createSyncObjects() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	printf(BLUE "initVulkan() " RESET_COLOR GRAY "end" RESET_COLOR "\n");
}
