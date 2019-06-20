#include "instance.h"






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

	VkApplicationInfo appInfo;
	info.appInfo.getVKStruct(&appInfo);

	VkInstanceCreateInfo createInfo;
	info.getVKStruct(&createInfo);
	createInfo.pApplicationInfo = &appInfo;

	auto func = (PFN_vkCreateInstance)vkGetInstanceProcAddr(nullptr, "vkCreateInstance");
	if (func != nullptr)
	{
		checkVKResult(func(&createInfo, nullptr, &vkHandle));
	}
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

//bool Instance::create2(InstanceCreateInfo &info)
//{
//	auto _appInfo = info.getAppInfo();
//	VkApplicationInfo appInfo = {};
//	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//	appInfo.apiVersion = _appInfo->getApiVersion();
//	appInfo.applicationVersion = _appInfo->getApplicationVersion();
//	appInfo.engineVersion = _appInfo->getEngineVersion();
//	appInfo.pApplicationName = _appInfo->getApplicationName().c_str();
//	appInfo.pEngineName = _appInfo->getEngineName().c_str();
//
//	VkInstanceCreateInfo createInfo = {};
//	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//	createInfo.pApplicationInfo = &appInfo;
//	std::vector<std::string> layerNames = info.getLayerNames();
//	auto lnames = vecStrToVecChar(layerNames);
//	createInfo.enabledLayerCount = static_cast<uint32_t>(layerNames.size());
//	createInfo.ppEnabledLayerNames = lnames.data();
//	auto extNames = info.getExtensionNames();
//	auto eNames = vecStrToVecChar(extNames);
//	createInfo.enabledExtensionCount = static_cast<uint32_t>(extNames.size());
//	createInfo.ppEnabledExtensionNames = eNames.data();
//
//	auto func = (PFN_vkCreateInstance)vkGetInstanceProcAddr(nullptr, "vkCreateInstance");
//	if (func != nullptr)
//	{
//		checkVKResult(func(&createInfo, nullptr, &vkHandle));
//	}
//	//else
//	//	checkVKResult(vkCreateInstance(&createInfo, nullptr, &vkHandle));
//
//	getInstanceFuncPointers();
//
//	return true;
//}


void Instance::destroy()
{
	if (_debugMessenger != nullptr)
	{
		_debugMessenger->destroy();
		_debugMessenger = nullptr;
	}
		
	if (_surfaceKHR != nullptr)
	{
		_surfaceKHR->destroy();
		_surfaceKHR = nullptr;
	}

	if (vkHandle == VK_NULL_HANDLE)
		return;

	auto func = (PFN_vkDestroyInstance)vkGetInstanceProcAddr(vkHandle, "vkDestroyInstance");
	if (func != nullptr)
		func(vkHandle, nullptr);
	//else
	//	vkDestroyInstance(vkHandle, nullptr);
	vkHandle = VK_NULL_HANDLE;
	//py::print("instance destroyed.");
}

//DebugUtilsMessengerEXT* Instance::createDebugUtilsMessengerEXT(int messageSeverity, int messageType, py::function userCallback)
//{
//	_debugMessenger = new DebugUtilsMessengerEXT(vkHandle, messageSeverity, messageType, userCallback);
//	return _debugMessenger;
//}
//
//SurfaceKHR * Instance::createSurface(py::dict createInfo)
//{
//	_surfaceKHR = new SurfaceKHR(vkHandle, createInfo);
//	return _surfaceKHR;
//	//return new SurfaceKHR(vkHandle, createInfo);
//}
//
//py::list Instance::getPhysicalDevices()
//{
//	py::list devices;
//	
//	uint32_t deviceCount;
//	checkVKResult(vkEnumeratePhysicalDevices(vkHandle, &deviceCount, nullptr));
//
//	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
//	checkVKResult(vkEnumeratePhysicalDevices(vkHandle, &deviceCount, physicalDevices.data()));
//
//	for (auto item : physicalDevices)
//	{
//		PhysicalDevice device(vkHandle, item);
//		devices.append(device);
//	}
//
//	return devices;
//}

bool Instance::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

uint32_t Instance::version()
{
	if (vkGetInstanceProcAddr == nullptr)
		initvk();

	uint32_t version;
	auto func = (PFN_vkEnumerateInstanceVersion)vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceVersion");
	if (func != nullptr)
	{
		func(&version);
	}
	//else
	//	vkEnumerateInstanceVersion(&version);
	return version;
}

std::vector<VkLayerProperties> Instance::layerProperties()
{
	if (vkGetInstanceProcAddr == nullptr)
		initvk();

	//py::list properties;
	std::vector<VkLayerProperties> layerProperties;
	uint32_t propertieCount;

	auto func = (PFN_vkEnumerateInstanceLayerProperties)vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceLayerProperties");
	if (func != nullptr)
	{
		checkVKResult(func(&propertieCount, nullptr));
		layerProperties.resize(propertieCount);
		checkVKResult(func(&propertieCount, layerProperties.data()));
	}
	//else
	//{
	//	checkVKResult(vkEnumerateInstanceLayerProperties(&propertieCount, nullptr));
	//	layerProperties.resize(propertieCount);
	//	checkVKResult(vkEnumerateInstanceLayerProperties(&propertieCount, layerProperties.data()));
	//}

	//for (auto item : layerProperties)
	//{
	//	py::dict lp;
	//	lp["layerName"] = py::str(item.layerName);
	//	lp["specVersion"] = py::int_(item.specVersion);
	//	lp["implementationVersion"] = py::int_(item.implementationVersion);
	//	lp["description"] = py::str(item.description);

	//	properties.append(lp);
	//}

	//return properties;

	return layerProperties;
}

std::vector<VkExtensionProperties> Instance::extensionProperties(const char* layerName)
{
	if (vkGetInstanceProcAddr == nullptr)
		initvk();

	//py::list extProperties;
	uint32_t propertyCount;
	std::vector<VkExtensionProperties> properties;

	auto func = (PFN_vkEnumerateInstanceExtensionProperties)vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceExtensionProperties");

	if (func != nullptr)
	{
		checkVKResult(func(layerName, &propertyCount, nullptr));
		properties.resize(propertyCount);
		checkVKResult(func(layerName, &propertyCount, properties.data()));
	}
	else
		throw std::runtime_error("failed to get vkEnumerateInstanceExtensionProperties function pointer.");
	//else
	//{
	//	checkVKResult(vkEnumerateInstanceExtensionProperties(layerName, &propertyCount, nullptr));
	//	properties.resize(propertyCount);
	//	checkVKResult(vkEnumerateInstanceExtensionProperties(layerName, &propertyCount, properties.data()));
	//}

	//for (auto item : properties)
	//{
	//	py::dict prop;
	//	prop["extensionName"] = py::str(item.extensionName);
	//	prop["specVersion"] = py::int_(item.specVersion);

	//	extProperties.append(prop);
	//}

	//return extProperties;
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
