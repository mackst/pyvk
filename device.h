#pragma once
#include <vector>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vulkan/vulkan.h>

namespace py = pybind11;


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
	py::list getQueueFamilyProperties();

	VkInstance _instance;
	VkPhysicalDevice vkHandle = VK_NULL_HANDLE;

private:
	PFN_vkGetPhysicalDeviceProperties _vkGetPhysicalDeviceProperties = nullptr;
	PFN_vkGetPhysicalDeviceProperties2 _vkGetPhysicalDeviceProperties2 = nullptr;
	PFN_vkGetPhysicalDeviceQueueFamilyProperties _vkGetPhysicalDeviceQueueFamilyProperties = nullptr;

};



class Device
{
public:
	Device(PhysicalDevice &physicalDevice, py::dict createInfo);
	~Device();

	bool create(py::dict createInfo);
	void destroy();
	bool isValid();

	VkDevice vkHandle = VK_NULL_HANDLE;
private:
	PhysicalDevice _physicalDevice;


	PFN_vkCreateDevice _vkCreateDevice = nullptr;
	PFN_vkDestroyDevice _vkDestroyDevice = nullptr;
	PFN_vkGetDeviceQueue _vkGetDeviceQueue = nullptr;

	void getInstanceFuncPointers();
};


#endif // !DEVICE_H

