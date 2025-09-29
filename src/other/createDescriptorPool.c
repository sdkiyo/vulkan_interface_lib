#include <vk.h>

int createDescriptorPool(const LoaderTable *const pTable, const VkDevice *const device, VkDescriptorPool* descriptorPool)
{
	VkDescriptorPoolSize poolSize = {};
	poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSize.descriptorCount = IMAGE_COUNT;

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = 1;
	poolInfo.pPoolSizes = &poolSize;
	poolInfo.maxSets = IMAGE_COUNT;

	if (pTable->pfn_vkCreateDescriptorPool(*device, &poolInfo, nullptr, descriptorPool) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create instance'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	return 0;
}
