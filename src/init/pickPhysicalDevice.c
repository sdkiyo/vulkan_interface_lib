#include "vk.h"

int lvPickPhysicalDevice(const PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, const VkInstance *const instance, VkPhysicalDevice *const physicalDevice)
{
	uint32_t deviceCount = 0;

	const PFN_vkEnumeratePhysicalDevices pfn_vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices) pfn_vkGetInstanceProcAddr(*instance, "vkEnumeratePhysicalDevices");

	pfn_vkEnumeratePhysicalDevices(*instance, &deviceCount, nullptr);
	if (deviceCount == 0)
	{
		fprintf(stderr, RED "%s(), line %d, 'unable to find GPUs with vulkan support'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	VkPhysicalDevice *devices = malloc(deviceCount * sizeof(VkPhysicalDevice));// ??
	pfn_vkEnumeratePhysicalDevices(*instance, &deviceCount, devices);

//	VkPhysicalDeviceProperties deviceProperties;
//	for (uint32_t i = 0; i < deviceCount; i++)
//	{
//		*physicalDevice = devices[i];
//		vkGetPhysicalDeviceProperties(*physicalDevice, &deviceProperties);
//		printf("physical device name: \033[36m%s\033[0m\n", deviceProperties.deviceName);
//	}

	*physicalDevice = devices[0];
	free(devices);

	return 0;
}
