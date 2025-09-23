#include <vk.h>

int funcPreLoader(LoaderTable *const pTable)
{
	pTable->vkLib = dlopen("/usr/lib64/libvulkan.so", RTLD_LAZY);
	printf(BLUE "- open libvulkan.so" RESET_COLOR "\n");

	pTable->pfn_vkGetInstanceProcAddr	= dlsym(pTable->vkLib, "vkGetInstanceProcAddr");
	pTable->pfn_vkGetDeviceProcAddr		= dlsym(pTable->vkLib, "vkGetDeviceProcAddr");
	pTable->pfn_vkCreateInstance		= (PFN_vkCreateInstance) pTable->pfn_vkGetInstanceProcAddr(NULL, "vkCreateInstance");

	return 0;
}

int funcInstanceLoader(LoaderTable *const pTable, const VkInstance *const instance)
{
	pTable->pfn_vkEnumeratePhysicalDevices			= (PFN_vkEnumeratePhysicalDevices) pTable->pfn_vkGetInstanceProcAddr(*instance, "vkEnumeratePhysicalDevices");
	pTable->pfn_vkCreateDebugUtilsMessengerEXT		= (PFN_vkCreateDebugUtilsMessengerEXT) pTable->pfn_vkGetInstanceProcAddr(*instance, "vkCreateDebugUtilsMessengerEXT");
	pTable->pfn_vkCreateDevice				= (PFN_vkCreateDevice) pTable->pfn_vkGetInstanceProcAddr(*instance, "vkCreateDevice");
	pTable->pfn_vkGetPhysicalDeviceSurfaceCapabilitiesKHR	= (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) pTable->pfn_vkGetInstanceProcAddr(*instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	pTable->pfn_vkGetPhysicalDeviceMemoryProperties		= (PFN_vkGetPhysicalDeviceMemoryProperties) pTable->pfn_vkGetInstanceProcAddr(*instance, "vkGetPhysicalDeviceMemoryProperties");
	pTable->pfn_vkDestroySurfaceKHR				= (PFN_vkDestroySurfaceKHR) pTable->pfn_vkGetInstanceProcAddr(*instance, "vkDestroySurfaceKHR");
	pTable->pfn_vkDestroyDebugUtilsMessengerEXT		= (PFN_vkDestroyDebugUtilsMessengerEXT) pTable->pfn_vkGetInstanceProcAddr(*instance, "vkDestroyDebugUtilsMessengerEXT");
	pTable->pfn_vkDestroyInstance				= (PFN_vkDestroyInstance) pTable->pfn_vkGetInstanceProcAddr(*instance, "vkDestroyInstance");

	return 0;
}

int funcDeviceLoader(LoaderTable *const pTable, const VkDevice *const device)
{
	pTable->pfn_vkCreatePipelineLayout			= (PFN_vkCreatePipelineLayout) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCreatePipelineLayout");
	pTable->pfn_vkCreateGraphicsPipelines			= (PFN_vkCreateGraphicsPipelines) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCreateGraphicsPipelines");
	pTable->pfn_vkDestroyShaderModule			= (PFN_vkDestroyShaderModule) pTable->pfn_vkGetDeviceProcAddr(*device, "vkDestroyShaderModule");
	pTable->pfn_vkCreateRenderPass				= (PFN_vkCreateRenderPass) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCreateRenderPass");
	pTable->pfn_vkQueuePresentKHR				= (PFN_vkQueuePresentKHR) pTable->pfn_vkGetDeviceProcAddr(*device, "vkQueuePresentKHR");
	pTable->pfn_vkQueueSubmit				= (PFN_vkQueueSubmit) pTable->pfn_vkGetDeviceProcAddr(*device, "vkQueueSubmit");
	pTable->pfn_vkResetCommandBuffer			= (PFN_vkResetCommandBuffer) pTable->pfn_vkGetDeviceProcAddr(*device, "vkResetCommandBuffer");
	pTable->pfn_vkAcquireNextImageKHR			= (PFN_vkAcquireNextImageKHR) pTable->pfn_vkGetDeviceProcAddr(*device, "vkAcquireNextImageKHR");
	pTable->pfn_vkWaitForFences				= (PFN_vkWaitForFences) pTable->pfn_vkGetDeviceProcAddr(*device, "vkWaitForFences");
	pTable->pfn_vkResetFences				= (PFN_vkResetFences) pTable->pfn_vkGetDeviceProcAddr(*device, "vkResetFences");
	pTable->pfn_vkCmdBindVertexBuffers			= (PFN_vkCmdBindVertexBuffers) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCmdBindVertexBuffers");
	pTable->pfn_vkCmdBindIndexBuffer			= (PFN_vkCmdBindIndexBuffer) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCmdBindIndexBuffer");
	pTable->pfn_vkCmdDrawIndexed				= (PFN_vkCmdDrawIndexed) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCmdDrawIndexed");
	pTable->pfn_vkEndCommandBuffer				= (PFN_vkEndCommandBuffer) pTable->pfn_vkGetDeviceProcAddr(*device, "vkEndCommandBuffer");
	pTable->pfn_vkCmdEndRenderPass				= (PFN_vkCmdEndRenderPass) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCmdEndRenderPass");
	pTable->pfn_vkCmdSetViewport				= (PFN_vkCmdSetViewport) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCmdSetViewport");
	pTable->pfn_vkCmdSetScissor				= (PFN_vkCmdSetScissor) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCmdSetScissor");
	pTable->pfn_vkCmdBeginRenderPass			= (PFN_vkCmdBeginRenderPass) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCmdBeginRenderPass");
	pTable->pfn_vkBeginCommandBuffer			= (PFN_vkBeginCommandBuffer) pTable->pfn_vkGetDeviceProcAddr(*device, "vkBeginCommandBuffer");
	pTable->pfn_vkCmdBindPipeline				= (PFN_vkCmdBindPipeline) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCmdBindPipeline");
	pTable->pfn_vkCreateSemaphore				= (PFN_vkCreateSemaphore) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCreateSemaphore");
	pTable->pfn_vkCreateFence				= (PFN_vkCreateFence) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCreateFence");
	pTable->pfn_vkCreateCommandPool				= (PFN_vkCreateCommandPool) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCreateCommandPool");
	pTable->pfn_vkAllocateCommandBuffers			= (PFN_vkAllocateCommandBuffers) pTable->pfn_vkGetDeviceProcAddr(*device, "vkAllocateCommandBuffers");
	pTable->pfn_vkCreateShaderModule			= (PFN_vkCreateShaderModule) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCreateShaderModule");
	pTable->pfn_vkCreateFramebuffer				= (PFN_vkCreateFramebuffer) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCreateFramebuffer");
	pTable->pfn_vkCreateImageView				= (PFN_vkCreateImageView) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCreateImageView");
	pTable->pfn_vkCreateSwapchainKHR			= (PFN_vkCreateSwapchainKHR) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCreateSwapchainKHR");
	pTable->pfn_vkGetSwapchainImagesKHR			= (PFN_vkGetSwapchainImagesKHR) pTable->pfn_vkGetDeviceProcAddr(*device, "vkGetSwapchainImagesKHR");
	pTable->pfn_vkUnmapMemory				= (PFN_vkUnmapMemory) pTable->pfn_vkGetDeviceProcAddr(*device, "vkUnmapMemory");
	pTable->pfn_vkMapMemory					= (PFN_vkMapMemory) pTable->pfn_vkGetDeviceProcAddr(*device, "vkMapMemory");
	pTable->pfn_vkDestroyBuffer				= (PFN_vkDestroyBuffer) pTable->pfn_vkGetDeviceProcAddr(*device, "vkDestroyBuffer");
	pTable->pfn_vkFreeMemory				= (PFN_vkFreeMemory) pTable->pfn_vkGetDeviceProcAddr(*device, "vkFreeMemory");
	pTable->pfn_vkBindBufferMemory				= (PFN_vkBindBufferMemory) pTable->pfn_vkGetDeviceProcAddr(*device, "vkBindBufferMemory");
	pTable->pfn_vkAllocateMemory				= (PFN_vkAllocateMemory) pTable->pfn_vkGetDeviceProcAddr(*device, "vkAllocateMemory");
	pTable->pfn_vkGetBufferMemoryRequirements		= (PFN_vkGetBufferMemoryRequirements) pTable->pfn_vkGetDeviceProcAddr(*device, "vkGetBufferMemoryRequirements");
	pTable->pfn_vkCreateBuffer				= (PFN_vkCreateBuffer) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCreateBuffer");
	pTable->pfn_vkCmdCopyBuffer				= (PFN_vkCmdCopyBuffer) pTable->pfn_vkGetDeviceProcAddr(*device, "vkCmdCopyBuffer");
	pTable->pfn_vkFreeCommandBuffers			= (PFN_vkFreeCommandBuffers) pTable->pfn_vkGetDeviceProcAddr(*device, "vkFreeCommandBuffers");
	pTable->pfn_vkQueueWaitIdle				= (PFN_vkQueueWaitIdle) pTable->pfn_vkGetDeviceProcAddr(*device, "vkQueueWaitIdle");
	pTable->pfn_vkDestroySemaphore				= (PFN_vkDestroySemaphore) pTable->pfn_vkGetDeviceProcAddr(*device, "vkDestroySemaphore");
	pTable->pfn_vkDestroyFence				= (PFN_vkDestroyFence) pTable->pfn_vkGetDeviceProcAddr(*device, "vkDestroyFence");
	pTable->pfn_vkDestroyCommandPool			= (PFN_vkDestroyCommandPool) pTable->pfn_vkGetDeviceProcAddr(*device, "vkDestroyCommandPool");
	pTable->pfn_vkDestroyFramebuffer			= (PFN_vkDestroyFramebuffer) pTable->pfn_vkGetDeviceProcAddr(*device, "vkDestroyFramebuffer");
	pTable->pfn_vkDestroyPipeline				= (PFN_vkDestroyPipeline) pTable->pfn_vkGetDeviceProcAddr(*device, "vkDestroyPipeline");
	pTable->pfn_vkDestroyRenderPass				= (PFN_vkDestroyRenderPass) pTable->pfn_vkGetDeviceProcAddr(*device, "vkDestroyRenderPass");
	pTable->pfn_vkDestroyPipelineLayout			= (PFN_vkDestroyPipelineLayout) pTable->pfn_vkGetDeviceProcAddr(*device, "vkDestroyPipelineLayout");
	pTable->pfn_vkDestroyImageView				= (PFN_vkDestroyImageView) pTable->pfn_vkGetDeviceProcAddr(*device, "vkDestroyImageView");
	pTable->pfn_vkDestroySwapchainKHR			= (PFN_vkDestroySwapchainKHR) pTable->pfn_vkGetDeviceProcAddr(*device, "vkDestroySwapchainKHR");
	pTable->pfn_vkDestroyDevice				= (PFN_vkDestroyDevice) pTable->pfn_vkGetDeviceProcAddr(*device, "vkDestroyDevice");


	return 0;
}
