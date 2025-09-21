#include "../include/vk.h"


int lvCreateInstance(PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, const char* const* validationLayers, const uint32_t validationLayersCount, const char* const* extensions, const uint32_t extensionsCount, VkInstance *const instance)
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.apiVersion = VK_API_VERSION_1_4;

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
	fillDebugUtilsMessengerCreateInfo(&debugCreateInfo);

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pNext = &debugCreateInfo;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = validationLayersCount;
	createInfo.ppEnabledLayerNames = validationLayers;
	createInfo.enabledExtensionCount = extensionsCount;
	createInfo.ppEnabledExtensionNames = extensions;

	PFN_vkCreateInstance pfn_vkCreateInstance = (PFN_vkCreateInstance)pfn_vkGetInstanceProcAddr(NULL, "vkCreateInstance");

	if (pfn_vkCreateInstance(&createInfo, nullptr, instance) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create instance'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	return 0;
}
