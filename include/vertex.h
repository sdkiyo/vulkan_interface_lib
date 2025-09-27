#pragma once
#ifndef _LAVA_VERTEX_H_
#define _LAVA_VERTEX_H_

#include "vk.h"

int createBuffer(
	const LoaderTable *const		pTable,
	const VkInstance *const			instance,
	const VkPhysicalDevice *const		physicalDevice,
	const VkDevice *const			device,
	const VkDeviceSize			size,
	const VkBufferUsageFlags		usage,
	VkMemoryPropertyFlags			properties,
	VkBuffer*				buffer,
	VkDeviceMemory*				bufferMemory);

int copyBuffer(
	const LoaderTable *const		pTable,
	const VkDevice *const			device,
	const VkCommandPool *const		commandPool,
	const VkQueue *const			queue,
	const VkBuffer *const			srcBuffer,
	const VkBuffer *const			dstBuffer,
	const VkDeviceSize			size);

int createIndexBuffer(
	const LoaderTable *const		pTable,
	const VkInstance *const			instance,
	const VkPhysicalDevice *const		physicalDevice,
	const VkDevice *const			device,
	const VkCommandPool *const		commandPool,
	const VkQueue *const			queue,
	VkBuffer*				indexBuffer,
	VkDeviceMemory*				indexBufferMemory);

int createVertexBuffer(
	const LoaderTable *const		pTable,
	const VkInstance *const			instance,
	const VkPhysicalDevice *const		physicalDevice,
	const VkDevice *const			device,
	const VkCommandPool *const		commandPool,
	const VkQueue *const			queue,
	VkBuffer*				vertexBuffer,
	VkDeviceMemory*				vertexBufferMemory);

void getBindingDescription(VkVertexInputBindingDescription *const bindingDescription);

void getAttributeDescriptions(VkVertexInputAttributeDescription *const attributeDescriptions);


typedef struct Vertex {
	vec2 pos;
	vec3 color;
} Vertex;

static const Vertex vertices[] = {
	{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
	{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
};
static const uint32_t VERTICES_SIZE = 4;

static const uint16_t indices[] = {
	0, 1, 2, 2, 3, 0
};
static const uint32_t INDICES_SIZE = 6;



#endif
