#include <vk.h>

int createDescriptorSetLayout(const LoaderTable *const pTable, const VkDevice *const device, VkDescriptorSetLayout *const descriptorSetLayout)
{
	VkDescriptorSetLayoutBinding uboLayoutBinding = {};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.pImmutableSamplers = nullptr;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = 1;
	layoutInfo.pBindings = &uboLayoutBinding;

	if (pTable->pfn_vkCreateDescriptorSetLayout(*device, &layoutInfo, nullptr, descriptorSetLayout) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create instance'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	return 0;
}
