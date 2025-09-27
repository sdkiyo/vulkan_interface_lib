#include <vk.h>

int updateUniformBuffer(uint32_t currentImage, void** uniformBuffersMapped, const VkExtent2D *const swapchainExtent)
{

	f += 0.0001f;
	float time = 0.3;

	UniformBufferObject ubo = {};// uBlock origin

	vec3 axis = {0.0f, 0.0f, 1.0f};
	rotate(ubo.model, f * 90.0f, &axis);

	vec3 cam_pos = {2.0f, 2.0f, 2.0f};
	vec3 cam_target = {0.0f, 0.0f, 0.0f};
	vec3 cam_up = {0.0f, 0.0f, 1.0f};

	lookcatRH(ubo.view, &cam_pos, &cam_target, &cam_up);

	perspective(ubo.proj, 45.0f, swapchainExtent->width / (float)swapchainExtent->height, 0.1f, 10.0f);
//	printf("w: %d\n", swapchainExtent->width);
//	printf("h: %d\n", swapchainExtent->height);
//
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			printf("proj[%d][%d]: %f\n", i, j, ubo.proj[i][j]);
//		}
//	}
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			printf("view[%d][%d]: %f\n", i, j, ubo.view[i][j]);
//		}
//	}
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			printf("model[%d][%d]: %f\n", i, j, ubo.model[i][j]);
//		}
//	}

	ubo.proj[1][1] *= -1;

	memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));

	return 0;
}
