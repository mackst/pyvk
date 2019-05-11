#include "extensions.h"
#include "instance.h"
#include "exception.h"


py::function DebugUtilsMessengerEXT::pycallback;


DebugUtilsMessengerEXT::DebugUtilsMessengerEXT()
{
}

DebugUtilsMessengerEXT::DebugUtilsMessengerEXT(VkInstance &instance, int messageSeverity, int messageType, py::function userCallback) : _instance(instance)
{
	_vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
	_vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT");

	if (_vkCreateDebugUtilsMessengerEXT == nullptr || _vkDestroyDebugUtilsMessengerEXT == nullptr)
		throw ExtensionNotPresent("VK_EXT_debug_report not present.");


	DebugUtilsMessengerEXT::pycallback = userCallback;

	VkDebugUtilsMessengerCreateInfoEXT _createInfo = {};
	_createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	_createInfo.messageSeverity = messageSeverity;
	_createInfo.messageType = messageType;
	_createInfo.pfnUserCallback = DebugUtilsMessengerEXT::debugCallback;

	checkVKResult(_vkCreateDebugUtilsMessengerEXT(_instance, &_createInfo, nullptr, &vkHandle));
	_isValid = true;
}

DebugUtilsMessengerEXT::~DebugUtilsMessengerEXT()
{
	destroy();
}

void DebugUtilsMessengerEXT::destroy()
{
	if (vkHandle != VK_NULL_HANDLE)
	{
		_vkDestroyDebugUtilsMessengerEXT(_instance, vkHandle, nullptr);
		py::print("DebugUtilsMessengerEXT destroyed.");
		DebugUtilsMessengerEXT::pycallback = {};
		_instance = VK_NULL_HANDLE;
		vkHandle = VK_NULL_HANDLE;
		_isValid = false;
	}
}

bool DebugUtilsMessengerEXT::isValid()
{
	return _isValid;
}


VKAPI_ATTR VkBool32 VKAPI_CALL DebugUtilsMessengerEXT::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData, void * pUserData)
{
	py::dict data;
	//data["cmdBufLabelCount"] = pCallbackData->cmdBufLabelCount;
	data["message"] = pCallbackData->pMessage;
	data["messageIdName"] = pCallbackData->pMessageIdName;

	DebugUtilsMessengerEXT::pycallback(messageSeverity, messageType, data);
	return VK_FALSE;
}

SurfaceKHR::SurfaceKHR()
{
}

SurfaceKHR::SurfaceKHR(VkInstance & instance, py::dict createInfo) : _instance(instance)
{
	_createWin32Surface = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(_instance, "vkCreateWin32SurfaceKHR");
	_destroySurfaceKHR = (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(_instance, "vkDestroySurfaceKHR");

	create(createInfo);
}

SurfaceKHR::~SurfaceKHR()
{
	destroy();
}

bool SurfaceKHR::create(py::dict createInfo)
{

#if defined(_WIN32)
	if (_createWin32Surface == nullptr)
		throw ExtensionNotPresent("VK_KHR_win32_surface not present.");

	HWND winId = (HWND)createInfo["winId"].cast<LONG>();
	HINSTANCE hinstance = (HINSTANCE)GetWindowLongA(winId, -6);

	VkWin32SurfaceCreateInfoKHR _createInfo = {};
	_createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	_createInfo.hinstance = hinstance;
	_createInfo.hwnd = winId;

	checkVKResult(_createWin32Surface(_instance, &_createInfo, nullptr, &vkHandle));

#else
	throw std::runtime_error("Unsupported platform.");
#endif


	return false;
}

void SurfaceKHR::destroy()
{
	if (isValid())
	{
		_destroySurfaceKHR(_instance, vkHandle, nullptr);
		_instance = VK_NULL_HANDLE;
		vkHandle = VK_NULL_HANDLE;
	}
}

bool SurfaceKHR::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

SwapchainKHR::SwapchainKHR()
{
}

SwapchainKHR::~SwapchainKHR()
{
}
