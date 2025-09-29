#include "pre.h"

int pickPhysicalDevice(const LoaderTable *const pTable, const VkInstance *const pInstance, VkPhysicalDevice *const pPhysicalDevice)
{
	uint32_t deviceCount = 0;

	pTable->pfn_vkEnumeratePhysicalDevices(*pInstance, &deviceCount, nullptr);
	if (deviceCount == 0)
	{
		fprintf(stderr, RED "%s(), line %d, 'unable to find GPUs with vulkan support'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	VkPhysicalDevice *devices = malloc(deviceCount * sizeof(VkPhysicalDevice));// ??
	pTable->pfn_vkEnumeratePhysicalDevices(*pInstance, &deviceCount, devices);

//	VkPhysicalDeviceProperties deviceProperties;
//	for (uint32_t i = 0; i < deviceCount; i++)
//	{
//		*physicalDevice = devices[i];
//		vkGetPhysicalDeviceProperties(*physicalDevice, &deviceProperties);
//		printf("physical device name: \033[36m%s\033[0m\n", deviceProperties.deviceName);
//	}

	*pPhysicalDevice = devices[0];
	free(devices);

	return 0;
}
