#include <vk.h>
#include <vertex.h>

int createUniformBuffers(const LoaderTable *const pTable, const VkInstance *const instance, const VkPhysicalDevice *const physicalDevice, const VkDevice *const device, VkBuffer *const uniformBuffers, VkDeviceMemory *const uniformBuffersMemory, void* *const uniformBuffersMapped)
{
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);

	for (size_t i = 0; i < IMAGE_COUNT; i++)
	{
		createBuffer(pTable, instance, physicalDevice, device, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &uniformBuffers[i], &uniformBuffersMemory[i]);

		pTable->pfn_vkMapMemory(*device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
	}

	return 0;
}
