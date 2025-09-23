#include "vertex.h"

int createVertexBuffer(const LoaderTable *const pTable, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkDevice *const device, const VkCommandPool *const commandPool, const VkQueue *const queue, VkBuffer* vertexBuffer, VkDeviceMemory* vertexBufferMemory)
{
	VkDeviceSize bufferSize = sizeof(vertices[0]) * VERTICES_SIZE;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(pTable, instance, physicalDevice, device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingBuffer, &stagingBufferMemory);

	void* data;
	pTable->pfn_vkMapMemory(*device, stagingBufferMemory, 0, bufferSize, 0, &data);

	memcpy(data, vertices, (size_t) bufferSize);

	pTable->pfn_vkUnmapMemory(*device, stagingBufferMemory);

	createBuffer(pTable, instance, physicalDevice, device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	copyBuffer(pTable, device, commandPool, queue, &stagingBuffer, vertexBuffer, bufferSize);

	pTable->pfn_vkDestroyBuffer(*device, stagingBuffer, nullptr);

	pTable->pfn_vkFreeMemory(*device, stagingBufferMemory, nullptr);
}
