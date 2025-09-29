#include "renderer.h"

int createCommandBuffer(const LoaderTable *const pTable, const VkDevice *const pDevice, VkCommandPool* pCommandPool, VkCommandBuffer* pCommandBuffers)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = *pCommandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = IMAGE_COUNT;// ??

	if (pTable->pfn_vkAllocateCommandBuffers(*pDevice, &allocInfo, pCommandBuffers) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create commandBuffer'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	return 0;
}
