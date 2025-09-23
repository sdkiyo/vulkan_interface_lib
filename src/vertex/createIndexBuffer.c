#include "vk.h"

int createIndexBuffer(const PFN_vkGetInstanceProcAddr pfn_vkGetInstanceProcAddr, const PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkDevice *const device, const VkCommandPool *const commandPool, const VkQueue *const queue, VkBuffer* indexBuffer, VkDeviceMemory* indexBufferMemory)
{
	VkDeviceSize bufferSize = sizeof(indices[0]) * INDICES_SIZE;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(pfn_vkGetInstanceProcAddr, pfn_vkGetDeviceProcAddr, instance, physicalDevice, device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingBuffer, &stagingBufferMemory);

	void* data;
	const PFN_vkMapMemory pfn_vkMapMemory = (PFN_vkMapMemory) pfn_vkGetDeviceProcAddr(*device, "vkMapMemory");
	pfn_vkMapMemory(*device, stagingBufferMemory, 0, bufferSize, 0, &data);

	memcpy(data, indices, (size_t) bufferSize);

	const PFN_vkUnmapMemory pfn_vkUnmapMemory = (PFN_vkUnmapMemory) pfn_vkGetDeviceProcAddr(*device, "vkUnmapMemory");
	pfn_vkUnmapMemory(*device, stagingBufferMemory);

	createBuffer(pfn_vkGetInstanceProcAddr, pfn_vkGetDeviceProcAddr, instance, physicalDevice, device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

	copyBuffer(pfn_vkGetDeviceProcAddr, device, commandPool, queue, &stagingBuffer, indexBuffer, bufferSize);

	const PFN_vkDestroyBuffer pfn_vkDestroyBuffer = (PFN_vkDestroyBuffer) pfn_vkGetDeviceProcAddr(*device, "vkDestroyBuffer");
	pfn_vkDestroyBuffer(*device, stagingBuffer, nullptr);

	const PFN_vkFreeMemory pfn_vkFreeMemory = (PFN_vkFreeMemory) pfn_vkGetDeviceProcAddr(*device, "vkFreeMemory");
	pfn_vkFreeMemory(*device, stagingBufferMemory, nullptr);
}
