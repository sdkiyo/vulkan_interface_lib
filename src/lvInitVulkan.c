#include "vk.h"
#include "pre.h"
#include "swapchain.h"
#include "renderSetup.h"
#include "renderer.h"
#include "vertex.h"

int initVulkan(lvParam *const lvparam, lvData *const lvdata, LoaderTable *const pTable)
{
	printf(BLUE "initVulkan() " RESET_COLOR GRAY "start" RESET_COLOR "\n");

	funcPreLoader(pTable);

	if (createInstance(pTable, lvparam->ppValidationLayers, lvparam->validationLayersCount, lvparam->ppInstanceExtensions, lvparam->instanceExtensionsCount, &lvdata->instance) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createInstance() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	funcInstanceLoader(pTable, &lvdata->instance);

	if (createDebugUtilsMessenger(pTable, &lvdata->instance, &lvdata->debugMessenger) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createDebugUtilsMessenger() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createSurface(lvparam->pWindow, &lvdata->instance, &lvdata->surface) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createSurface() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (pickPhysicalDevice(pTable, &lvdata->instance, &lvdata->physicalDevice) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'pickPhysicalDevice() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createLogicalDevice(pTable, &lvdata->instance, lvparam->ppDeviceExtensions, lvparam->deviceExtensionsCount, &lvdata->physicalDevice, &lvdata->device, &lvdata->queue) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createLogicalDevice() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	funcDeviceLoader(pTable, &lvdata->device);

	if (createSwapchain(pTable, &lvdata->instance, &lvdata->physicalDevice, &lvdata->surface, &lvdata->device, &lvdata->swapchain, lvdata->swapchainImages, &lvdata->swapchainImageFormat, &lvdata->swapchainExtent) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createSwapchain() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createImageViews(pTable, &lvdata->device, &lvdata->swapchainImageFormat, lvdata->swapchainImages, lvdata->swapchainImageViews) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createImageViews() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createRenderPass(pTable, &lvdata->device, &lvdata->swapchainImageFormat, &lvdata->renderPass) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createRenderPass() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createDescriptorSetLayout(pTable, &lvdata->device,&lvdata->descriptorSetLayout) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createDescriptorSetLayout() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createGraphicsPipeline(pTable, &lvdata->device, &lvdata->pipelineLayout, &lvdata->graphicsPipeline, &lvdata->renderPass, &lvdata->descriptorSetLayout) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createGraphicsPipeline() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createFramebuffers(pTable, &lvdata->device, &lvdata->swapchainExtent, &lvdata->renderPass, lvdata->swapchainImageViews, lvdata->swapchainFramebuffers) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createFramebuffers() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createCommandPool(pTable, &lvdata->device, &lvdata->commandPool) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createCommandPool() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createVertexBuffer(pTable, &lvdata->instance, &lvdata->physicalDevice, &lvdata->device, &lvdata->commandPool, &lvdata->queue, &lvdata->vertexBuffer, &lvdata->vertexBufferMemory, lvparam->pVertices, lvparam->vertices_size) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createVertexBuffer() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createIndexBuffer(pTable, &lvdata->instance, &lvdata->physicalDevice, &lvdata->device, &lvdata->commandPool, &lvdata->queue, &lvdata->indexBuffer, &lvdata->indexBufferMemory, lvparam->pIndices, lvparam->indices_size) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createIndexBuffer() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createUniformBuffers(pTable, &lvdata->instance, &lvdata->physicalDevice, &lvdata->device, lvdata->uniformBuffers, lvdata->uniformBuffersMemory, lvdata->uniformBuffersMapped) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createUnfiromBuffers() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createDescriptorPool(pTable, &lvdata->device, &lvdata->descriptorPool) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createDescriptorPool() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createDescriptorSets(pTable, &lvdata->device, &lvdata->descriptorPool, &lvdata->descriptorSetLayout, lvdata->uniformBuffers, lvdata->descriptorSets) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createDescriptorSets() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createCommandBuffer(pTable, &lvdata->device, &lvdata->commandPool, lvdata->commandBuffers) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createCommandBuffer() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	if (createSyncObjects(pTable, &lvdata->device, lvdata->imageAvailableSemaphore, lvdata->renderFinishedSemaphore, lvdata->inFlightFence) == -1)
	{
		fprintf(stderr, RED "%s(), line %d, 'createSyncObjects() failed'" RESET_COLOR "\n", __func__, __LINE__);
	}

	printf(BLUE "initVulkan() " RESET_COLOR GRAY "end" RESET_COLOR "\n");
}
