#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vulkan/vulkan.h>


namespace py = pybind11;


#ifndef EXTENSIONS_H
#define EXTENSIONS_H



class DebugUtilsMessengerEXT
{
public:
	DebugUtilsMessengerEXT();
	DebugUtilsMessengerEXT(VkInstance &instance, int messageSeverity, int messageType, py::function userCallback);
	~DebugUtilsMessengerEXT();

	void destroy();

	bool isValid();

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);


private:
	VkInstance _instance;

	VkDebugUtilsMessengerEXT vkHandle = VK_NULL_HANDLE;
	VkDebugUtilsMessengerCreateInfoEXT _createInfo = {};

	bool _isValid = false;

	// python function callback
	static py::function pycallback;

	// function pointer
	PFN_vkCreateDebugUtilsMessengerEXT _vkCreateDebugUtilsMessengerEXT = nullptr;
	PFN_vkDestroyDebugUtilsMessengerEXT _vkDestroyDebugUtilsMessengerEXT = nullptr;
};




#endif // !EXTENSIONS_H

