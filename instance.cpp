#include "instance.h"




static VKAPI_ATTR VkBool32 VKAPI_CALL instance_debug_callback(
	VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
	VkDebugUtilsMessageTypeFlagsEXT message_type,
	const VkDebugUtilsMessengerCallbackDataEXT* message_data,
	void* usrdata
) {
	if (message_severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		throw std::runtime_error(message_data->pMessage);
	}
	else
	{
		std::cout << std::endl << message_data->pMessage << std::endl;
	}

	return VK_FALSE;
}



//Instance::Instance()
//{
//}

//Instance::Instance(py::dict createInfo)
//{
//	py::dict appInfoDict = createInfo["applicationInfo"];
//
//	std::vector<std::string> enabledLayerNamesList = createInfo["enabledLayerNames"].cast<std::vector<std::string>>();
//	std::vector<const char*> enabledLayerNames = vecStrToVecChar(enabledLayerNamesList);
//
//	std::vector<std::string> enabledExtensionNamesList = createInfo["enabledExtensionNames"].cast<std::vector<std::string>>();
//	std::vector<const char*> enabledExtensionNames = vecStrToVecChar(enabledExtensionNamesList);
//	
//	/*
//	auto testList = createInfo["enabledExtensionNames"].cast<py::list>();
//	std::vector<std::string> testVec = createInfo["enabledExtensionNames"].cast<std::vector<std::string>>();
//
//	for (int i=0; i < enabledExtensionNames.size(); i++)
//	{
//		//py::print(enabledExtensionNames[i]);
//		std::cout << enabledExtensionNames[i] << std::endl;
//		py::print(testVec[i]);
//		py::print(testList[i]);
//	}*/
//
//	std::string appName(appInfoDict["applicationName"].cast<py::str>());
//	std::string engineName(appInfoDict["engineName"].cast<py::str>());
//
//	VkApplicationInfo _appInfo = {};
//	_appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//	_appInfo.pApplicationName = appName.c_str();
//	_appInfo.applicationVersion = appInfoDict["applicationVersion"].cast<py::int_>();
//	_appInfo.pEngineName = engineName.c_str();
//	_appInfo.engineVersion = appInfoDict["engineVersion"].cast<py::int_>();
//	_appInfo.apiVersion = appInfoDict["apiVersion"].cast<py::int_>();
//
//	//_createInfo = {};
//	_createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//	_createInfo.pApplicationInfo = &_appInfo;
//
//	uint32_t enabledLayerCount = static_cast<uint32_t>(enabledLayerNames.size());
//	if (enabledLayerCount > 0)
//	{
//		_createInfo.enabledLayerCount = enabledLayerCount;
//		_createInfo.ppEnabledLayerNames = enabledLayerNames.data();
//	}
//	else
//	{
//		_createInfo.enabledLayerCount = 0;
//	}
//
//	uint32_t enabledExtensionCount = static_cast<uint32_t>(enabledExtensionNames.size());
//	if (enabledExtensionCount > 0)
//	{
//		_createInfo.enabledExtensionCount = enabledExtensionCount;
//		_createInfo.ppEnabledExtensionNames = enabledExtensionNames.data();
//	}
//	else
//	{
//		_createInfo.enabledExtensionCount = 0;
//	}
//
//	create();
//}

Instance::Instance(InstanceCreateInfo &info)
{
	if (vkGetInstanceProcAddr == nullptr)
		initvk();

	create(info);
}

Instance::~Instance()
{
	destroy();
}

//bool Instance::create(py::dict createInfo)
//{
//	py::dict appInfoDict = createInfo["applicationInfo"];
//
//	std::vector<std::string> enabledLayerNamesList = createInfo["enabledLayerNames"].cast<std::vector<std::string>>();
//	std::vector<const char*> enabledLayerNames = vecStrToVecChar(enabledLayerNamesList);
//
//	std::vector<std::string> enabledExtensionNamesList = createInfo["enabledExtensionNames"].cast<std::vector<std::string>>();
//	std::vector<const char*> enabledExtensionNames = vecStrToVecChar(enabledExtensionNamesList);
//
//	/*
//	auto testList = createInfo["enabledExtensionNames"].cast<py::list>();
//	std::vector<std::string> testVec = createInfo["enabledExtensionNames"].cast<std::vector<std::string>>();
//
//	for (int i=0; i < enabledExtensionNames.size(); i++)
//	{
//		//py::print(enabledExtensionNames[i]);
//		std::cout << enabledExtensionNames[i] << std::endl;
//		py::print(testVec[i]);
//		py::print(testList[i]);
//	}*/
//
//	std::string appName(appInfoDict["applicationName"].cast<py::str>());
//	std::string engineName(appInfoDict["engineName"].cast<py::str>());
//
//	VkApplicationInfo _appInfo = {};
//	_appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//	_appInfo.pApplicationName = appName.c_str();
//	_appInfo.applicationVersion = appInfoDict["applicationVersion"].cast<py::int_>();
//	_appInfo.pEngineName = engineName.c_str();
//	_appInfo.engineVersion = appInfoDict["engineVersion"].cast<py::int_>();
//	_appInfo.apiVersion = appInfoDict["apiVersion"].cast<py::int_>();
//
//	//_createInfo = {};
//	_createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//	_createInfo.pApplicationInfo = &_appInfo;
//
//	uint32_t enabledLayerCount = static_cast<uint32_t>(enabledLayerNames.size());
//	if (enabledLayerCount > 0)
//	{
//		_createInfo.enabledLayerCount = enabledLayerCount;
//		_createInfo.ppEnabledLayerNames = enabledLayerNames.data();
//	}
//	else
//	{
//		_createInfo.enabledLayerCount = 0;
//	}
//
//	uint32_t enabledExtensionCount = static_cast<uint32_t>(enabledExtensionNames.size());
//	if (enabledExtensionCount > 0)
//	{
//		_createInfo.enabledExtensionCount = enabledExtensionCount;
//		_createInfo.ppEnabledExtensionNames = enabledExtensionNames.data();
//	}
//	else
//	{
//		_createInfo.enabledExtensionCount = 0;
//	}
//
//	auto func = (PFN_vkCreateInstance)vkGetInstanceProcAddr(nullptr, "vkCreateInstance");
//	if (func != nullptr)
//	{
//		checkVKResult(func(&_createInfo, nullptr, &vkHandle));
//	}
//	//else
//	//	checkVKResult(vkCreateInstance(&_createInfo, nullptr, &vkHandle));
//
//	getInstanceFuncPointers();
//
//	return true;
//}

//bool Instance::create()
//{
//	auto func = (PFN_vkCreateInstance)vkGetInstanceProcAddr(nullptr, "vkCreateInstance");
//	if (func != nullptr)
//	{
//		checkVKResult(func(&_createInfo, nullptr, &vkHandle));
//	}
//	else
//		checkVKResult(vkCreateInstance(&_createInfo, nullptr, &vkHandle));
//
//	getInstanceFuncPointers();
//
//	return true;
//}

bool Instance::create(InstanceCreateInfo &info)
{
	VkApplicationInfo appInfo = {};
	info.appInfo.getVKStruct(&appInfo);

	VkInstanceCreateInfo createInfo = {};
	info.getVKStruct(&createInfo);
	createInfo.pApplicationInfo = &appInfo;

	if (info.pNext)
	{
		VkDebugUtilsMessengerCreateInfoEXT debugInfo = {};
		info.pNext->getVKStruct(&debugInfo);
		createInfo.pNext = &debugInfo;
	}

	//VkDebugUtilsMessengerCreateInfoEXT debugInfo = {};
	//debugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	//debugInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
	//	VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
	//	VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
	//	VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	//debugInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
	//	VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
	//	VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	//debugInfo.pfnUserCallback = instance_debug_callback;
	//createInfo.pNext = &debugInfo;

	auto result = vkCreateInstance(&createInfo, nullptr, &vkHandle);
	//py::print(result);
	checkVKResult(result);
	volkLoadInstance(vkHandle);
	return true;
}


void Instance::destroy()
{		
	//if (_surfaceKHR != nullptr)
	//{
	//	_surfaceKHR->destroy();
	//	_surfaceKHR = nullptr;
	//}

	if (vkHandle == VK_NULL_HANDLE)
		return;

	//auto func = (PFN_vkDestroyInstance)vkGetInstanceProcAddr(vkHandle, "vkDestroyInstance");
	//if (func != nullptr)
	//	func(vkHandle, nullptr);
	//else
	vkDestroyInstance(vkHandle, nullptr);
	vkHandle = VK_NULL_HANDLE;
	//py::print("instance destroyed.");
}

DebugUtilsMessengerEXT* Instance::createDebugUtilsMessengerEXT(DebugUtilsMessengerCreateInfoEXT & info)
{
	return new DebugUtilsMessengerEXT(vkHandle, info);
}


//
//SurfaceKHR * Instance::createSurface(py::dict createInfo)
//{
//	_surfaceKHR = new SurfaceKHR(vkHandle, createInfo);
//	return _surfaceKHR;
//	//return new SurfaceKHR(vkHandle, createInfo);
//}
//
py::list Instance::getPhysicalDevices()
{
	py::list devices;
	
	uint32_t deviceCount;
	checkVKResult(vkEnumeratePhysicalDevices(vkHandle, &deviceCount, nullptr));

	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
	checkVKResult(vkEnumeratePhysicalDevices(vkHandle, &deviceCount, physicalDevices.data()));

	for (auto item : physicalDevices)
	{
		PhysicalDevice device(vkHandle, item);
		devices.append(device);
	}

	return devices;
}

bool Instance::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

uint32_t Instance::version()
{
	if (vkGetInstanceProcAddr == nullptr)
		initvk();

	uint32_t version;
	vkEnumerateInstanceVersion(&version);
	return version;
}

std::vector<VkLayerProperties> Instance::layerProperties()
{
	if (vkGetInstanceProcAddr == nullptr)
		initvk();

	std::vector<VkLayerProperties> layerProperties;
	uint32_t propertieCount;

	checkVKResult(vkEnumerateInstanceLayerProperties(&propertieCount, nullptr));
	layerProperties.resize(propertieCount);
	checkVKResult(vkEnumerateInstanceLayerProperties(&propertieCount, layerProperties.data()));

	return layerProperties;
}

std::vector<VkExtensionProperties> Instance::extensionProperties(const char* layerName)
{
	if (vkGetInstanceProcAddr == nullptr)
		initvk();

	uint32_t propertyCount;
	std::vector<VkExtensionProperties> properties;

	checkVKResult(vkEnumerateInstanceExtensionProperties(layerName, &propertyCount, nullptr));
	properties.resize(propertyCount);
	checkVKResult(vkEnumerateInstanceExtensionProperties(layerName, &propertyCount, properties.data()));

	return properties;
}

void Instance::getInstanceFuncPointers()
{

}

void initvk()
{
	if (vkCreateInstance == nullptr)
	{
		auto result = volkInitialize();
		if (result != VK_SUCCESS)
			throw std::runtime_error("Unable to initialize volk.");
	}
		
}
