#include "../include/vk.h"

int createFramebuffers(PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, const VkExtent2D *const swapchainExtent, const VkRenderPass *const renderPass, const VkImageView *const swapchainImageViews, VkFramebuffer* swapchainFramebuffers)
{
	for (uint32_t i = 0; i < IMAGE_COUNT; i++) {
		VkImageView attachments[] = { swapchainImageViews[i] };

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = *renderPass;
		framebufferInfo.attachmentCount = (uint32_t) (sizeof(attachments) / sizeof(*attachments));
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = swapchainExtent->width;
		framebufferInfo.height = swapchainExtent->height;
		framebufferInfo.layers = 1;

		PFN_vkCreateFramebuffer pfn_vkCreateFramebuffer = (PFN_vkCreateFramebuffer)pfn_vkGetDeviceProcAddr(*device, "vkCreateFramebuffer");

		if (pfn_vkCreateFramebuffer(*device, &framebufferInfo, nullptr, &swapchainFramebuffers[i]) != VK_SUCCESS) {
			fprintf(stderr, RED "%s(), line %d, 'failed to create framebuffer'" RESET_COLOR "\n", __func__, __LINE__);
			return -1;
		}
	}

	return 0;
}
