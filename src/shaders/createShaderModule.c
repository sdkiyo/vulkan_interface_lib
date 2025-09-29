#include "shader.h"

VkShaderModule createShaderModule(const LoaderTable *const pTable, const VkDevice *const pDevice, const char *const pShader_code, const uint32_t shader_code_size)
{
	VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
	shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shaderModuleCreateInfo.codeSize = shader_code_size;
	shaderModuleCreateInfo.pCode = (const uint32_t *) pShader_code;

	VkShaderModule shaderModule;

	if (pTable->pfn_vkCreateShaderModule(*pDevice, &shaderModuleCreateInfo, nullptr, &shaderModule) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create shader module'" RESET_COLOR "\n", __func__, __LINE__);
		return nullptr;
	}

	return shaderModule;
}
