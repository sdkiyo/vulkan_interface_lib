#include "vk.h"

int createSwapchain(const PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkSurfaceKHR *const surface, const VkDevice *const device, VkSwapchainKHR *swapchain, VkImage* swapchainImages, VkFormat* swapchainImageFormat, VkExtent2D* swapchainExtent)
{
	VkSurfaceCapabilitiesKHR surfaceCapabilities = {};

	const PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR pfn_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR) pfn_vkGetInstanceProcAddr(*instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");

	pfn_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*physicalDevice, *surface, &surfaceCapabilities);

	VkExtent2D extent = {720, 480};// ??

	VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
	swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCreateInfo.surface = *surface;
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

	const PFN_vkCreateSwapchainKHR pfn_vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR) pfn_vkGetDeviceProcAddr(*device, "vkCreateSwapchainKHR");

	if (pfn_vkCreateSwapchainKHR(*device, &swapchainCreateInfo, nullptr, swapchain) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create swapchain'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	uint32_t count = 0;

	const PFN_vkGetSwapchainImagesKHR pfn_vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR) pfn_vkGetDeviceProcAddr(*device, "vkGetSwapchainImagesKHR");

	pfn_vkGetSwapchainImagesKHR(*device, *swapchain, &count, nullptr);

	pfn_vkGetSwapchainImagesKHR(*device, *swapchain, &count, swapchainImages);

	*swapchainImageFormat = swapchainCreateInfo.imageFormat;// ??
	*swapchainExtent = swapchainCreateInfo.imageExtent;// ??

	return 0;
}
