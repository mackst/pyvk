#pragma once

//#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "volk.h"
#include "exception.h"
#include "utils.h"
#include "extensions.h"
#include "device.h"
//#include "createInfo.h"


namespace py = pybind11;


#ifndef INSTANCE_H
#define INSTANCE_H


void initvk();


class Instance
{
public:
	//Instance();
	//Instance(py::dict);
	Instance(InstanceCreateInfo &info);
	~Instance();

	//bool create();
	bool create(InstanceCreateInfo &);
	//bool create(py::dict);
	void destroy();

	DebugUtilsMessengerEXT* createDebugUtilsMessengerEXT(DebugUtilsMessengerCreateInfoEXT &info);
	SurfaceKHR* createWin32Surface(long winId);
	std::vector<PhysicalDevice> getPhysicalDevices();

	bool isValid();

	static uint32_t version();
	static std::vector<VkLayerProperties> layerProperties();
	static std::vector<VkExtensionProperties> extensionProperties(const char* layerName = nullptr);

	
	VkInstance vkHandle = VK_NULL_HANDLE;
};


#endif // !INSTANCE_H
