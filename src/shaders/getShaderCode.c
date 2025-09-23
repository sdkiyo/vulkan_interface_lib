#include "shader.h"

char* getShaderCode(const char *const file_name, uint32_t *const pShaderSize)
{
	FILE *file = nullptr;
	file = fopen(file_name, "rb+");
	if(file == nullptr)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to read shader'" RESET_COLOR "\n", __func__, __LINE__);
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
