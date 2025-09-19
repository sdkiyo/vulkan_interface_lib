#include "../include/vk.h"

char* getShaderCode(const char *const file_name, uint32_t *const pShaderSize)
{
	FILE *file = nullptr;
	file = fopen(file_name, "rb+");
	if(file == nullptr)
	{
		return nullptr;
	}
	fseek(file, 0l, SEEK_END);
	*pShaderSize = (uint32_t)ftell(file);
	rewind(file);

	char *shaderCode = (char *)malloc((*pShaderSize) * sizeof(char));
	fread(shaderCode, 1, *pShaderSize, file);

	fclose(file);
	return shaderCode;
}
