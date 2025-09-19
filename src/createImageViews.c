#include "../include/vk.h"

int createImageViews(VkDevice* device, VkFormat* swapchainImageFormat, VkImage* swapchainImages, VkImageView* swapchainImageViews)
{
	for (size_t i = 0; i < IMAGE_COUNT; i++) {
		VkImageViewCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = swapchainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = *swapchainImageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(*device, &createInfo, nullptr, &swapchainImageViews[i]) != VK_SUCCESS)
		{
			fprintf(stderr, RED "%s(), line %d, 'failed to create imageViews'" RESET_COLOR "\n", __func__, __LINE__);
			return -1;
		}
	}

	printf("- create " BLUE "imageViews " GREEN "success!" RESET_COLOR "\n");

	return 0;
}
