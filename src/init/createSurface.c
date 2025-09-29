#include "pre.h"

int createSurface(GLFWwindow *const pWindow, const VkInstance *const pInstance, VkSurfaceKHR *const pSurface)
{
	void *vklib = dlopen("/usr/lib64/libglfw.so", RTLD_LAZY);
	const PFN_glfwCreateWindowSurface pfn_glfwCreateWindowSurface = dlsym(vklib, "glfwCreateWindowSurface");

	if (pfn_glfwCreateWindowSurface(*pInstance, pWindow, nullptr, pSurface) != VK_SUCCESS)
	{
		fprintf(stderr, RED "%s(), line %d, 'failed to create surface'" RESET_COLOR "\n", __func__, __LINE__);
		return -1;
	}

	return 0;
}
