#include "renderer.h"

int createSyncObjects(const LoaderTable *const pTable, const VkDevice *const device, VkSemaphore *const imageAvailableSemaphore, VkSemaphore *const renderFinishedSemaphore, VkFence *const inFlightFence)
{
	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (uint32_t i = 0; i < IMAGE_COUNT; i++)
	{
		if (pTable->pfn_vkCreateSemaphore(*device, &semaphoreInfo, nullptr, &imageAvailableSemaphore[i]) != VK_SUCCESS)
		{
			fprintf(stderr, RED "%s(), line %d, 'failed to create syncObjects:imageAvailableSemaphore'" RESET_COLOR "\n", __func__, __LINE__);
			return -1;
		}

		if (pTable->pfn_vkCreateSemaphore(*device, &semaphoreInfo, nullptr, &renderFinishedSemaphore[i]) != VK_SUCCESS)
		{
			fprintf(stderr, RED "%s(), line %d, 'failed to create syncObjects:renderFiniahedSemaphore'" RESET_COLOR "\n", __func__, __LINE__);
			return -1;
		}

		if (pTable->pfn_vkCreateFence(*device, &fenceInfo, nullptr, &inFlightFence[i]) != VK_SUCCESS)
		{
			fprintf(stderr, RED "%s(), line %d, 'failed to create syncObjects:inFlightFence'" RESET_COLOR "\n", __func__, __LINE__);
			return -1;
		}
	}

	return 0;
}
