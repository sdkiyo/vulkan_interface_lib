#include "vk.h"

int createVertexBuffer(const PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, const PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkDevice *const device, const VkCommandPool *const commandPool, const VkQueue *const queue, VkBuffer* vertexBuffer, VkDeviceMemory* vertexBufferMemory)
{
	VkDeviceSize bufferSize = sizeof(vertices[0]) * VERTICES_SIZE;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(pfn_vkGetInstanceProcAddr, pfn_vkGetDeviceProcAddr, instance, physicalDevice, device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingBuffer, &stagingBufferMemory);

	void* data;
	const PFN_vkMapMemory pfn_vkMapMemory = (PFN_vkMapMemory) pfn_vkGetDeviceProcAddr(*device, "vkMapMemory");
	pfn_vkMapMemory(*device, stagingBufferMemory, 0, bufferSize, 0, &data);

	memcpy(data, vertices, (size_t) bufferSize);

	const PFN_vkUnmapMemory pfn_vkUnmapMemory = (PFN_vkUnmapMemory) pfn_vkGetDeviceProcAddr(*device, "vkUnmapMemory");
	pfn_vkUnmapMemory(*device, stagingBufferMemory);

	createBuffer(pfn_vkGetInstanceProcAddr, pfn_vkGetDeviceProcAddr, instance, physicalDevice, device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	copyBuffer(pfn_vkGetDeviceProcAddr, device, commandPool, queue, &stagingBuffer, vertexBuffer, bufferSize);

	const PFN_vkDestroyBuffer pfn_vkDestroyBuffer = (PFN_vkDestroyBuffer) pfn_vkGetDeviceProcAddr(*device, "vkDestroyBuffer");
	pfn_vkDestroyBuffer(*device, stagingBuffer, nullptr);

	const PFN_vkFreeMemory pfn_vkFreeMemory = (PFN_vkFreeMemory) pfn_vkGetDeviceProcAddr(*device, "vkFreeMemory");
	pfn_vkFreeMemory(*device, stagingBufferMemory, nullptr);
}
