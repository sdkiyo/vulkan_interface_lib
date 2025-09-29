#include "swapchain.h"

int createFramebuffers( const LoaderTable *const pTable, const VkDevice *const pDevice, const VkExtent2D *const pSwapchainExtent, const VkRenderPass *const pRenderPass, const VkImageView *const pSwapchainImageViews, VkFramebuffer* pSwapchainFramebuffers)
{
	for (uint32_t i = 0; i < IMAGE_COUNT; i++) {
		VkImageView attachments[] = { pSwapchainImageViews[i] };

		VkFramebufferCreateInfo framebufferInfo = {};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = *pRenderPass;
		framebufferInfo.attachmentCount = (uint32_t) (sizeof(attachments) / sizeof(*attachments));
		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = pSwapchainExtent->width;// ??
		framebufferInfo.height = pSwapchainExtent->height;// ??
		framebufferInfo.layers = 1;

		if (pTable->pfn_vkCreateFramebuffer(*pDevice, &framebufferInfo, nullptr, &pSwapchainFramebuffers[i]) != VK_SUCCESS) {
			fprintf(stderr, RED "%s(), line %d, 'failed to create framebuffer'" RESET_COLOR "\n", __func__, __LINE__);
			return -1;
		}
	}

	return 0;
}
