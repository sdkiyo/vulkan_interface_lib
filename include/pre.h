#pragma once
#ifndef _LAVA_PRE_H_
#define _LAVA_PRE_H_

#include "vk.h"


int createInstance(
	const LoaderTable *const		pTable,
	const char* const*			ppValidationLayers,
	const uint32_t				validationLayersCount,
	const char* const*			ppExtensions,
	const uint32_t				extensionsCount,
	VkInstance *const			pInstance);

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT		severity,
	VkDebugUtilsMessageTypeFlagsEXT 		type,
	const VkDebugUtilsMessengerCallbackDataEXT*	callbackData,
	void*						pUserData);

void fillDebugUtilsMessengerCreateInfo(
	VkDebugUtilsMessengerCreateInfoEXT*	pDebugCreateInfo);

int createDebugUtilsMessenger(
	const LoaderTable *const		pTable,
	const VkInstance *const			pInstance,
	VkDebugUtilsMessengerEXT *const		pDebugMessenger);

int createSurface(
	GLFWwindow *const			pWindow,
	const VkInstance *const			pInstance,
	VkSurfaceKHR *const			pSurface);

int pickPhysicalDevice(
	const LoaderTable *const		pTable,
	const VkInstance *const			pInstance,
	VkPhysicalDevice *const			pPhysicalDevice);

int createLogicalDevice(
	const LoaderTable *const		pTable,
	const VkInstance *const			pInstance,
	const char* const*			ppDeviceExtensions,
	uint32_t				deviceExtensionsCount,
	const VkPhysicalDevice *const		pPhysicalDevice,
	VkDevice *const				pDevice,
	VkQueue *const				pQueue);


#endif
