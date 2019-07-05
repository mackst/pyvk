#pragma once

//#if defined(_WIN32)
//
//#define VK_USE_PLATFORM_WIN32_KHR
//
//#endif

#include <vector>
#include <string>

#include "createInfo.h"
#include "image.h"
#include "pipeline.h"
#include "cmdBuffers.h"


namespace py = pybind11;


class SurfaceKHR;
class Queue;
class SwapchainKHR;


#ifndef DEVICE_H
#define DEVICE_H


class PhysicalDevice
{
public:
	PhysicalDevice();
	PhysicalDevice(VkInstance &instance, VkPhysicalDevice &device);
	~PhysicalDevice();

	bool isValid();

	std::string toString();

	VkPhysicalDeviceProperties getProperties();
	VkPhysicalDeviceProperties2 getProperties2(VkPhysicalDeviceProperties2* properties2 = nullptr);
	std::vector<VkLayerProperties> layerProperties();
	std::vector<VkExtensionProperties> extensionProperties(const char* layerName = nullptr);
	std::vector<VkQueueFamilyProperties> getQueueFamilyProperties();
	VkBool32 getSurfaceSupportKHR(SurfaceKHR &surface, uint32_t queueFamilyIndex);
	VkSurfaceCapabilitiesKHR getSurfaceCapabilitiesKHR(SurfaceKHR &surface);
	std::vector<VkSurfaceFormatKHR> getSurfaceFormatsKHR(SurfaceKHR &surface);
	std::vector<VkPresentModeKHR> getSurfacePresentModeKHR(SurfaceKHR &surface);

	VkInstance _instance;
	VkPhysicalDevice vkHandle = VK_NULL_HANDLE;

};



class Device
{
public:
	Device(PhysicalDevice &physicalDevice, DeviceCreateInfo &createInfo);
	~Device();

	bool create(DeviceCreateInfo &createInfo);
	void destroy();

	bool isValid();
	Queue* getQueue(uint32_t queueFamilyIndex, uint32_t queueIndex);
	SwapchainKHR* createSwapchainKHR(SwapchainCreateInfoKHR &createInfo);
	py::list getSwapchainImagesKHR(SwapchainKHR &swapchain);
	ImageView* createImageView(ImageViewCreateInfo &creatInfo);
	ShaderModule* createShaderModule(const std::string &filename);
	PipelineLayout* createPipelineLayout(PipelineLayoutCreateInfo &createInfo);
	RenderPass* createRenderPass(RenderPassCreateInfo &createInfo);
	std::vector<Pipeline*> createGraphicsPipelines(PipelineCache &cache, std::vector<GraphicsPipelineCreateInfo*> &createInfos);
	std::vector<Pipeline*> createComputePipelines(PipelineCache &cache, std::vector<ComputePipelineCreateInfo*> &infos);
	Framebuffer* createFramebuffer(FramebufferCreateInfo &createInfo);
	CommandPool* createCommandPool(VkCommandPoolCreateInfo &createInfo);
	std::vector<CommandBuffer*> allocateCommandBuffers(CommandBufferAllocateInfo &createInfo);
	Semaphore* createSemaphore(VkSemaphoreCreateInfo *createInfo);
	Fence* createFence(VkFenceCreateInfo *createInfo);
	bool waitForFences(std::vector<Fence*> &fences, VkBool32 waitAll, uint64_t timeout);
	bool resetFences(std::vector<Fence*> &fences);

	Device* waitIdle();

	VkDevice vkHandle = VK_NULL_HANDLE;
	VolkDeviceTable table;

	PhysicalDevice _physicalDevice;
};


class Queue
{
public:
	Queue(Device *device, uint32_t queueFamilyIndex, uint32_t queueIndex);
	~Queue();

	Queue* submit(std::vector<SubmitInfo*> &infos, Fence *fence = nullptr);
	Queue* presentKHR(PresentInfoKHR &info);
	Queue* waitIdle();

	bool isValid();


	VkQueue vkHandle = VK_NULL_HANDLE;
	Device *_device = nullptr;
};


#endif // !DEVICE_H

