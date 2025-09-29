#include "pre.h"

VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback( VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* pUserData)
{
	if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
	{
		fprintf(stderr, CYAN "Validation layer [info]: [%s] " RESET_COLOR "%s" RESET_COLOR "\n", callbackData->pMessageIdName, callbackData->pMessage);
	}
	else if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
	{
		fprintf(stderr, BLUE "Validation layer [verbose]: [%s] " RESET_COLOR "%s" RESET_COLOR "\n", callbackData->pMessageIdName, callbackData->pMessage);
	}
	else if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		fprintf(stderr, YELLOW "Validation layer [warning]: [%s] " YELLOW "%s" RESET_COLOR "\n\n", callbackData->pMessageIdName, callbackData->pMessage);
	}
	else if (severity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		fprintf(stderr, RED "Validation layer [error]: [%s] " YELLOW "%s" RESET_COLOR "\n\n", callbackData->pMessageIdName, callbackData->pMessage);
	}
	else
	{
		fprintf(stderr, RED "Validation layer [unknown]: [%s] " RESET_COLOR "%s\n", callbackData->pMessageIdName, callbackData->pMessage);
	}

	return VK_FALSE;
}

void fillDebugUtilsMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* pDebugCreateInfo)
{
	pDebugCreateInfo->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

	pDebugCreateInfo->messageSeverity =
	//	VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
	//	VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

	pDebugCreateInfo->messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

	pDebugCreateInfo->pfnUserCallback = debugCallback;
}

int createDebugUtilsMessenger(const LoaderTable *const pTable, const VkInstance *const pInstance, VkDebugUtilsMessengerEXT *const pDebugMessenger)
{
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
	fillDebugUtilsMessengerCreateInfo(&debugCreateInfo);

	if (pTable->pfn_vkCreateDebugUtilsMessengerEXT(*pInstance, &debugCreateInfo, nullptr, pDebugMessenger) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create debugUtilsMessenger'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	return 0;
}
