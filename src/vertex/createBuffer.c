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

int createBuffer( const LoaderTable *const pTable, const VkInstance *const pInstance, const VkPhysicalDevice *const pPhysicalDevice, const VkDevice *const pDevice, const VkDeviceSize size, const VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer* pBuffer, VkDeviceMemory* pBufferMemory)
{
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (pTable->pfn_vkCreateBuffer(*pDevice, &bufferInfo, nullptr, pBuffer) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create vertex or index buffer, vkCreateBuffer() failed.'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	VkMemoryRequirements memRequirements;
	pTable->pfn_vkGetBufferMemoryRequirements(*pDevice, *pBuffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(pTable, pInstance, pPhysicalDevice, pDevice, memRequirements.memoryTypeBits, properties);

	if (pTable->pfn_vkAllocateMemory(*pDevice, &allocInfo, nullptr, pBufferMemory) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create vertex or index buffer, vkAllocateMemory() failed.'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	pTable->pfn_vkBindBufferMemory(*pDevice, *pBuffer, *pBufferMemory, 0);

	return 0;
}
