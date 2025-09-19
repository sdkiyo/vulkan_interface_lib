#include "../include/vk.h"


int lvCreateInstance(VkInstance *const instance)
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.apiVersion = VK_API_VERSION_1_4;

	const char *const layers[] = {
		"VK_LAYER_KHRONOS_validation",
		"VK_LAYER_KHRONOS_validation"
	};

	const char *const extensions[] = {
		"VK_KHR_surface",
		"VK_KHR_wayland_surface",
		"VK_EXT_debug_utils"
	};

	uint32_t extensionCount = 3;
	//const char *const *const extensions = glfwGetRequiredInstanceExtensions( &extensionCount );

	printf("instance extensions:\n");
	for (int i = 0; i < extensionCount; i++)
	{
		printf("\033[35m   %s\033[0m\n", extensions[i]);
	}

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = 2;
	createInfo.ppEnabledLayerNames = layers;
	createInfo.enabledExtensionCount = extensionCount;
	createInfo.ppEnabledExtensionNames = extensions;

	if (vkCreateInstance(&createInfo, nullptr, instance) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create instance'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}
	printf("- create " BLUE "instance " GREEN "success!" RESET_COLOR "\n");

	return 0;
}
