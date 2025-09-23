#pragma once
#ifndef _LAVA_SHADER_H_
#define _LAVA_SHADER_H_

#include "vk.h"

char* getShaderCode(
	const char *const			fileName,
	uint32_t *const				pShaderSize);

VkShaderModule createShaderModule(
	const LoaderTable *const		pTable,
	const VkDevice *const			device,
	const char *const			shader_code,
	const uint32_t				shader_code_size);


#endif
