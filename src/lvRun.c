#include "../include/vk.h"

void lvInitVulkan(lvData *const lvdata, GLFWwindow *const window)
{
	lvCreateInstance(&lvdata->instance);
	createDebugUtilsMessenger(&lvdata->instance, &lvdata->debugMessenger);
	lvCreateSurface(window, &lvdata->instance, &lvdata->surface);
	lvPickPhysicalDevice(&lvdata->instance, &lvdata->physicalDevice);
	createLogicalDevice(&lvdata->physicalDevice, &lvdata->device, &lvdata->queue);
	createSwapchain(&lvdata->physicalDevice, &lvdata->surface, &lvdata->device, &lvdata->swapchain, lvdata->swapchainImages, &lvdata->swapchainImageFormat, &lvdata->swapchainExtent);
	createImageViews(&lvdata->device, &lvdata->swapchainImageFormat, lvdata->swapchainImages, lvdata->swapchainImageViews);
	createRenderPass(&lvdata->device, &lvdata->swapchainImageFormat, &lvdata->renderPass);
	createGraphicsPipeline(&lvdata->device, &lvdata->pipelineLayout, &lvdata->graphicsPipeline, &lvdata->renderPass);
	createFramebuffers(&lvdata->device, &lvdata->swapchainExtent, &lvdata->renderPass, lvdata->swapchainImageViews, lvdata->swapchainFramebuffers);
	createCommandPool(&lvdata->device, &lvdata->commandPool);
	createCommandBuffer(&lvdata->device, &lvdata->commandPool, lvdata->commandBuffers);
	createSyncObjects(&lvdata->device, lvdata->imageAvailableSemaphore, lvdata->renderFinishedSemaphore, lvdata->inFlightFence);
}
