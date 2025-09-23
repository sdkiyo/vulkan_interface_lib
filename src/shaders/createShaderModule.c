#include "vk.h"

VkShaderModule createShaderModule(const PFN_vkGetDeviceProcAddr pfn_vkGetDeviceProcAddr, const VkDevice *const device, const char *const shader_code, const uint32_t shader_code_size)
{
	VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
	shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shaderModuleCreateInfo.codeSize = shader_code_size;
	shaderModuleCreateInfo.pCode = (const uint32_t *)shader_code;

	VkShaderModule shaderModule;

	const PFN_vkCreateShaderModule pfn_vkCreateShaderModule = (PFN_vkCreateShaderModule) pfn_vkGetDeviceProcAddr(*device, "vkCreateShaderModule");

	if (pfn_vkCreateShaderModule(*device, &shaderModuleCreateInfo, nullptr, &shaderModule) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create shader module'" RESET_COLOR "\n", __func__, __LINE__);
		return nullptr;
	}

	return shaderModule;
}
