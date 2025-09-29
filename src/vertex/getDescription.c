#include "vertex.h"


void getBindingDescription(VkVertexInputBindingDescription *const pBindingDescription)
{
	pBindingDescription->binding = 0;
	pBindingDescription->stride = sizeof(Vertex);
	pBindingDescription->inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
}

void getAttributeDescriptions(VkVertexInputAttributeDescription *const pAttributeDescriptions)
{
	pAttributeDescriptions[0].binding = 0;
	pAttributeDescriptions[0].location = 0;
	pAttributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	pAttributeDescriptions[0].offset = offsetof(Vertex, pos);

	pAttributeDescriptions[1].binding = 0;
	pAttributeDescriptions[1].location = 1;
	pAttributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	pAttributeDescriptions[1].offset = offsetof(Vertex, color);
}
