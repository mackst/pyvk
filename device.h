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


namespace py = pybind11;


class SurfaceKHR;
class DeviceQueue;
class SwapchainKHR;


#ifndef DEVICE_H
#define DEVICE_H


class PhysicalDevice
{
public:
	PhysicalDevice();
	PhysicalDevice(VkInstance &instance, VkPhysicalDevice &device);
	PhysicalDevice(PhysicalDevice& device);
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
	DeviceQueue* getQueue(uint32_t queueFamilyIndex, uint32_t queueIndex);
	SwapchainKHR* createSwapchainKHR(py::dict createInfo);
	py::list getSwapchainImagesKHR(SwapchainKHR &swapchain);
	ImageView* createImageView(py::dict createInfo);
	ShaderModule* createShaderModule(const std::string &filename);
	PipelineLayout* createPipelineLayout(py::dict createInfo);
	//PipelineLayout* createPipelineLayout(PipelineLayoutCreateInfo &createInfo);
	RenderPass* createRenderPass(RenderPassCreateInfo &createInfo);
	//std::vector<Pipeline> createGraphicsPipelines(PipelineCache &cache, std::vector<GraphicsPipelineCreateInfo*> createInfos);
	std::vector<Pipeline> createGraphicsPipelines(PipelineCache &cache, py::list createInfos);


	VkDevice vkHandle = VK_NULL_HANDLE;
	VolkDeviceTable table;

	PhysicalDevice _physicalDevice;
};


class DeviceQueue
{
public:
	DeviceQueue(Device *device, uint32_t queueFamilyIndex, uint32_t queueIndex);
	~DeviceQueue();

	bool isValid();


	VkQueue vkHandle = VK_NULL_HANDLE;
};


#endif // !DEVICE_H

