#pragma once

//#if defined(_WIN32)
//
//#define VK_USE_PLATFORM_WIN32_KHR
//
//#endif


#include "createInfo.h"



namespace py = pybind11;


class Device;


#ifndef EXTENSIONS_H
#define EXTENSIONS_H




class DebugUtilsMessengerEXT
{
public:
	DebugUtilsMessengerEXT();
	DebugUtilsMessengerEXT(VkInstance &instance, DebugUtilsMessengerCreateInfoEXT &info);
	~DebugUtilsMessengerEXT();

	void destroy();

	bool isValid();

private:
	VkInstance _instance = VK_NULL_HANDLE;

	VkDebugUtilsMessengerEXT vkHandle = VK_NULL_HANDLE;
	DebugUtilsMessengerCreateInfoEXT _createInfo;

	bool _isValid = false;
};


class SurfaceKHR
{
public:
	SurfaceKHR();
	SurfaceKHR(VkInstance &instance, long winId);
	~SurfaceKHR();

	bool create(long winId);
	void destroy();

	bool isValid();

	VkSurfaceKHR vkHandle = VK_NULL_HANDLE;
private:
	VkInstance _instance = VK_NULL_HANDLE;
};


class SwapchainKHR
{
public:
	SwapchainKHR();
	SwapchainKHR(Device *device, SwapchainCreateInfoKHR &createInfo);
	~SwapchainKHR();

	bool isValid();

	py::list getImagesKHR();

	VkSwapchainKHR vkHandle = VK_NULL_HANDLE;
private:
	Device *_device = nullptr;
};





#endif // !EXTENSIONS_H

