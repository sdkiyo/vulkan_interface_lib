#include "swapchain.h"

int createSwapchain( const LoaderTable *const pTable, const VkInstance *const pInstance, const VkPhysicalDevice *const pPhysicalDevice, const VkSurfaceKHR *const pSurface, const VkDevice *const pDevice, VkSwapchainKHR* pSwapchain, VkImage* pSwapchainImages, VkFormat* pSwapchainImageFormat, VkExtent2D* pSwapchainExtent)
{
	VkSurfaceCapabilitiesKHR surfaceCapabilities = {};

	pTable->pfn_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*pPhysicalDevice, *pSurface, &surfaceCapabilities);

	VkExtent2D extent = {1920, 1080};// ??

	VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
	swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCreateInfo.surface = *pSurface;
	swapchainCreateInfo.minImageCount = IMAGE_COUNT;
	swapchainCreateInfo.imageFormat = VK_FORMAT_B8G8R8A8_SRGB;
	swapchainCreateInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	swapchainCreateInfo.imageExtent = extent;
	swapchainCreateInfo.imageArrayLayers = 1;
	swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchainCreateInfo.preTransform = surfaceCapabilities.currentTransform;
	swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchainCreateInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;// ??
	swapchainCreateInfo.clipped = VK_TRUE;
	swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

	if (pTable->pfn_vkCreateSwapchainKHR(*pDevice, &swapchainCreateInfo, nullptr, pSwapchain) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create swapchain'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	uint32_t count = 0;

	pTable->pfn_vkGetSwapchainImagesKHR(*pDevice, *pSwapchain, &count, nullptr);

	pTable->pfn_vkGetSwapchainImagesKHR(*pDevice, *pSwapchain, &count, pSwapchainImages);

	*pSwapchainImageFormat = swapchainCreateInfo.imageFormat;// ??
	*pSwapchainExtent = swapchainCreateInfo.imageExtent;// ??

	return 0;
}
