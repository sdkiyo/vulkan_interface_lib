#include "vertex.h"


uint32_t findMemoryType(const LoaderTable *const pTable, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkDevice *const device, const uint32_t typeFilter, const VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties memProperties;
	pTable->pfn_vkGetPhysicalDeviceMemoryProperties(*physicalDevice, &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}

	fprintf(stderr, RED "%s(), line %d, 'failed.'" RESET_COLOR "\n", __func__, __LINE__);
}

int createBuffer(const LoaderTable *const pTable, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkDevice *const device, const VkDeviceSize size, const VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer* buffer, VkDeviceMemory* bufferMemory)
{
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (pTable->pfn_vkCreateBuffer(*device, &bufferInfo, nullptr, buffer) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create vertex or index buffer, vkCreateBuffer() failed.'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	VkMemoryRequirements memRequirements;
	pTable->pfn_vkGetBufferMemoryRequirements(*device, *buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(pTable, instance, physicalDevice, device, memRequirements.memoryTypeBits, properties);

	if (pTable->pfn_vkAllocateMemory(*device, &allocInfo, nullptr, bufferMemory) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create vertex or index buffer, vkAllocateMemory() failed.'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	pTable->pfn_vkBindBufferMemory(*device, *buffer, *bufferMemory, 0);

	return 0;
}
