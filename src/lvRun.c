#include "../include/vk.h"

int lvInitVulkan(lvParam *const lvparam, GLFWwindow *const window)
{
	printf(BLUE "initVulkan() " RESET_COLOR GRAY "start" RESET_COLOR "\n");

	printf("=-------starting_params-------=" RESET_COLOR "\n");
	printf(" layers:\n");
	for (uint32_t i = 0; i < lvparam->validationLayersCount; i++)
	{
		printf("\033[35m   %s\033[0m\n", lvparam->validationLayers[i]);
	}
	printf(" instance ext:\n");
	for (uint32_t i = 0; i < lvparam->instanceExtensionsCount; i++)
	{
		printf("\033[35m   %s\033[0m\n", lvparam->instanceExtensions[i]);
	}
	printf(" device ext:\n");
	for (uint32_t i = 0; i < lvparam->deviceExtensionsCount; i++)
	{
		printf("\033[35m   %s\033[0m\n", lvparam->deviceExtensions[i]);
	}
	printf("=-------starting_params-------=" RESET_COLOR "\n");

	void *vklib = dlopen("/usr/lib64/libvulkan.so", RTLD_LAZY);
	lvparam->lvdata->pfn_vkGetInstanceProcAddr = dlsym(vklib, "vkGetInstanceProcAddr");
	lvparam->lvdata->pfn_vkGetDeviceProcAddr = dlsym(vklib, "vkGetDeviceProcAddr");


	if (lvCreateInstance(lvparam->lvdata->pfn_vkGetInstanceProcAddr, lvparam->validationLayers, lvparam->validationLayersCount, lvparam->instanceExtensions, lvparam->instanceExtensionsCount, &lvparam->lvdata->instance) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'lvCreateInstance() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "lvCreateInstance() " GREEN "success!" RESET_COLOR "\n");

	if (createDebugUtilsMessenger(lvparam->lvdata->pfn_vkGetInstanceProcAddr, &lvparam->lvdata->instance, &lvparam->lvdata->debugMessenger) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createDebugUtilsMessenger() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createDebugUtilsMessenger() " GREEN "success!" RESET_COLOR "\n");

	if (lvCreateSurface(window, &lvparam->lvdata->instance, &lvparam->lvdata->surface) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'lvCreateSurface() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "lvCreateSurface() " GREEN "success!" RESET_COLOR "\n");

	if (lvPickPhysicalDevice(lvparam->lvdata->pfn_vkGetInstanceProcAddr, &lvparam->lvdata->instance, &lvparam->lvdata->physicalDevice) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'lvPickPhysicalDevice() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "lvPickPhysicalDevice() " GREEN "success!" RESET_COLOR "\n");

	if (createLogicalDevice(lvparam->lvdata->pfn_vkGetInstanceProcAddr, lvparam->lvdata->pfn_vkGetDeviceProcAddr, &lvparam->lvdata->instance, lvparam->deviceExtensions, lvparam->deviceExtensionsCount, &lvparam->lvdata->physicalDevice, &lvparam->lvdata->device, &lvparam->lvdata->queue) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createLogicalDevice() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createLogicalDevice() " GREEN "success!" RESET_COLOR "\n");

	if (createSwapchain(lvparam->lvdata->pfn_vkGetInstanceProcAddr, lvparam->lvdata->pfn_vkGetDeviceProcAddr, &lvparam->lvdata->instance, &lvparam->lvdata->physicalDevice, &lvparam->lvdata->surface, &lvparam->lvdata->device, &lvparam->lvdata->swapchain, lvparam->lvdata->swapchainImages, &lvparam->lvdata->swapchainImageFormat, &lvparam->lvdata->swapchainExtent) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createSwapchain() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createSwapchain() " GREEN "success!" RESET_COLOR "\n");

	if (createImageViews(lvparam->lvdata->pfn_vkGetDeviceProcAddr, &lvparam->lvdata->device, &lvparam->lvdata->swapchainImageFormat, lvparam->lvdata->swapchainImages, lvparam->lvdata->swapchainImageViews) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createImageViews() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createImageViews() " GREEN "success!" RESET_COLOR "\n");

	if (createRenderPass(lvparam->lvdata->pfn_vkGetDeviceProcAddr, &lvparam->lvdata->device, &lvparam->lvdata->swapchainImageFormat, &lvparam->lvdata->renderPass) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createRenderPass() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createRenderPass() " GREEN "success!" RESET_COLOR "\n");

	if (createGraphicsPipeline(lvparam->lvdata->pfn_vkGetDeviceProcAddr, &lvparam->lvdata->device, &lvparam->lvdata->pipelineLayout, &lvparam->lvdata->graphicsPipeline, &lvparam->lvdata->renderPass) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createGraphicsPipeline() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createGraphicsPipeline() " GREEN "success!" RESET_COLOR "\n");

	if (createFramebuffers(lvparam->lvdata->pfn_vkGetDeviceProcAddr, &lvparam->lvdata->device, &lvparam->lvdata->swapchainExtent, &lvparam->lvdata->renderPass, lvparam->lvdata->swapchainImageViews, lvparam->lvdata->swapchainFramebuffers) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createFramebuffers() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createFramebuffers() " GREEN "success!" RESET_COLOR "\n");

	if (createCommandPool(lvparam->lvdata->pfn_vkGetDeviceProcAddr, &lvparam->lvdata->device, &lvparam->lvdata->commandPool) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createCommandPool() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createCommandPool() " GREEN "success!" RESET_COLOR "\n");

	if (createCommandBuffer(lvparam->lvdata->pfn_vkGetDeviceProcAddr, &lvparam->lvdata->device, &lvparam->lvdata->commandPool, lvparam->lvdata->commandBuffers) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createCommandBuffer() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createCommandBuffer() " GREEN "success!" RESET_COLOR "\n");

	if (createSyncObjects(lvparam->lvdata->pfn_vkGetDeviceProcAddr, &lvparam->lvdata->device, lvparam->lvdata->imageAvailableSemaphore, lvparam->lvdata->renderFinishedSemaphore, lvparam->lvdata->inFlightFence) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createSyncObjects() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createSyncObjects() " GREEN "success!" RESET_COLOR "\n");

	printf(BLUE "initVulkan() " RESET_COLOR GRAY "end" RESET_COLOR "\n");
}
