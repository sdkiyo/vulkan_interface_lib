#include "../include/vk.h"

int createLogicalDevice(const VkPhysicalDevice *const physicalDevice, VkDevice *const device, VkQueue* queue)
{
	float queuePriority = 1.0f;
	VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.queueFamilyIndex = 0;
	deviceQueueCreateInfo.queueCount = 1;
	deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

	const char* deviceExtensions[] = {"VK_KHR_swapchain"};

	VkDeviceCreateInfo deviceCreateInfo = {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
	deviceCreateInfo.enabledExtensionCount = 1;
	deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions;

	if (vkCreateDevice(*physicalDevice, &deviceCreateInfo, nullptr, device) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create logical device'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	vkGetDeviceQueue(*device, 0, 0, queue);

	printf("- create " BLUE "device " GREEN "success!" RESET_COLOR "\n");

	return 0;
}
