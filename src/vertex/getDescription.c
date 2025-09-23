#include "vk.h"


void getBindingDescription(VkVertexInputBindingDescription *const bindingDescription)
{
	bindingDescription->binding = 0;
	bindingDescription->stride = sizeof(Vertex);
	bindingDescription->inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
}

void getAttributeDescriptions(VkVertexInputAttributeDescription *const attributeDescriptions)
{
	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
	attributeDescriptions[0].offset = offsetof(Vertex, pos);

	attributeDescriptions[1].binding = 0;
	attributeDescriptions[1].location = 1;
	attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[1].offset = offsetof(Vertex, color);
}
