#include "../include/vk.h"

int createCommandPool(const VkDevice *const device, VkCommandPool* commandPool)
{
        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = 0;

        if (vkCreateCommandPool(*device, &poolInfo, nullptr, commandPool) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create commandPool'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}
	printf("- create " BLUE "commandPool " GREEN "success!" RESET_COLOR "\n");

	return 0;
}
