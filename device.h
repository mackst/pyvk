#pragma once

#if defined(_WIN32)

#define VK_USE_PLATFORM_WIN32_KHR

#endif

#include <vector>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vulkan/vulkan.h>

#include "image.h"

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

	py::dict getProperties();
	py::dict getProperties2();
	py::list layerProperties();
	py::list extensionProperties(const char* layerName = nullptr);
	py::list getQueueFamilyProperties();
	VkBool32 getSurfaceSupportKHR(SurfaceKHR &surface, uint32_t queueFamilyIndex);
	VkSurfaceCapabilitiesKHR getSurfaceCapabilitiesKHR(SurfaceKHR &surface);
	std::vector<VkSurfaceFormatKHR> getSurfaceFormatsKHR(SurfaceKHR &surface);
	std::vector<VkPresentModeKHR> getSurfacePresentModeKHR(SurfaceKHR &surface);

	VkInstance _instance;
	VkPhysicalDevice vkHandle = VK_NULL_HANDLE;

private:
	PFN_vkEnumerateDeviceExtensionProperties _vkEnumerateDeviceExtensionProperties = nullptr;
	PFN_vkEnumerateDeviceLayerProperties _vkEnumerateDeviceLayerProperties = nullptr;
	PFN_vkGetPhysicalDeviceProperties _vkGetPhysicalDeviceProperties = nullptr;
	PFN_vkGetPhysicalDeviceProperties2 _vkGetPhysicalDeviceProperties2 = nullptr;
	PFN_vkGetPhysicalDeviceQueueFamilyProperties _vkGetPhysicalDeviceQueueFamilyProperties = nullptr;
	PFN_vkGetPhysicalDeviceSurfaceSupportKHR _vkGetPhysicalDeviceSurfaceSupportKHR = nullptr;
	PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR _vkGetPhysicalDeviceSurfaceCapabilitiesKHR = nullptr;
	PFN_vkGetPhysicalDeviceSurfaceFormatsKHR _vkGetPhysicalDeviceSurfaceFormatsKHR = nullptr;
	PFN_vkGetPhysicalDeviceSurfacePresentModesKHR _vkGetPhysicalDeviceSurfacePresentModesKHR = nullptr;
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

	VkDevice vkHandle = VK_NULL_HANDLE;

protected:
	PFN_vkCreateDevice _vkCreateDevice = nullptr;
	PFN_vkDestroyDevice _vkDestroyDevice = nullptr;
	PFN_vkGetDeviceQueue _vkGetDeviceQueue = nullptr;
	PFN_vkCreateImageView _vkCreateImageView = nullptr;
	PFN_vkDestroyImageView _vkDestroyImageView = nullptr;

private:
	PhysicalDevice _physicalDevice;

	void getFuncPointers();
};





#endif // !DEVICE_H

