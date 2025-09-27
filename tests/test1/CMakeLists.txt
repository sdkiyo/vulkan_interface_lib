cmake_minimum_required(VERSION 3.31.7)

project( test2
	LANGUAGES C )

set(CMAKE_C_STANDARD 23)

#----------TEMPORARY----------#
#find_package(Vulkan REQUIRED)
find_package(glfw3 3.4 REQUIRED)
#----------TEMPORARY-------------#

set(P ../../src/)
add_library( lava SHARED
	${P}init/createInstance.c		${P}lvInitVulkan.c
	${P}init/debugUtilsMessenger.c		${P}init/createSurface.c
	${P}init/pickPhysicalDevice.c		${P}init/createLogicalDevice.c
	${P}swapchain/createSwapchain.c		${P}swapchain/createImageViews.c
	${P}swapchain/createFramebuffers.c	${P}render_setup/createGraphicsPipeline.c
	${P}render_setup/createRenderPass.c
	${P}renderer/createCommandPool.c	${P}renderer/createCommandBuffer.c
	${P}renderer/createSyncObjects.c	${P}renderer/recordCommandBuffer.c
	${P}renderer/drawFrame.c
	${P}vertex/getDescription.c		${P}vertex/createVertexBuffer.c
	${P}vertex/createIndexBuffer.c		${P}vertex/createBuffer.c
	${P}vertex/copyBuffer.c
	${P}lvTerminate.c			${P}funcLoader.c
	${P}shaders/getShaderCode.c		${P}shaders/createShaderModule.c
	${P}createDescriptorSetLayout.c		${P}createUniformBuffers.c
	${P}updateUniformBuffer.c		${P}createDescriptorPool.c
	${P}createDescriptorSets.c
)
target_include_directories(lava PUBLIC ../../libs/test_math/)
target_include_directories(lava PUBLIC ../../include/)

add_executable(${PROJECT_NAME} main.c)
target_include_directories(${PROJECT_NAME} PRIVATE ../../libs/test_math/)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw m)
