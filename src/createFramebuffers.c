#include "../include/vk.h"

int createFramebuffers(VkDevice* device, VkExtent2D* swapchainExtent, VkRenderPass* renderPass, VkImageView* swapchainImageViews, VkFramebuffer* swapchainFramebuffers)
{
	for (size_t i = 0; i < IMAGE_COUNT; i++) {
		VkImageView attachments[] = { swapchainImageViews[i] };

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = *renderPass;
		framebufferInfo.attachmentCount = (uint32_t) (sizeof(attachments) / sizeof(*attachments));
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapchainExtent->width;
		framebufferInfo.height = swapchainExtent->height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(*device, &framebufferInfo, nullptr, &swapchainFramebuffers[i]) != VK_SUCCESS) {
			fprintf(stderr, RED "%s(), line %d, 'failed to create framebuffer'" RESET_COLOR "\n", __func__, __LINE__);
			return -1;
		}
	}
	printf("- create " BLUE "framebuffer " GREEN "success!" RESET_COLOR "\n");

	return 0;
}
