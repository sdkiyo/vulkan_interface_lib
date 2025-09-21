#include "../include/vk.h"


int lvCreateInstance(const char* const* validationLayers, const uint32_t validationLayersCount, const char* const* extensions, const uint32_t extensionsCount, VkInstance *const instance)
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.apiVersion = VK_API_VERSION_1_4;

//	const char *const layers[] = {
	//	"VK_LAYER_KHRONOS_validation",
//		"VK_LAYER_KHRONOS_validation"
//	};

//	const char *const extensions[] = {
//		"VK_KHR_surface",
//		"VK_KHR_wayland_surface",
//		"VK_EXT_debug_utils"
//	};

//	uint32_t extensionCount = 3;
	//const char *const *const extensions = glfwGetRequiredInstanceExtensions( &extensionCount );

	printf("validation layers:\n");
	for (uint32_t i = 0; i < validationLayersCount; i++)
	{
		printf("\033[35m   %s\033[0m\n", validationLayers[i]);
	}
	printf("instance extensions:\n");
	for (uint32_t i = 0; i < extensionsCount; i++)
	{
		printf("\033[35m   %s\033[0m\n", extensions[i]);
	}

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
	fillDebugUtilsMessengerCreateInfo(&debugCreateInfo);

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = validationLayersCount;
	createInfo.ppEnabledLayerNames = validationLayers;
	createInfo.enabledExtensionCount = extensionsCount;
	createInfo.ppEnabledExtensionNames = extensions;

	//PFN_vkVoidFunction pfnCreateInstance = vkGetInstanceProcAddr(*instance, "vkCreateDebugUtilsMessengerEXT");
	void *vklib = dlopen("/usr/lib64/libvulkan.so", RTLD_LAZY);
	typedef VkResult (*PFN_vkCreateInstance)(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
	PFN_vkCreateInstance pfn_vkCreateInstance = dlsym(vklib, "vkCreateInstance");
	if (pfn_vkCreateInstance(&createInfo, nullptr, instance) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create instance'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	return 0;
}
