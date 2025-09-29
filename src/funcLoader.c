#include <vk.h>

int funcPreLoader(LoaderTable *const pTable)
{
	pTable->vkLib = dlopen("/usr/lib64/libvulkan.so", RTLD_LAZY);

	pTable->pfn_vkGetInstanceProcAddr	= dlsym(pTable->vkLib, "vkGetInstanceProcAddr");
	pTable->pfn_vkGetDeviceProcAddr		= dlsym(pTable->vkLib, "vkGetDeviceProcAddr");
	pTable->pfn_vkCreateInstance		= (PFN_vkCreateInstance) pTable->pfn_vkGetInstanceProcAddr(NULL, "vkCreateInstance");

	return 0;
}

int funcInstanceLoader(LoaderTable *const pTable, const VkInstance *const pInstance)
{
	pTable->pfn_vkEnumeratePhysicalDevices			= (PFN_vkEnumeratePhysicalDevices) pTable->pfn_vkGetInstanceProcAddr(*pInstance, "vkEnumeratePhysicalDevices");
	pTable->pfn_vkCreateDebugUtilsMessengerEXT		= (PFN_vkCreateDebugUtilsMessengerEXT) pTable->pfn_vkGetInstanceProcAddr(*pInstance, "vkCreateDebugUtilsMessengerEXT");
	pTable->pfn_vkCreateDevice				= (PFN_vkCreateDevice) pTable->pfn_vkGetInstanceProcAddr(*pInstance, "vkCreateDevice");
	pTable->pfn_vkGetPhysicalDeviceSurfaceCapabilitiesKHR	= (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) pTable->pfn_vkGetInstanceProcAddr(*pInstance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	pTable->pfn_vkGetPhysicalDeviceMemoryProperties		= (PFN_vkGetPhysicalDeviceMemoryProperties) pTable->pfn_vkGetInstanceProcAddr(*pInstance, "vkGetPhysicalDeviceMemoryProperties");
	pTable->pfn_vkDestroySurfaceKHR				= (PFN_vkDestroySurfaceKHR) pTable->pfn_vkGetInstanceProcAddr(*pInstance, "vkDestroySurfaceKHR");
	pTable->pfn_vkDestroyDebugUtilsMessengerEXT		= (PFN_vkDestroyDebugUtilsMessengerEXT) pTable->pfn_vkGetInstanceProcAddr(*pInstance, "vkDestroyDebugUtilsMessengerEXT");
	pTable->pfn_vkDestroyInstance				= (PFN_vkDestroyInstance) pTable->pfn_vkGetInstanceProcAddr(*pInstance, "vkDestroyInstance");

	return 0;
}

int funcDeviceLoader(LoaderTable *const pTable, const VkDevice *const pDevice)
{
	pTable->pfn_vkCreatePipelineLayout			= (PFN_vkCreatePipelineLayout) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreatePipelineLayout");
	pTable->pfn_vkCreateGraphicsPipelines			= (PFN_vkCreateGraphicsPipelines) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreateGraphicsPipelines");
	pTable->pfn_vkDestroyShaderModule			= (PFN_vkDestroyShaderModule) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroyShaderModule");
	pTable->pfn_vkCreateRenderPass				= (PFN_vkCreateRenderPass) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreateRenderPass");
	pTable->pfn_vkQueuePresentKHR				= (PFN_vkQueuePresentKHR) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkQueuePresentKHR");
	pTable->pfn_vkQueueSubmit				= (PFN_vkQueueSubmit) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkQueueSubmit");
	pTable->pfn_vkResetCommandBuffer			= (PFN_vkResetCommandBuffer) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkResetCommandBuffer");
	pTable->pfn_vkAcquireNextImageKHR			= (PFN_vkAcquireNextImageKHR) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkAcquireNextImageKHR");
	pTable->pfn_vkWaitForFences				= (PFN_vkWaitForFences) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkWaitForFences");
	pTable->pfn_vkResetFences				= (PFN_vkResetFences) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkResetFences");
	pTable->pfn_vkCmdBindVertexBuffers			= (PFN_vkCmdBindVertexBuffers) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCmdBindVertexBuffers");
	pTable->pfn_vkCmdBindIndexBuffer			= (PFN_vkCmdBindIndexBuffer) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCmdBindIndexBuffer");
	pTable->pfn_vkCmdDrawIndexed				= (PFN_vkCmdDrawIndexed) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCmdDrawIndexed");
	pTable->pfn_vkEndCommandBuffer				= (PFN_vkEndCommandBuffer) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkEndCommandBuffer");
	pTable->pfn_vkCmdEndRenderPass				= (PFN_vkCmdEndRenderPass) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCmdEndRenderPass");
	pTable->pfn_vkCmdSetViewport				= (PFN_vkCmdSetViewport) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCmdSetViewport");
	pTable->pfn_vkCmdSetScissor				= (PFN_vkCmdSetScissor) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCmdSetScissor");
	pTable->pfn_vkCmdBeginRenderPass			= (PFN_vkCmdBeginRenderPass) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCmdBeginRenderPass");
	pTable->pfn_vkBeginCommandBuffer			= (PFN_vkBeginCommandBuffer) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkBeginCommandBuffer");
	pTable->pfn_vkCmdBindPipeline				= (PFN_vkCmdBindPipeline) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCmdBindPipeline");
	pTable->pfn_vkCreateSemaphore				= (PFN_vkCreateSemaphore) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreateSemaphore");
	pTable->pfn_vkCreateFence				= (PFN_vkCreateFence) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreateFence");
	pTable->pfn_vkCreateCommandPool				= (PFN_vkCreateCommandPool) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreateCommandPool");
	pTable->pfn_vkAllocateCommandBuffers			= (PFN_vkAllocateCommandBuffers) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkAllocateCommandBuffers");
	pTable->pfn_vkCreateShaderModule			= (PFN_vkCreateShaderModule) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreateShaderModule");
	pTable->pfn_vkCreateFramebuffer				= (PFN_vkCreateFramebuffer) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreateFramebuffer");
	pTable->pfn_vkCreateImageView				= (PFN_vkCreateImageView) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreateImageView");
	pTable->pfn_vkCreateSwapchainKHR			= (PFN_vkCreateSwapchainKHR) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreateSwapchainKHR");
	pTable->pfn_vkGetSwapchainImagesKHR			= (PFN_vkGetSwapchainImagesKHR) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkGetSwapchainImagesKHR");
	pTable->pfn_vkUnmapMemory				= (PFN_vkUnmapMemory) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkUnmapMemory");
	pTable->pfn_vkMapMemory					= (PFN_vkMapMemory) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkMapMemory");
	pTable->pfn_vkDestroyBuffer				= (PFN_vkDestroyBuffer) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroyBuffer");
	pTable->pfn_vkFreeMemory				= (PFN_vkFreeMemory) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkFreeMemory");
	pTable->pfn_vkBindBufferMemory				= (PFN_vkBindBufferMemory) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkBindBufferMemory");
	pTable->pfn_vkAllocateMemory				= (PFN_vkAllocateMemory) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkAllocateMemory");
	pTable->pfn_vkGetBufferMemoryRequirements		= (PFN_vkGetBufferMemoryRequirements) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkGetBufferMemoryRequirements");
	pTable->pfn_vkCreateBuffer				= (PFN_vkCreateBuffer) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreateBuffer");
	pTable->pfn_vkCmdCopyBuffer				= (PFN_vkCmdCopyBuffer) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCmdCopyBuffer");
	pTable->pfn_vkFreeCommandBuffers			= (PFN_vkFreeCommandBuffers) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkFreeCommandBuffers");
	pTable->pfn_vkQueueWaitIdle				= (PFN_vkQueueWaitIdle) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkQueueWaitIdle");
	pTable->pfn_vkDestroySemaphore				= (PFN_vkDestroySemaphore) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroySemaphore");
	pTable->pfn_vkDestroyFence				= (PFN_vkDestroyFence) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroyFence");
	pTable->pfn_vkDestroyCommandPool			= (PFN_vkDestroyCommandPool) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroyCommandPool");
	pTable->pfn_vkDestroyFramebuffer			= (PFN_vkDestroyFramebuffer) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroyFramebuffer");
	pTable->pfn_vkDestroyPipeline				= (PFN_vkDestroyPipeline) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroyPipeline");
	pTable->pfn_vkDestroyRenderPass				= (PFN_vkDestroyRenderPass) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroyRenderPass");
	pTable->pfn_vkDestroyPipelineLayout			= (PFN_vkDestroyPipelineLayout) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroyPipelineLayout");
	pTable->pfn_vkDestroyImageView				= (PFN_vkDestroyImageView) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroyImageView");
	pTable->pfn_vkDestroySwapchainKHR			= (PFN_vkDestroySwapchainKHR) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroySwapchainKHR");
	pTable->pfn_vkDestroyDevice				= (PFN_vkDestroyDevice) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroyDevice");

	pTable->pfn_vkCreateDescriptorSetLayout			= (PFN_vkCreateDescriptorSetLayout) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreateDescriptorSetLayout");
	pTable->pfn_vkDestroyDescriptorSetLayout		= (PFN_vkDestroyDescriptorSetLayout) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroyDescriptorSetLayout");

	pTable->pfn_vkCreateDescriptorPool			= (PFN_vkCreateDescriptorPool) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCreateDescriptorPool");
	pTable->pfn_vkAllocateDescriptorSets			= (PFN_vkAllocateDescriptorSets) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkAllocateDescriptorSets");
	pTable->pfn_vkUpdateDescriptorSets			= (PFN_vkUpdateDescriptorSets) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkUpdateDescriptorSets");
	pTable->pfn_vkDestroyDescriptorPool			= (PFN_vkDestroyDescriptorPool) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkDestroyDescriptorPool");
	pTable->pfn_vkCmdBindDescriptorSets			= (PFN_vkCmdBindDescriptorSets) pTable->pfn_vkGetDeviceProcAddr(*pDevice, "vkCmdBindDescriptorSets");

	return 0;
}
