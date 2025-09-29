#include "vertex.h"

int createIndexBuffer( const LoaderTable *const pTable, const VkInstance *const pInstance, const VkPhysicalDevice *const pPhysicalDevice, const VkDevice *const pDevice, const VkCommandPool *const pCommandPool, const VkQueue *const pQueue, VkBuffer* pIndexBuffer, VkDeviceMemory* pIndexBufferMemory, const uint16_t *const pIndices, const uint32_t indices_size)
{
	VkDeviceSize bufferSize = sizeof(pIndices[0]) * indices_size;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(pTable, pInstance, pPhysicalDevice, pDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingBuffer, &stagingBufferMemory);

	void* data;
	pTable->pfn_vkMapMemory(*pDevice, stagingBufferMemory, 0, bufferSize, 0, &data);

	memcpy(data, pIndices, (size_t) bufferSize);

	pTable->pfn_vkUnmapMemory(*pDevice, stagingBufferMemory);

	createBuffer(pTable, pInstance, pPhysicalDevice, pDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, pIndexBuffer, pIndexBufferMemory);

	copyBuffer(pTable, pDevice, pCommandPool, pQueue, &stagingBuffer, pIndexBuffer, bufferSize);

	pTable->pfn_vkDestroyBuffer(*pDevice, stagingBuffer, nullptr);

	pTable->pfn_vkFreeMemory(*pDevice, stagingBufferMemory, nullptr);
}
