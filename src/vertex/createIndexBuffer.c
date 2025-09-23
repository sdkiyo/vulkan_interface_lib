#include "vertex.h"

int createIndexBuffer(const LoaderTable *const pTable, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkDevice *const device, const VkCommandPool *const commandPool, const VkQueue *const queue, VkBuffer* indexBuffer, VkDeviceMemory* indexBufferMemory)
{
	VkDeviceSize bufferSize = sizeof(indices[0]) * INDICES_SIZE;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(pTable, instance, physicalDevice, device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingBuffer, &stagingBufferMemory);

	void* data;
	pTable->pfn_vkMapMemory(*device, stagingBufferMemory, 0, bufferSize, 0, &data);

	memcpy(data, indices, (size_t) bufferSize);

	pTable->pfn_vkUnmapMemory(*device, stagingBufferMemory);

	createBuffer(pTable, instance, physicalDevice, device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

	copyBuffer(pTable, device, commandPool, queue, &stagingBuffer, indexBuffer, bufferSize);

	pTable->pfn_vkDestroyBuffer(*device, stagingBuffer, nullptr);

	pTable->pfn_vkFreeMemory(*device, stagingBufferMemory, nullptr);
}
