#include "device.h"
#include "utils.h"
#include "exception.h"


PhysicalDevice::PhysicalDevice()
{
}

PhysicalDevice::PhysicalDevice(VkInstance & instance, VkPhysicalDevice & device) : _instance(instance), vkHandle(device)
{
	_vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)vkGetInstanceProcAddr(_instance, "vkGetPhysicalDeviceProperties");
	_vkGetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2)vkGetInstanceProcAddr(_instance, "vkGetPhysicalDeviceProperties2");
	_vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)vkGetInstanceProcAddr(_instance, "vkGetPhysicalDeviceQueueFamilyProperties");


}

PhysicalDevice::~PhysicalDevice()
{
	_instance = VK_NULL_HANDLE;
	vkHandle = VK_NULL_HANDLE;
}

bool PhysicalDevice::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

std::string PhysicalDevice::toString()
{
	auto properties = getProperties();
	std::string a = "<class PhysicalDevice for " + properties["deviceName"].cast<std::string>() + ">";
	return a;
}

py::dict PhysicalDevice::getProperties()
{
	py::dict out;
	VkPhysicalDeviceProperties properties;
	_vkGetPhysicalDeviceProperties(vkHandle, &properties);

	out["apiVersion"] = properties.apiVersion;
	out["driverVersion"] = properties.driverVersion;
	out["vendorID"] = properties.vendorID;
	out["deviceID"] = properties.deviceID;
	out["deviceType"] = properties.deviceType;
	out["deviceName"] = py::str(properties.deviceName);
	out["pipelineCacheUUID"] = properties.pipelineCacheUUID;
	//out["limits"] = properties.limits;

	return out;
}

py::dict PhysicalDevice::getProperties2()
{
	return py::dict();
}

py::list PhysicalDevice::getQueueFamilyProperties()
{
	py::list out;

	uint32_t propertyCount;
	_vkGetPhysicalDeviceQueueFamilyProperties(vkHandle, &propertyCount, nullptr);

	std::vector<VkQueueFamilyProperties> properties(propertyCount);
	_vkGetPhysicalDeviceQueueFamilyProperties(vkHandle, &propertyCount, properties.data());

	for (auto item : properties)
	{
		py::dict p;
		p["queueFlags"] = item.queueFlags;
		p["queueCount"] = item.queueCount;
		p["timestampValidBits"] = item.timestampValidBits;
		p["minImageTransferGranularity"] = item.minImageTransferGranularity;

		out.append(p);
	}

	return out;
}


Device::Device(PhysicalDevice &physicalDevice, py::dict createInfo) : _physicalDevice(physicalDevice)
{
	_vkCreateDevice = (PFN_vkCreateDevice)vkGetInstanceProcAddr(_physicalDevice._instance, "vkCreateDevice");
	

	create(createInfo);
}


Device::~Device()
{
	destroy();
}

bool Device::create(py::dict createInfo)
{
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	py::list queueCreateInfo = createInfo["queueCreateInfos"].cast<py::list>();

	for (auto item : queueCreateInfo)
	{
		std::vector<float> queuePriorities = item["queuePriorities"].cast<std::vector<float>>();

		VkDeviceQueueCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		info.pQueuePriorities = queuePriorities.data();
		info.queueCount = item["queueCount"].cast<uint32_t>();
		info.queueFamilyIndex = item["queueFamilyIndex"].cast<uint32_t>();
		
		queueCreateInfos.emplace_back(info);

		// debug
		py::print(queuePriorities);
		py::print(info.queueCount);
		py::print(info.queueFamilyIndex);
	}

	std::vector<std::string> enabledLayerNamesList = createInfo["enabledLayerNames"].cast<std::vector<std::string>>();
	std::vector<const char*> enabledLayerNames = vecStrToVecChar(enabledLayerNamesList);

	std::vector<std::string> enabledExtensionNamesList = createInfo["enabledExtensionNames"].cast<std::vector<std::string>>();
	std::vector<const char*> enabledExtensionNames = vecStrToVecChar(enabledExtensionNamesList);

	VkDeviceCreateInfo _createInfo = {};
	_createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	_createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	_createInfo.pQueueCreateInfos = queueCreateInfos.data();
	
	auto enabledLayerCount = static_cast<uint32_t>(enabledLayerNames.size());
	if (enabledLayerCount > 0)
	{
		_createInfo.enabledLayerCount = enabledLayerCount;
		_createInfo.ppEnabledLayerNames = enabledLayerNames.data();
	}
	else
		_createInfo.enabledLayerCount = 0;

	auto enabledExtensionCount = static_cast<uint32_t>(enabledExtensionNames.size());
	if (enabledExtensionCount > 0)
	{
		_createInfo.enabledExtensionCount = enabledExtensionCount;
		_createInfo.ppEnabledExtensionNames = enabledExtensionNames.data();
	}
	else
	{
		_createInfo.enabledExtensionCount = 0;
	}

	VkPhysicalDeviceFeatures deviceFeatures = {};
	_createInfo.pEnabledFeatures = &deviceFeatures;

	//checkVKResult(_vkCreateDevice(_physicalDevice.vkHandle, &_createInfo, nullptr, &vkHandle));

	return isValid();
}

void Device::destroy()
{
}

bool Device::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

void Device::getInstanceFuncPointers()
{
	_vkDestroyDevice = (PFN_vkDestroyDevice)vkGetDeviceProcAddr(vkHandle, "vkDestroyDevice");
	_vkGetDeviceQueue = (PFN_vkGetDeviceQueue)vkGetDeviceProcAddr(vkHandle, "vkGetDeviceQueue");
}
