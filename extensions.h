#pragma once

#if defined(_WIN32)

#define VK_USE_PLATFORM_WIN32_KHR

#endif


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
	VkInstance _instance = VK_NULL_HANDLE;

	VkDebugUtilsMessengerEXT vkHandle = VK_NULL_HANDLE;
	//VkDebugUtilsMessengerCreateInfoEXT _createInfo = {};

	bool _isValid = false;

	// python function callback
	static py::function pycallback;

	// function pointer
	PFN_vkCreateDebugUtilsMessengerEXT _vkCreateDebugUtilsMessengerEXT = nullptr;
	PFN_vkDestroyDebugUtilsMessengerEXT _vkDestroyDebugUtilsMessengerEXT = nullptr;
};


class SurfaceKHR
{
public:
	SurfaceKHR();
	SurfaceKHR(VkInstance &instance, py::dict createInfo);
	~SurfaceKHR();

	bool create(py::dict createInfo);
	void destroy();

	bool isValid();

	VkSurfaceKHR vkHandle = VK_NULL_HANDLE;
private:
	VkInstance _instance = VK_NULL_HANDLE;

	//bool _isValid = false;

	// function pointer
	PFN_vkCreateWin32SurfaceKHR _createWin32Surface = nullptr;
	PFN_vkDestroySurfaceKHR _destroySurfaceKHR = nullptr;
};




#endif // !EXTENSIONS_H

