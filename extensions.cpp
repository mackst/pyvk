#include "extensions.h"
#include "instance.h"
#include "exception.h"


py::function DebugUtilsMessengerEXT::pycallback;


DebugUtilsMessengerEXT::DebugUtilsMessengerEXT()
{
}

DebugUtilsMessengerEXT::DebugUtilsMessengerEXT(VkInstance &instance, int messageSeverity, int messageType, py::function userCallback)
{
	_instance = instance;
	_vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
	_vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT");

	if (_vkCreateDebugUtilsMessengerEXT == nullptr || _vkDestroyDebugUtilsMessengerEXT == nullptr)
		throw ExtensionNotPresent("VK_EXT_debug_report not present.");


	DebugUtilsMessengerEXT::pycallback = userCallback;

	_createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	_createInfo.messageSeverity = messageSeverity;
	_createInfo.messageType = messageType;
	_createInfo.pfnUserCallback = DebugUtilsMessengerEXT::debugCallback;

	//auto messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

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
		_isValid = false;
		py::print("DebugUtilsMessengerEXT destroyed.");
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
