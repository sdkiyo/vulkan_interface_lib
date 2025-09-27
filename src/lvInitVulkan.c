#include "vk.h"
#include "pre.h"
#include "swapchain.h"
#include "renderSetup.h"
#include "renderer.h"
#include "vertex.h"

int lvInitVulkan(lvParam *const lvparam, lvData *const lvdata, LoaderTable *const pTable)
{
	printf(BLUE "initVulkan() " RESET_COLOR GRAY "start" RESET_COLOR "\n");

	for (int i = 0; i < VERTICES_SIZE; i++)
	{
		printf("pos[%d] x: %f\n", i, vertices[i].pos.x);
		printf("pos[%d] y: %f\n", i, vertices[i].pos.y);
	}
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

	funcPreLoader(pTable);

	if (lvCreateInstance(pTable, lvparam->validationLayers, lvparam->validationLayersCount, lvparam->instanceExtensions, lvparam->instanceExtensionsCount, &lvdata->instance) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'lvCreateInstance() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "lvCreateInstance() " GREEN "success!" RESET_COLOR "\n");

	funcInstanceLoader(pTable, &lvdata->instance);

	if (createDebugUtilsMessenger(pTable, &lvdata->instance, &lvdata->debugMessenger) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createDebugUtilsMessenger() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createDebugUtilsMessenger() " GREEN "success!" RESET_COLOR "\n");

	if (lvCreateSurface(lvparam->window, &lvdata->instance, &lvdata->surface) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'lvCreateSurface() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "lvCreateSurface() " GREEN "success!" RESET_COLOR "\n");

	if (lvPickPhysicalDevice(pTable, &lvdata->instance, &lvdata->physicalDevice) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'lvPickPhysicalDevice() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "lvPickPhysicalDevice() " GREEN "success!" RESET_COLOR "\n");

	if (createLogicalDevice(pTable, &lvdata->instance, lvparam->deviceExtensions, lvparam->deviceExtensionsCount, &lvdata->physicalDevice, &lvdata->device, &lvdata->queue) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createLogicalDevice() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createLogicalDevice() " GREEN "success!" RESET_COLOR "\n");


	funcDeviceLoader(pTable, &lvdata->device);


	if (createSwapchain(pTable, &lvdata->instance, &lvdata->physicalDevice, &lvdata->surface, &lvdata->device, &lvdata->swapchain, lvdata->swapchainImages, &lvdata->swapchainImageFormat, &lvdata->swapchainExtent) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createSwapchain() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createSwapchain() " GREEN "success!" RESET_COLOR "\n");

	if (createImageViews(pTable, &lvdata->device, &lvdata->swapchainImageFormat, lvdata->swapchainImages, lvdata->swapchainImageViews) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createImageViews() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createImageViews() " GREEN "success!" RESET_COLOR "\n");

	if (createRenderPass(pTable, &lvdata->device, &lvdata->swapchainImageFormat, &lvdata->renderPass) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createRenderPass() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createRenderPass() " GREEN "success!" RESET_COLOR "\n");

	if (createDescriptorSetLayout(pTable, &lvdata->device,&lvdata->descriptorSetLayout) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createDescriptorSetLayout() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createDescriptorSetLayout() " GREEN "success!" RESET_COLOR "\n");

	if (createGraphicsPipeline(pTable, &lvdata->device, &lvdata->pipelineLayout, &lvdata->graphicsPipeline, &lvdata->renderPass, &lvdata->descriptorSetLayout) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createGraphicsPipeline() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createGraphicsPipeline() " GREEN "success!" RESET_COLOR "\n");

	if (createFramebuffers(pTable, &lvdata->device, &lvdata->swapchainExtent, &lvdata->renderPass, lvdata->swapchainImageViews, lvdata->swapchainFramebuffers) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createFramebuffers() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createFramebuffers() " GREEN "success!" RESET_COLOR "\n");

	if (createCommandPool(pTable, &lvdata->device, &lvdata->commandPool) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createCommandPool() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createCommandPool() " GREEN "success!" RESET_COLOR "\n");

	if (createVertexBuffer(pTable, &lvdata->instance, &lvdata->physicalDevice, &lvdata->device, &lvdata->commandPool, &lvdata->queue, &lvdata->vertexBuffer, &lvdata->vertexBufferMemory) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createVertexBuffer() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createVertexBuffer() " GREEN "success!" RESET_COLOR "\n");

	if (createIndexBuffer(pTable, &lvdata->instance, &lvdata->physicalDevice, &lvdata->device, &lvdata->commandPool, &lvdata->queue, &lvdata->indexBuffer, &lvdata->indexBufferMemory) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createIndexBuffer() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createIndexBuffer() " GREEN "success!" RESET_COLOR "\n");

	if (createUniformBuffers(pTable, &lvdata->instance, &lvdata->physicalDevice, &lvdata->device, lvdata->uniformBuffers, lvdata->uniformBuffersMemory, lvdata->uniformBuffersMapped) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createUnfiromBuffers() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createUniformBuffers() " GREEN "success!" RESET_COLOR "\n");


	if (createDescriptorPool(pTable, &lvdata->device, &lvdata->descriptorPool) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createDescriptorPool() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createDescriptorPool() " GREEN "success!" RESET_COLOR "\n");

	if (createDescriptorSets(pTable, &lvdata->device, &lvdata->descriptorPool, &lvdata->descriptorSetLayout, lvdata->uniformBuffers, lvdata->descriptorSets) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createDescriptorSets() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createDescriptorSets() " GREEN "success!" RESET_COLOR "\n");


	if (createCommandBuffer(pTable, &lvdata->device, &lvdata->commandPool, lvdata->commandBuffers) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createCommandBuffer() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createCommandBuffer() " GREEN "success!" RESET_COLOR "\n");

	if (createSyncObjects(pTable, &lvdata->device, lvdata->imageAvailableSemaphore, lvdata->renderFinishedSemaphore, lvdata->inFlightFence) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createSyncObjects() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}
	printf("- " BLUE "createSyncObjects() " GREEN "success!" RESET_COLOR "\n");

	printf(BLUE "initVulkan() " RESET_COLOR GRAY "end" RESET_COLOR "\n");
}
