#pragma once
#ifndef _LAVA_VERTEX_H_
#define _LAVA_VERTEX_H_

#include "vk.h"

int createBuffer(
	const LoaderTable *const		pTable,
	const VkInstance *const			pInstance,
	const VkPhysicalDevice *const		pPhysicalDevice,
	const VkDevice *const			pDevice,
	const VkDeviceSize			size,
	const VkBufferUsageFlags		usage,
	VkMemoryPropertyFlags			properties,
	VkBuffer*				pBuffer,
	VkDeviceMemory*				pBufferMemory);

int copyBuffer(
	const LoaderTable *const		pTable,
	const VkDevice *const			pDevice,
	const VkCommandPool *const		pCommandPool,
	const VkQueue *const			pQueue,
	const VkBuffer *const			pSrcBuffer,
	const VkBuffer *const			pDstBuffer,
	const VkDeviceSize			size);

int createIndexBuffer(
	const LoaderTable *const		pTable,
	const VkInstance *const			pInstance,
	const VkPhysicalDevice *const		pPhysicalDevice,
	const VkDevice *const			pDevice,
	const VkCommandPool *const		pCommandPool,
	const VkQueue *const			pQueue,
	VkBuffer*				pIndexBuffer,
	VkDeviceMemory*				pIndexBufferMemory,
	const uint16_t *const			pIndices,
	const uint32_t				indices_size);

int createVertexBuffer(
	const LoaderTable *const		pTable,
	const VkInstance *const			pInstance,
	const VkPhysicalDevice *const		pPhysicalDevice,
	const VkDevice *const			pDevice,
	const VkCommandPool *const		pCommandPool,
	const VkQueue *const			pQueue,
	VkBuffer*				pVertexBuffer,
	VkDeviceMemory*				pVertexBufferMemory,
	const Vertex *const			pVertices,
	const uint32_t				vertices_size);

void getBindingDescription(VkVertexInputBindingDescription *const pBindingDescription);

void getAttributeDescriptions(VkVertexInputAttributeDescription *const pAttributeDescriptions);




#endif
