#include <vk.h>

int createDescriptorSets(const LoaderTable *const pTable, const VkDevice *const device, const VkDescriptorPool *const descriptorPool, const VkDescriptorSetLayout *const descriptorSetLayout, const VkBuffer *const uniformBuffers, VkDescriptorSet* descriptorSets)
{
	VkDescriptorSetLayout layouts[IMAGE_COUNT];
	for (uint32_t i = 0; i < IMAGE_COUNT; i++)
	{
		layouts[i] = *descriptorSetLayout;
	}

	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = *descriptorPool;
	allocInfo.descriptorSetCount = IMAGE_COUNT;
	allocInfo.pSetLayouts = layouts;

	if (pTable->pfn_vkAllocateDescriptorSets(*device, &allocInfo, descriptorSets) != VK_SUCCESS)
	{
		return -1;
	}

	for (uint32_t i = 0; i < IMAGE_COUNT; i++)
	{
		VkDescriptorBufferInfo bufferInfo = {};
		bufferInfo.buffer = uniformBuffers[i];
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(UniformBufferObject);

		VkWriteDescriptorSet descriptorWrite = {};
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = descriptorSets[i];
		descriptorWrite.dstBinding = 0;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pBufferInfo = &bufferInfo;

		pTable->pfn_vkUpdateDescriptorSets(*device, 1, &descriptorWrite, 0, nullptr);
	}

	return 0;
}
