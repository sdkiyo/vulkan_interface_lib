#include "pre.h"

int lvCreateSurface(GLFWwindow *const window, const VkInstance *const instance, VkSurfaceKHR *const surface)
{
	void *vklib = dlopen("/usr/lib64/libglfw.so", RTLD_LAZY);
	const PFN_glfwCreateWindowSurface pfn_glfwCreateWindowSurface = dlsym(vklib, "glfwCreateWindowSurface");

	if (pfn_glfwCreateWindowSurface(*instance, window, nullptr, surface) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create surface'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	return 0;
}
