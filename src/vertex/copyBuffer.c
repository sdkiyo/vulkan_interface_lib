#include "vk.h"

int copyBuffer(const PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, const VkCommandPool *const commandPool, const VkQueue *const queue, const VkBuffer *const srcBuffer, const VkBuffer *const dstBuffer, const VkDeviceSize size)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = *commandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;

	const PFN_vkAllocateCommandBuffers pfn_vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers) pfn_vkGetDeviceProcAddr(*device, "vkAllocateCommandBuffers");
	pfn_vkAllocateCommandBuffers(*device, &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;


	const PFN_vkBeginCommandBuffer pfn_vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer) pfn_vkGetDeviceProcAddr(*device, "vkBeginCommandBuffer");
	pfn_vkBeginCommandBuffer(commandBuffer, &beginInfo);

	VkBufferCopy copyRegion = {};
	copyRegion.size = size;

	const PFN_vkCmdCopyBuffer pfn_vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer) pfn_vkGetDeviceProcAddr(*device, "vkCmdCopyBuffer");
	pfn_vkCmdCopyBuffer(commandBuffer, *srcBuffer, *dstBuffer, 1, &copyRegion);

	const PFN_vkEndCommandBuffer pfn_vkEndCommandBuffer = (PFN_vkEndCommandBuffer) pfn_vkGetDeviceProcAddr(*device, "vkEndCommandBuffer");
	pfn_vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	const PFN_vkQueueSubmit pfn_vkQueueSubmit = (PFN_vkQueueSubmit) pfn_vkGetDeviceProcAddr(*device, "vkQueueSubmit");
	pfn_vkQueueSubmit(*queue, 1, &submitInfo, VK_NULL_HANDLE);

	const PFN_vkQueueWaitIdle pfn_vkQueueWaitIdle = (PFN_vkQueueWaitIdle) pfn_vkGetDeviceProcAddr(*device, "vkQueueWaitIdle");
	pfn_vkQueueWaitIdle(*queue);

	const PFN_vkFreeCommandBuffers pfn_vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers) pfn_vkGetDeviceProcAddr(*device, "vkFreeCommandBuffers");
	pfn_vkFreeCommandBuffers(*device, *commandPool, 1, &commandBuffer);

	return 0;
}
