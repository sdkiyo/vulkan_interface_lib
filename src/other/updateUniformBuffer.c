#include <vk.h>

static float f = 0.0f;

int updateUniformBuffer(uint32_t currentImage, void** pUniformBuffersMapped, const VkExtent2D *const pSwapchainExtent, const vec3 *const pCam_pos, const vec3 *const pCam_target, const vec3 *const pCam_up, const float fov, const float near, const float far)
{
	f += 0.01f;

	UniformBufferObject ubo = {};// uBlock origin
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ubo.proj[i][j] = 0;
			ubo.view[i][j] = 0;
			ubo.model[i][j] = 0;
		}
	}

	vec3 axis = {0.3f, 0.6f, 0.9f};
	rotate(ubo.model, 0.0f, &axis);

	lookAt(ubo.view, pCam_pos, pCam_target, pCam_up);
	perspective(ubo.proj, fov, pSwapchainExtent->width / (float)pSwapchainExtent->height, near, far);

	ubo.proj[1][1] *= -1;

	memcpy(pUniformBuffersMapped[currentImage], &ubo, sizeof(ubo));

	return 0;
}
