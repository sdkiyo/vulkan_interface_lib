#include "../../include/vk.h"


int main()
{
	printf(GRAY ITALIC "test1 start." RESET_COLOR "\n");

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        GLFWwindow* window = glfwCreateWindow(720, 480, "No title", nullptr, nullptr);//	1920x810 or 1920x960   1920x1080
	if (window == nullptr)
	{
		glfwTerminate();
		fprintf(stderr, RED "failed to create glfw window." RESET_COLOR "\n");
		exit(-1);
	}

	const char *const layers[] = {
	//	"VK_LAYER_KHRONOS_validation",
		"VK_LAYER_KHRONOS_validation"
	};

	//uint32_t extensionCount = 3;
	//const char *const *const extensions = glfwGetRequiredInstanceExtensions( &extensionCount );
	const char *const instanceExtensions[] = {
		"VK_KHR_surface",
		"VK_KHR_wayland_surface",
		"VK_EXT_debug_utils"
	};
	const char *const deviceExtensions[] = {"VK_KHR_swapchain"};
	lvParam param = {};
	param.window = window;
	param.validationLayersCount = 1;
	param.validationLayers = layers;
	param.instanceExtensionsCount = 3;
	param.instanceExtensions = instanceExtensions;
	param.deviceExtensionsCount = 1;
	param.deviceExtensions = deviceExtensions;
	param.imageCount = 4;

	void *vklib = dlopen("./liblava.so", RTLD_LAZY);
	const PFN_lvInitVulkan pfn_lvInitVulkan = dlsym(vklib, "lvInitVulkan");
	const PFN_drawFrame pfn_drawFrame = dlsym(vklib, "drawFrame");
	const PFN_lvTerminate pfn_lvTerminate = dlsym(vklib, "lvTerminate");

	lvData lvdata = {};
	LoaderTable loaderTable = {};
	pfn_lvInitVulkan(&param, &lvdata, &loaderTable);

	char ch = ' ';
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		pfn_drawFrame(&lvdata, &loaderTable);
		//ch = getchar();
		if (ch == 'q')
		{
			break;
		}
	}
	PFN_vkDeviceWaitIdle pfn_vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle) loaderTable.pfn_vkGetInstanceProcAddr(lvdata.instance, "vkDeviceWaitIdle");
	pfn_vkDeviceWaitIdle(lvdata.device);


	glfwDestroyWindow(window);

	pfn_lvTerminate(&lvdata, &loaderTable);
	dlclose(vklib);

	glfwTerminate();

	printf(GRAY ITALIC "test1 end." RESET_COLOR "\n");
	return 0;
}
