#include "../include/vk.h"

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback( VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* userData)
{
      fprintf(stderr, RED "Validation layer: [%s] " YELLOW "%s" RESET_COLOR "\n\n", callbackData->pMessageIdName, callbackData->pMessage);
      return VK_FALSE;
}

void createDebugUtilsMessenger(const VkInstance *const instance, VkDebugUtilsMessengerEXT *const debugMessenger)
{
	PFN_vkCreateDebugUtilsMessengerEXT pfnCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(*instance, "vkCreateDebugUtilsMessengerEXT");

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
	debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

	debugCreateInfo.messageSeverity =
	//	VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
	//	VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

	debugCreateInfo.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	debugCreateInfo.pfnUserCallback = debugCallback;

	pfnCreateDebugUtilsMessengerEXT(*instance, &debugCreateInfo, nullptr, debugMessenger);
}

void destroyDebugUtilsMessenger(const VkInstance *const instance, VkDebugUtilsMessengerEXT *const debugMessenger)
{
	PFN_vkDestroyDebugUtilsMessengerEXT pfnDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(*instance, "vkDestroyDebugUtilsMessengerEXT");

   	pfnDestroyDebugUtilsMessengerEXT(*instance, *debugMessenger, nullptr);
}
