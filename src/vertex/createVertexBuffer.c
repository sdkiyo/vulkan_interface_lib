#include "vertex.h"

int createVertexBuffer( const LoaderTable *const pTable, const VkInstance *const pInstance, const VkPhysicalDevice *const pPhysicalDevice, const VkDevice *const pDevice, const VkCommandPool *const pCommandPool, const VkQueue *const pQueue, VkBuffer* pVertexBuffer, VkDeviceMemory* pVertexBufferMemory, const Vertex *const pVertices, const uint32_t vertices_size)
{
	VkDeviceSize bufferSize = sizeof(pVertices[0]) * vertices_size;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(pTable, pInstance, pPhysicalDevice, pDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingBuffer, &stagingBufferMemory);

	void* data;
	pTable->pfn_vkMapMemory(*pDevice, stagingBufferMemory, 0, bufferSize, 0, &data);

	memcpy(data, pVertices, (size_t) bufferSize);

	pTable->pfn_vkUnmapMemory(*pDevice, stagingBufferMemory);

	createBuffer(pTable, pInstance, pPhysicalDevice, pDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, pVertexBuffer, pVertexBufferMemory);

	copyBuffer(pTable, pDevice, pCommandPool, pQueue, &stagingBuffer, pVertexBuffer, bufferSize);

	pTable->pfn_vkDestroyBuffer(*pDevice, stagingBuffer, nullptr);

	pTable->pfn_vkFreeMemory(*pDevice, stagingBufferMemory, nullptr);
}
