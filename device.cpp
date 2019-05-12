#include "device.h"
#include "utils.h"
#include "exception.h"
#include "extensions.h"
#include "deviceQueue.h"


PhysicalDevice::PhysicalDevice()
{
}

PhysicalDevice::PhysicalDevice(VkInstance & instance, VkPhysicalDevice & device) : _instance(instance), vkHandle(device)
{
	_vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)vkGetInstanceProcAddr(_instance, "vkGetPhysicalDeviceProperties");
	_vkGetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2)vkGetInstanceProcAddr(_instance, "vkGetPhysicalDeviceProperties2");
	_vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)vkGetInstanceProcAddr(_instance, "vkGetPhysicalDeviceQueueFamilyProperties");
	_vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)vkGetInstanceProcAddr(_instance, "vkGetPhysicalDeviceSurfaceSupportKHR");
	_vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties)vkGetInstanceProcAddr(_instance, "vkEnumerateDeviceLayerProperties");
	_vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)vkGetInstanceProcAddr(_instance, "vkEnumerateDeviceExtensionProperties");
	_vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)vkGetInstanceProcAddr(_instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
	_vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)vkGetInstanceProcAddr(_instance, "vkGetPhysicalDeviceSurfaceFormatsKHR");
	_vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)vkGetInstanceProcAddr(_instance, "vkGetPhysicalDeviceSurfacePresentModesKHR");
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
	std::string a = "<PhysicalDevice() for " + properties["deviceName"].cast<std::string>() + ">";
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

py::list PhysicalDevice::layerProperties()
{
	py::list properties;
	std::vector<VkLayerProperties> layerProperties;
	uint32_t propertieCount;

	if (!isValid())
		return properties;

	checkVKResult(_vkEnumerateDeviceLayerProperties(vkHandle, &propertieCount, nullptr));

	layerProperties.resize(propertieCount);
	checkVKResult(_vkEnumerateDeviceLayerProperties(vkHandle, &propertieCount, layerProperties.data()));

	for (auto item : layerProperties)
	{
		py::dict lp;
		lp["layerName"] = py::str(item.layerName);
		lp["specVersion"] = py::int_(item.specVersion);
		lp["implementationVersion"] = py::int_(item.implementationVersion);
		lp["description"] = py::str(item.description);

		properties.append(lp);
	}

	return properties;
}

py::list PhysicalDevice::extensionProperties(const char * layerName)
{
	py::list extProperties;
	uint32_t propertyCount;
	std::vector<VkExtensionProperties> properties;

	if (!isValid())
		return extProperties;

	checkVKResult(_vkEnumerateDeviceExtensionProperties(vkHandle, layerName, &propertyCount, nullptr));

	properties.resize(propertyCount);
	checkVKResult(_vkEnumerateDeviceExtensionProperties(vkHandle, layerName, &propertyCount, properties.data()));

	for (auto item : properties)
	{
		py::dict prop;
		prop["extensionName"] = py::str(item.extensionName);
		prop["specVersion"] = py::int_(item.specVersion);

		extProperties.append(prop);
	}

	return extProperties;
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

VkBool32 PhysicalDevice::getSurfaceSupportKHR(SurfaceKHR &surface, uint32_t queueFamilyIndex)
{
	VkBool32 support = false;
	checkVKResult(_vkGetPhysicalDeviceSurfaceSupportKHR(vkHandle, queueFamilyIndex, surface.vkHandle, &support));
	return support;
}

VkSurfaceCapabilitiesKHR PhysicalDevice::getSurfaceCapabilitiesKHR(SurfaceKHR & surface)
{
	VkSurfaceCapabilitiesKHR capabilities;

	checkVKResult(_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkHandle, surface.vkHandle, &capabilities));

	return capabilities;
}

std::vector<VkSurfaceFormatKHR> PhysicalDevice::getSurfaceFormatsKHR(SurfaceKHR & surface)
{
	uint32_t formatCount;

	checkVKResult(_vkGetPhysicalDeviceSurfaceFormatsKHR(vkHandle, surface.vkHandle, &formatCount, nullptr));

	std::vector<VkSurfaceFormatKHR> formats(formatCount);
	checkVKResult(_vkGetPhysicalDeviceSurfaceFormatsKHR(vkHandle, surface.vkHandle, &formatCount, formats.data()));

	return formats;
}

std::vector<VkPresentModeKHR> PhysicalDevice::getSurfacePresentModeKHR(SurfaceKHR & surface)
{
	uint32_t count;
	checkVKResult(_vkGetPhysicalDeviceSurfacePresentModesKHR(vkHandle, surface.vkHandle, &count, nullptr));

	std::vector<VkPresentModeKHR> modes(count);
	checkVKResult(_vkGetPhysicalDeviceSurfacePresentModesKHR(vkHandle, surface.vkHandle, &count, modes.data()));

	return modes;
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
		std::vector<float> queuePrioritieList = item["queuePriorities"].cast<std::vector<float>>();
		std::vector<float> queuePriorities = vecFloatToVecFloat(queuePrioritieList);
		//std::vector<float> queuePriorities;
		//for (auto item : queuePrioritieList)
			//queuePriorities.emplace_back((float)item);

		VkDeviceQueueCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		info.pQueuePriorities = queuePriorities.data();
		info.queueCount = item["queueCount"].cast<uint32_t>();
		info.queueFamilyIndex = item["queueFamilyIndex"].cast<uint32_t>();
		
		queueCreateInfos.emplace_back(info);

		// debug
		//std::cout << queuePriorities[0] << std::endl;
		//py::print(queuePriorities);
		//py::print(info.queueCount);
		//py::print(info.queueFamilyIndex);
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

	//VkPhysicalDeviceFeatures deviceFeatures = {};
	VkPhysicalDeviceFeatures deviceFeatures = createInfo["deviceFeatures"].cast<VkPhysicalDeviceFeatures>();
	_createInfo.pEnabledFeatures = &deviceFeatures;

	checkVKResult(_vkCreateDevice(_physicalDevice.vkHandle, &_createInfo, nullptr, &vkHandle));

	getFuncPointers();

	return isValid();
}

void Device::destroy()
{
	if (isValid())
	{
		_vkDestroyDevice(vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_physicalDevice = {};
	}
}

bool Device::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

DeviceQueue * Device::getQueue(uint32_t queueFamilyIndex, uint32_t queueIndex)
{
	return new DeviceQueue(this, queueFamilyIndex, queueIndex);
}

SwapchainKHR * Device::createSwapchainKHR(py::dict createInfo)
{
	return new SwapchainKHR(this, createInfo);
}

py::list Device::getSwapchainImagesKHR(SwapchainKHR & swapchain)
{
	return swapchain.getImagesKHR();
}

ImageView* Device::createImageView(py::dict createInfo)
{
	return new ImageView(vkHandle, createInfo);
}

ShaderModule * Device::createShaderModule(const std::string &filename)
{
	return new ShaderModule(vkHandle, filename);
}

//PipelineLayout * Device::createPipelineLayout(py::dict createInfo)
//{
//	return new PipelineLayout(vkHandle, createInfo);
//}

PipelineLayout * Device::createPipelineLayout(PipelineLayoutCreateInfo & createInfo)
{
	return new PipelineLayout(vkHandle, createInfo);
}

RenderPass * Device::createRenderPass(RenderPassCreateInfo & createInfo)
{
	return new RenderPass(vkHandle, createInfo);
}

void Device::getFuncPointers()
{
	_vkDestroyDevice = (PFN_vkDestroyDevice)vkGetDeviceProcAddr(vkHandle, "vkDestroyDevice");
	_vkGetDeviceQueue = (PFN_vkGetDeviceQueue)vkGetDeviceProcAddr(vkHandle, "vkGetDeviceQueue");
	_vkCreateImageView = (PFN_vkCreateImageView)vkGetDeviceProcAddr(vkHandle, "vkCreateImageView");
}




