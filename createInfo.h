#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "volk.h"

namespace py = pybind11;

#ifndef CREATEINFO_H
#define CREATEINFO_H


class ApplicationInfo
{
public:
	ApplicationInfo();
	ApplicationInfo(std::string _appName, std::string _engineName, uint32_t _appVersion, uint32_t _engineVersion, uint32_t _apiVersion);
	~ApplicationInfo();

	void getVKStruct(VkApplicationInfo *info);

	uint32_t appVersion = 0;
	uint32_t engineVersion = 0;
	uint32_t apiVersion = 0;
	std::string appName = "";
	std::string engineName = "";
};


class InstanceCreateInfo
{
public:
	InstanceCreateInfo();
	InstanceCreateInfo(ApplicationInfo &appInfo, std::vector<std::string> &layerNames, std::vector<std::string> &extentsionNames);
	~InstanceCreateInfo();

	void setLayerNames(std::vector<std::string> &names);
	std::vector<std::string> getLayerNames() { return layerNames; };
	void setExtensionNames(std::vector<std::string> &names);
	std::vector<std::string> getExtensionNames() { return extensionNames; };

	void getVKStruct(VkInstanceCreateInfo *info);

	ApplicationInfo appInfo;
	std::vector<std::string> layerNames = {};
	std::vector<std::string> extensionNames = {};
	std::vector<const char*> lnames = {};
	std::vector<const char*> enames = {};
};



//static VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsUserCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);


class DebugUtilsMessengerCreateInfoEXT
{
public:
	DebugUtilsMessengerCreateInfoEXT();
	~DebugUtilsMessengerCreateInfoEXT();

	//static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

	void getVKStruct(VkDebugUtilsMessengerCreateInfoEXT *info);

	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity;
	VkDebugUtilsMessageTypeFlagsEXT messageTypes;
	
	py::function pycallback;
};



#endif // !CREATEINFO_H
