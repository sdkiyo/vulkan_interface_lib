#include "swapchain.h"

int createImageViews( const LoaderTable *const pTable, const VkDevice *const pDevice, const VkFormat *const pSwapchainImageFormat, const VkImage *const pSwapchainImages, VkImageView* pSwapchainImageViews)
{
	for (uint32_t i = 0; i < IMAGE_COUNT; i++) {
		VkImageViewCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = pSwapchainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = *pSwapchainImageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if (pTable->pfn_vkCreateImageView(*pDevice, &createInfo, nullptr, &pSwapchainImageViews[i]) != VK_SUCCESS)
		{
			fprintf(stderr, RED "%s(), line %d, 'failed to create imageViews'" RESET_COLOR "\n", __func__, __LINE__);
			return -1;
		}
	}

	return 0;
}
