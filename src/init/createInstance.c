#include "pre.h"


int createInstance(const LoaderTable *const pTable, const char* const* ppValidationLayers, const uint32_t validationLayersCount, const char* const* ppExtensions, const uint32_t extensionsCount, VkInstance *const pInstance)
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
	createInfo.ppEnabledLayerNames = ppValidationLayers;
	createInfo.enabledExtensionCount = extensionsCount;
	createInfo.ppEnabledExtensionNames = ppExtensions;

	if (pTable->pfn_vkCreateInstance(&createInfo, nullptr, pInstance) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create instance'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	return 0;
}
