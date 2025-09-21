#include "../include/vk.h"

int createLogicalDevice(PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkInstance *const instance, const char* const* deviceExtensions, uint32_t deviceExtensionsCount, const VkPhysicalDevice *const physicalDevice, VkDevice *const device, VkQueue *const queue)
{
	float queuePriority = 1.0f;
	VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.queueFamilyIndex = 0;
	deviceQueueCreateInfo.queueCount = 1;
	deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

	//const char *const deviceExtensions[] = {"VK_KHR_swapchain"};
	printf("device extensions:\n");
	for (uint32_t i = 0; i < deviceExtensionsCount; i++)
	{
		printf("\033[35m   %s\033[0m\n", deviceExtensions[i]);
	}

	VkDeviceCreateInfo deviceCreateInfo = {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
	deviceCreateInfo.enabledExtensionCount = deviceExtensionsCount;
	deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions;

	PFN_vkCreateDevice pfn_vkCreateDevice = (PFN_vkCreateDevice)pfn_vkGetInstanceProcAddr(*instance, "vkCreateDevice");

	if (pfn_vkCreateDevice(*physicalDevice, &deviceCreateInfo, nullptr, device) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create logical device'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	PFN_vkGetDeviceQueue pfn_vkGetDeviceQueue = (PFN_vkGetDeviceQueue)pfn_vkGetDeviceProcAddr(*device, "vkGetDeviceQueue");

	pfn_vkGetDeviceQueue(*device, 0, 0, queue);

	return 0;
}
