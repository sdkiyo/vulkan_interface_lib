#include "../include/vk.h"

VkShaderModule createShaderModule(const VkDevice *const device, const char* shader_code, const uint32_t shader_code_size)
{
	VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
	shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shaderModuleCreateInfo.codeSize = shader_code_size;
	shaderModuleCreateInfo.pCode = (const uint32_t *)shader_code;

	VkShaderModule shaderModule;

	if (vkCreateShaderModule(*device, &shaderModuleCreateInfo, nullptr, &shaderModule) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create shader module'" RESET_COLOR "\n", __func__, __LINE__);
		return nullptr;
	}
	printf("- - create " BLUE "shader module " GREEN "success!" RESET_COLOR "\n");

	return shaderModule;
}
