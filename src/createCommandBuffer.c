#include "../include/vk.h"

int createCommandBuffer(PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, VkCommandPool* commandPool, VkCommandBuffer* commandBuffers)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = *commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = IMAGE_COUNT;// ??

	PFN_vkAllocateCommandBuffers pfn_vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)pfn_vkGetDeviceProcAddr(*device, "vkAllocateCommandBuffers");

	if (pfn_vkAllocateCommandBuffers(*device, &allocInfo, commandBuffers) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create commandBuffer'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	return 0;
}
