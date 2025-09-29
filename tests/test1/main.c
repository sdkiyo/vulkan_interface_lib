#include "../../include/vk.h"


int main()
{
	printf(GRAY ITALIC "test1 start." RESET_COLOR "\n");

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        GLFWwindow* window = glfwCreateWindow(1920, 1080, "No title", nullptr, nullptr);//	1920x810 or 1920x960   1920x1080
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


	const Vertex vertices[] = {
		{{-1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
		{{1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
		{{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
		{{-1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},

		{{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
		{{1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}},
		{{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
		{{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}},


		{{-1.0f, -1.0f, -1.5f}, {0.2f, 0.2f, 0.2f}},
		{{1.0f, -1.0f, -1.5f}, {0.2f, 0.2f, 0.2f}},
		{{1.0f, 1.0f, -1.5f}, {0.2f, 0.2f, 0.2f}},
		{{-1.0f, 1.0f, -1.5f}, {0.2f, 0.2f, 0.2f}},

		{{-1.0f, -1.0f, -3.5f}, {0.2f, 0.2f, 0.2f}},
		{{1.0f, -1.0f, -3.5f}, {0.2f, 0.2f, 0.2f}},
		{{1.0f, 1.0f, -3.5f}, {0.2f, 0.2f, 0.2f}},
		{{-1.0f, 1.0f, -3.5f}, {0.2f, 0.2f, 0.2f}}
	};

	const uint16_t indices[] = {
		0, 1, 2, 2, 3, 0,
		6, 5, 4, 4, 7, 6,
		6, 7, 3,
		3, 7, 4,
		2, 6, 3,
		0, 3, 4,
		1, 0, 5,
		0, 4, 5,
		2, 1, 6,
		1, 5, 6,


		8, 9, 10, 10, 11, 8,
		14, 13, 12, 12, 15, 14,
		14, 15, 11,
		11, 15, 12,
		10, 14, 11,
		8, 11, 12,
		9, 8, 13,
		8, 12, 13,
		10, 9, 14,
		9, 13, 14
	};

	vec3 cam_pos = {2.0f, 2.0f, 2.0f};
	vec3 cam_target = {0.0f, 0.0f, 0.0f};
	vec3 cam_up = {0.0f, 0.0f, 1.0f};

	lvParam param = {};
	param.pWindow = window;
	param.validationLayersCount = 1;
	param.ppValidationLayers = layers;
	param.instanceExtensionsCount = 3;
	param.ppInstanceExtensions = instanceExtensions;
	param.deviceExtensionsCount = 1;
	param.ppDeviceExtensions = deviceExtensions;
	param.imageCount = 4;
	param.pVertices = vertices;
	param.vertices_size = 16;
	param.pIndices = indices;
	param.indices_size = 72;

	param.pCam_pos = &cam_pos;
	param.pCam_target = &cam_target;
	param.pCam_up = &cam_up;
	param.fov = 90.0f;
	param.near = 0.001f;
	param.far = 10000.0f;



	void *vklib = dlopen("./liblava.so", RTLD_LAZY);
	const PFN_initVulkan pfn_initVulkan = dlsym(vklib, "initVulkan");
	const PFN_drawFrame pfn_drawFrame = dlsym(vklib, "drawFrame");
	const PFN_lvTerminate pfn_lvTerminate = dlsym(vklib, "lvTerminate");

	lvData lvdata = {};
	LoaderTable loaderTable = {};
	pfn_initVulkan(&param, &lvdata, &loaderTable);

	char ch = ' ';
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		pfn_drawFrame(&lvdata, &loaderTable, &param);

		int key_state = 0;

		key_state = glfwGetKey(window, GLFW_KEY_ESCAPE);
		if (key_state == GLFW_PRESS)
		{
			break;
		}

		key_state = glfwGetKey(window, GLFW_KEY_A);
		if (key_state == GLFW_PRESS)
		{
			param.pCam_pos->y -= 0.1f;
			param.pCam_target->y -= 0.1f;
		}

		key_state = glfwGetKey(window, GLFW_KEY_S);
		if (key_state == GLFW_PRESS)
		{
			param.pCam_pos->x += 0.1f;
			param.pCam_target->x += 0.1f;
		}

		key_state = glfwGetKey(window, GLFW_KEY_W);
		if (key_state == GLFW_PRESS)
		{
			param.pCam_pos->x -= 0.1f;
			param.pCam_target->x -= 0.1f;
		}

		key_state = glfwGetKey(window, GLFW_KEY_D);
		if (key_state == GLFW_PRESS)
		{
			param.pCam_pos->y += 0.1f;
			param.pCam_target->y += 0.1f;
		}

		key_state = glfwGetKey(window, GLFW_KEY_E);
		if (key_state == GLFW_PRESS)
		{
			param.pCam_pos->z += 0.1f;
			param.pCam_target->z += 0.1f;
		}

		key_state = glfwGetKey(window, GLFW_KEY_Q);
		if (key_state == GLFW_PRESS)
		{
			param.pCam_pos->z -= 0.1f;
			param.pCam_target->z -= 0.1f;
		}

	//	printf("mainLoop\n");
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
