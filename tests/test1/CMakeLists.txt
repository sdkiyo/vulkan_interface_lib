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
	${P}createInstance.c		${P}lvRun.c
	${P}debugUtilsMessenger.c
	${P}getShaderCode.c		${P}createShaderModule.c
	${P}createSurface.c		${P}pickPhysicalDevice.c
	${P}createLogicalDevice.c	${P}createSwapchain.c
	${P}createImageViews.c		${P}createRenderPass.c
	${P}createFramebuffers.c	${P}createGraphicsPipeline.c
	${P}createCommandPool.c		${P}createCommandBuffer.c
	${P}createSyncObjects.c		${P}recordCommandBuffer.c
	${P}drawFrame.c			${P}lvTerminate.c
)
#target_link_libraries(lava PUBLIC Vulkan::Vulkan)
target_link_libraries(lava PUBLIC glfw)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE lava)
