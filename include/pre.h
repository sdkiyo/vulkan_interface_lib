#pragma once
#ifndef _LAVA_PRE_H_
#define _LAVA_PRE_H_

#include "vk.h"


int lvCreateInstance(
	const LoaderTable *const		pTable,
	const char* const*			validationLayers,
	const uint32_t				validationLayersCount,
	const char* const*			extensions,
	const uint32_t				extensionsCount,
	VkInstance *const			instance);

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT		severity,
	VkDebugUtilsMessageTypeFlagsEXT 		type,
	const VkDebugUtilsMessengerCallbackDataEXT*	callbackData,
	void*						userData);

void fillDebugUtilsMessengerCreateInfo(
	VkDebugUtilsMessengerCreateInfoEXT*	debugCreateInfo);

int createDebugUtilsMessenger(
	const LoaderTable *const		pTable,
	const VkInstance *const			instance,
	VkDebugUtilsMessengerEXT *const		debugMessenger);

int lvCreateSurface(
	GLFWwindow *const			window,
	const VkInstance *const			instance,
	VkSurfaceKHR *const			surface);

int lvPickPhysicalDevice(
	const LoaderTable *const		pTable,
	const VkInstance *const			instance,
	VkPhysicalDevice *const			physicalDevice);

int createLogicalDevice(
	const LoaderTable *const		pTable,
	const VkInstance *const			instance,
	const char* const*			deviceExtensions,
	uint32_t				deviceExtensionsCount,
	const VkPhysicalDevice *const		physicalDevice,
	VkDevice *const				device,
	VkQueue *const				queue);


#endif
