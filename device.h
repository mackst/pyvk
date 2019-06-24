#pragma once

//#if defined(_WIN32)
//
//#define VK_USE_PLATFORM_WIN32_KHR
//
//#endif

#include <vector>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#include "volk.h"

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
	Device(PhysicalDevice &physicalDevice, py::dict createInfo);
	~Device();

	bool create(py::dict createInfo);
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

protected:
	PFN_vkCreateDevice _vkCreateDevice = nullptr;
	PFN_vkDestroyDevice _vkDestroyDevice = nullptr;
	PFN_vkGetDeviceQueue _vkGetDeviceQueue = nullptr;
	PFN_vkCreateImageView _vkCreateImageView = nullptr;
	PFN_vkDestroyImageView _vkDestroyImageView = nullptr;
	PFN_vkCreateGraphicsPipelines _vkCreateGraphicsPipelines = nullptr;
	PFN_vkDestroyPipeline _vkDestroyPipeline = nullptr;

private:
	PhysicalDevice _physicalDevice;

	void getFuncPointers();
};





#endif // !DEVICE_H

