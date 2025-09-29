#pragma once
#ifndef _LAVA_SHADER_H_
#define _LAVA_SHADER_H_

#include "vk.h"

char* getShaderCode(
	const char *const			pFileName,
	uint32_t *const				pShaderSize);

VkShaderModule createShaderModule(
	const LoaderTable *const		pTable,
	const VkDevice *const			pDevice,
	const char *const			pShader_code,
	const uint32_t				shader_code_size);


#endif
