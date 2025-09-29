#include "vertex.h"

int copyBuffer( const LoaderTable *const pTable, const VkDevice *const pDevice, const VkCommandPool *const pCommandPool, const VkQueue *const pQueue, const VkBuffer *const pSrcBuffer, const VkBuffer *const pDstBuffer, const VkDeviceSize size)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = *pCommandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;

	pTable->pfn_vkAllocateCommandBuffers(*pDevice, &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	pTable->pfn_vkBeginCommandBuffer(commandBuffer, &beginInfo);

	VkBufferCopy copyRegion = {};
	copyRegion.size = size;

	pTable->pfn_vkCmdCopyBuffer(commandBuffer, *pSrcBuffer, *pDstBuffer, 1, &copyRegion);

	pTable->pfn_vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	pTable->pfn_vkQueueSubmit(*pQueue, 1, &submitInfo, VK_NULL_HANDLE);

	pTable->pfn_vkQueueWaitIdle(*pQueue);

	pTable->pfn_vkFreeCommandBuffers(*pDevice, *pCommandPool, 1, &commandBuffer);

	return 0;
}
