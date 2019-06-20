#include "createInfo.h"
#include "utils.h"

ApplicationInfo::ApplicationInfo()
{
}

ApplicationInfo::ApplicationInfo(std::string _appName, std::string _engineName, uint32_t _appVersion, uint32_t _engineVersion, uint32_t _apiVersion):
	appName(_appName), engineName(_engineName), appVersion(_appVersion), engineVersion(_engineVersion), apiVersion(_apiVersion)
{
}

ApplicationInfo::~ApplicationInfo()
{
}

void ApplicationInfo::getVKStruct(VkApplicationInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info->apiVersion = apiVersion;
	info->applicationVersion = appVersion;
	info->engineVersion = engineVersion;
	info->pApplicationName = appName.c_str();
	info->pEngineName = engineName.c_str();
}

InstanceCreateInfo::InstanceCreateInfo()
{
}

InstanceCreateInfo::InstanceCreateInfo(ApplicationInfo & _appInfo, std::vector<std::string>& _layerNames, std::vector<std::string>& _extentsionNames):
	appInfo(_appInfo)
{
	setLayerNames(_layerNames);
	setExtensionNames(_extentsionNames);
}

InstanceCreateInfo::~InstanceCreateInfo()
{
}

void InstanceCreateInfo::setLayerNames(std::vector<std::string>& names)
{
	layerNames = names;
	lnames = vecStrToVecChar(layerNames);
}

void InstanceCreateInfo::setExtensionNames(std::vector<std::string>& names)
{
	extensionNames = names;
	enames = vecStrToVecChar(extensionNames);
}

void InstanceCreateInfo::getVKStruct(VkInstanceCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

	info->enabledLayerCount = static_cast<uint32_t>(layerNames.size());
	info->enabledExtensionCount = static_cast<uint32_t>(extensionNames.size());

	if (info->enabledLayerCount > 0)
		info->ppEnabledLayerNames = lnames.data();
	if (info->enabledExtensionCount > 0)
		info->ppEnabledExtensionNames = enames.data();
}


//py::function DebugUtilsMessengerCreateInfoEXT::pycallback = {};

DebugUtilsMessengerCreateInfoEXT::DebugUtilsMessengerCreateInfoEXT()
{
}

DebugUtilsMessengerCreateInfoEXT::~DebugUtilsMessengerCreateInfoEXT()
{
	//DebugUtilsMessengerCreateInfoEXT::pycallback = {};
	pycallback = {};
}

//VKAPI_ATTR VkBool32 VKAPI_CALL DebugUtilsMessengerCreateInfoEXT::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData, void * pUserData)
//{
//	py::dict data;
//	//data["cmdBufLabelCount"] = pCallbackData->cmdBufLabelCount;
//	data["message"] = pCallbackData->pMessage;
//	data["messageIdName"] = pCallbackData->pMessageIdName;
//
//	DebugUtilsMessengerCreateInfoEXT::pycallback(messageSeverity, messageType, data);
//	return VK_FALSE;
//}

void DebugUtilsMessengerCreateInfoEXT::getVKStruct(VkDebugUtilsMessengerCreateInfoEXT * info)
{
	auto dcallback = [&](VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData, void * pUserData) -> VKAPI_ATTR VkBool32 VKAPI_CALL {
		py::dict data;
		//data["cmdBufLabelCount"] = pCallbackData->cmdBufLabelCount;
		data["message"] = pCallbackData->pMessage;
		data["messageIdName"] = pCallbackData->pMessageIdName;

		pycallback(messageSeverity, messageType, data);
		return VK_FALSE;
	};

	info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	info->messageSeverity = messageSeverity;
	info->messageType = messageTypes;
	//info->pfnUserCallback = &debugCallback;
	info->pfnUserCallback = &dcallback;
}
