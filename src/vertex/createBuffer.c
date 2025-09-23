#include "vk.h"


uint32_t findMemoryType(const PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkDevice *const device, const uint32_t typeFilter, const VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties memProperties;

	const PFN_vkGetPhysicalDeviceMemoryProperties pfn_vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties) pfn_vkGetInstanceProcAddr(*instance, "vkGetPhysicalDeviceMemoryProperties");

	pfn_vkGetPhysicalDeviceMemoryProperties(*physicalDevice, &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}

	fprintf(stderr, RED "%s(), line %d, 'failed.'" RESET_COLOR "\n", __func__, __LINE__);
}

int createBuffer(const PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, const PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkDevice *const device, const VkDeviceSize size, const VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer* buffer, VkDeviceMemory* bufferMemory)
{
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	const PFN_vkCreateBuffer pfn_vkCreateBuffer = (PFN_vkCreateBuffer) pfn_vkGetDeviceProcAddr(*device, "vkCreateBuffer");

	if (pfn_vkCreateBuffer(*device, &bufferInfo, nullptr, buffer) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create vertex or index buffer, vkCreateBuffer() failed.'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	VkMemoryRequirements memRequirements;

	const PFN_vkGetBufferMemoryRequirements pfn_vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements) pfn_vkGetDeviceProcAddr(*device, "vkGetBufferMemoryRequirements");

	pfn_vkGetBufferMemoryRequirements(*device, *buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(pfn_vkGetInstanceProcAddr, instance, physicalDevice, device, memRequirements.memoryTypeBits, properties);

	const PFN_vkAllocateMemory pfn_vkAllocateMemory = (PFN_vkAllocateMemory) pfn_vkGetDeviceProcAddr(*device, "vkAllocateMemory");

	if (pfn_vkAllocateMemory(*device, &allocInfo, nullptr, bufferMemory) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create vertex or index buffer, vkAllocateMemory() failed.'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	const PFN_vkBindBufferMemory pfn_vkBindBufferMemory = (PFN_vkBindBufferMemory) pfn_vkGetDeviceProcAddr(*device, "vkBindBufferMemory");

	pfn_vkBindBufferMemory(*device, *buffer, *bufferMemory, 0);

	return 0;
}
