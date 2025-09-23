#include "vk.h"

int createLogicalDevice(const PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkInstance *const instance, const char* const* deviceExtensions, uint32_t deviceExtensionsCount, const VkPhysicalDevice *const physicalDevice, VkDevice *const device, VkQueue *const queue)
{
	float queuePriority = 1.0f;// ??
	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = 0;
	queueCreateInfo.queueCount = 1;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = 1;// ??
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.enabledExtensionCount = deviceExtensionsCount;
	createInfo.ppEnabledExtensionNames = deviceExtensions;

	const PFN_vkCreateDevice pfn_vkCreateDevice = (PFN_vkCreateDevice) pfn_vkGetInstanceProcAddr(*instance, "vkCreateDevice");

	if (pfn_vkCreateDevice(*physicalDevice, &createInfo, nullptr, device) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create logical device'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	const PFN_vkGetDeviceQueue pfn_vkGetDeviceQueue = (PFN_vkGetDeviceQueue) pfn_vkGetDeviceProcAddr(*device, "vkGetDeviceQueue");

	pfn_vkGetDeviceQueue(*device, 0, 0, queue);// ??

	return 0;
}
