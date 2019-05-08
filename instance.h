#pragma once

#ifndef INSTANCE_H
#define INSTANCE_H


//#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vulkan/vulkan.h>

#include "exception.h"
#include "utils.h"
#include "extensions.h"
#include "device.h"


namespace py = pybind11;



class Instance
{
public:
	//Instance();
	Instance(py::dict);
	~Instance();

	bool create();
	void destroy();

	DebugUtilsMessengerEXT* createDebugUtilsMessengerEXT(int messageSeverity, int messageType, py::function userCallback);
	py::list getPhysicalDevices();

	bool isValid();

	static uint32_t version();
	static py::list layerProperties();
	static py::list extensionProperties(const char* layerName = nullptr);

	
	VkInstance vkHandle = VK_NULL_HANDLE;
private:
	void getInstanceFuncPointers();

	VkInstanceCreateInfo _createInfo = {};

	PFN_vkEnumeratePhysicalDevices _vkEnumeratePhysicalDevices = VK_NULL_HANDLE;
};


#endif // !INSTANCE_H
