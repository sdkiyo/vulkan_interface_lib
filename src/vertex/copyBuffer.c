#include "vertex.h"

int copyBuffer(const LoaderTable *const pTable, const VkDevice *const device, const VkCommandPool *const commandPool, const VkQueue *const queue, const VkBuffer *const srcBuffer, const VkBuffer *const dstBuffer, const VkDeviceSize size)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = *commandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;

	pTable->pfn_vkAllocateCommandBuffers(*device, &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	pTable->pfn_vkBeginCommandBuffer(commandBuffer, &beginInfo);

	VkBufferCopy copyRegion = {};
	copyRegion.size = size;

	pTable->pfn_vkCmdCopyBuffer(commandBuffer, *srcBuffer, *dstBuffer, 1, &copyRegion);

	pTable->pfn_vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	pTable->pfn_vkQueueSubmit(*queue, 1, &submitInfo, VK_NULL_HANDLE);

	pTable->pfn_vkQueueWaitIdle(*queue);

	pTable->pfn_vkFreeCommandBuffers(*device, *commandPool, 1, &commandBuffer);

	return 0;
}
