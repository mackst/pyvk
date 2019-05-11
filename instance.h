#pragma once

#if defined(_WIN32)

#define VK_USE_PLATFORM_WIN32_KHR

#endif




//#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vulkan/vulkan.h>

#include "exception.h"
#include "utils.h"
#include "extensions.h"
#include "device.h"


namespace py = pybind11;


#ifndef INSTANCE_H
#define INSTANCE_H


class Instance
{
public:
	//Instance();
	Instance(py::dict);
	~Instance();

	bool create();
	void destroy();

	DebugUtilsMessengerEXT* createDebugUtilsMessengerEXT(int messageSeverity, int messageType, py::function userCallback);
	SurfaceKHR* createSurface(py::dict createInfo);
	py::list getPhysicalDevices();

	bool isValid();

	static uint32_t version();
	static py::list layerProperties();
	static py::list extensionProperties(const char* layerName = nullptr);

	
	VkInstance vkHandle = VK_NULL_HANDLE;
private:
	void getInstanceFuncPointers();

	VkInstanceCreateInfo _createInfo = {};
	DebugUtilsMessengerEXT *_debugMessenger = nullptr;
	SurfaceKHR *_surfaceKHR = nullptr;

	PFN_vkEnumeratePhysicalDevices _vkEnumeratePhysicalDevices = VK_NULL_HANDLE;
};


#endif // !INSTANCE_H
