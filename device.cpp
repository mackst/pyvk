#include "device.h"
#include "utils.h"
#include "exception.h"
#include "extensions.h"


PhysicalDevice::PhysicalDevice()
{
}

PhysicalDevice::PhysicalDevice(VkInstance & instance, VkPhysicalDevice & device) : _instance(instance), vkHandle(device)
{
}

//PhysicalDevice::PhysicalDevice(PhysicalDevice & device)
//{
//	_instance = device._instance;
//	vkHandle = device.vkHandle;
//}

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
	std::string dn(properties.deviceName);
	std::string a = "<PhysicalDevice() for " + dn + ">";
	return a;
}

VkPhysicalDeviceProperties PhysicalDevice::getProperties()
{
	VkPhysicalDeviceProperties properties;
	vkGetPhysicalDeviceProperties(vkHandle, &properties);

	return properties;
}

VkPhysicalDeviceProperties2 PhysicalDevice::getProperties2(VkPhysicalDeviceProperties2* properties2)
{
	//VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME
	if (vkGetPhysicalDeviceProperties2 == nullptr)
		throw ExtensionNotPresent("VK_KHR_get_physical_device_properties2 not present.");
	
	if (properties2 != nullptr)
	{
		vkGetPhysicalDeviceProperties2(vkHandle, properties2);
		return *properties2;
	}
	else
	{
		VkPhysicalDeviceProperties2 properties;
		vkGetPhysicalDeviceProperties2(vkHandle, &properties);
		return properties;
	}
}

std::vector<VkLayerProperties> PhysicalDevice::layerProperties()
{
	std::vector<VkLayerProperties> layerProperties;
	uint32_t propertieCount;

	if (!isValid())
		return layerProperties;

	checkVKResult(vkEnumerateDeviceLayerProperties(vkHandle, &propertieCount, nullptr));

	layerProperties.resize(propertieCount);
	checkVKResult(vkEnumerateDeviceLayerProperties(vkHandle, &propertieCount, layerProperties.data()));


	return layerProperties;
}

std::vector<VkExtensionProperties> PhysicalDevice::extensionProperties(const char * layerName)
{
	uint32_t propertyCount;
	std::vector<VkExtensionProperties> properties;

	if (!isValid())
		return properties;

	checkVKResult(vkEnumerateDeviceExtensionProperties(vkHandle, layerName, &propertyCount, nullptr));

	properties.resize(propertyCount);
	checkVKResult(vkEnumerateDeviceExtensionProperties(vkHandle, layerName, &propertyCount, properties.data()));

	return properties;
}

std::vector<VkQueueFamilyProperties> PhysicalDevice::getQueueFamilyProperties()
{
	uint32_t propertyCount;
	vkGetPhysicalDeviceQueueFamilyProperties(vkHandle, &propertyCount, nullptr);

	std::vector<VkQueueFamilyProperties> properties(propertyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(vkHandle, &propertyCount, properties.data());

	return properties;
}

VkBool32 PhysicalDevice::getSurfaceSupportKHR(SurfaceKHR &surface, uint32_t queueFamilyIndex)
{
	VkBool32 support = false;
	checkVKResult(vkGetPhysicalDeviceSurfaceSupportKHR(vkHandle, queueFamilyIndex, surface.vkHandle, &support));
	return support;
}

VkSurfaceCapabilitiesKHR PhysicalDevice::getSurfaceCapabilitiesKHR(SurfaceKHR & surface)
{
	VkSurfaceCapabilitiesKHR capabilities;

	checkVKResult(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkHandle, surface.vkHandle, &capabilities));

	return capabilities;
}

std::vector<VkSurfaceFormatKHR> PhysicalDevice::getSurfaceFormatsKHR(SurfaceKHR & surface)
{
	uint32_t formatCount;

	checkVKResult(vkGetPhysicalDeviceSurfaceFormatsKHR(vkHandle, surface.vkHandle, &formatCount, nullptr));

	std::vector<VkSurfaceFormatKHR> formats(formatCount);
	checkVKResult(vkGetPhysicalDeviceSurfaceFormatsKHR(vkHandle, surface.vkHandle, &formatCount, formats.data()));

	return formats;
}

std::vector<VkPresentModeKHR> PhysicalDevice::getSurfacePresentModeKHR(SurfaceKHR & surface)
{
	uint32_t count;
	checkVKResult(vkGetPhysicalDeviceSurfacePresentModesKHR(vkHandle, surface.vkHandle, &count, nullptr));

	std::vector<VkPresentModeKHR> modes(count);
	checkVKResult(vkGetPhysicalDeviceSurfacePresentModesKHR(vkHandle, surface.vkHandle, &count, modes.data()));

	return modes;
}


Device::Device(PhysicalDevice &physicalDevice, DeviceCreateInfo &createInfo) : _physicalDevice(physicalDevice)
{	
	create(createInfo);
}


Device::~Device()
{
	destroy();
}

bool Device::create(DeviceCreateInfo &createInfo)
{
	VkDeviceCreateInfo _createInfo = {};
	createInfo.getVKStruct(&_createInfo);
	
	checkVKResult(vkCreateDevice(_physicalDevice.vkHandle, &_createInfo, nullptr, &vkHandle));

	// load device functions
	volkLoadDeviceTable(&table, vkHandle);

	return isValid();
}

void Device::destroy()
{
	if (isValid())
	{
		table.vkDestroyDevice(vkHandle, nullptr);
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

//SwapchainKHR * Device::createSwapchainKHR(py::dict createInfo)
//{
//	return new SwapchainKHR(this, createInfo);
//}
//
//py::list Device::getSwapchainImagesKHR(SwapchainKHR & swapchain)
//{
//	return swapchain.getImagesKHR();
//}

ImageView* Device::createImageView(py::dict createInfo)
{
	return new ImageView(vkHandle, createInfo);
}

ShaderModule * Device::createShaderModule(const std::string &filename)
{
	return new ShaderModule(vkHandle, filename);
}

PipelineLayout * Device::createPipelineLayout(py::dict createInfo)
{
	return new PipelineLayout(vkHandle, createInfo);
}

//PipelineLayout * Device::createPipelineLayout(PipelineLayoutCreateInfo & createInfo)
//{
//	return new PipelineLayout(vkHandle, createInfo);
//}

RenderPass * Device::createRenderPass(RenderPassCreateInfo & createInfo)
{
	return new RenderPass(vkHandle, createInfo);
}

std::vector<Pipeline> Device::createGraphicsPipelines(PipelineCache & cache, py::list createInfos)
{
	std::vector<Pipeline> out;
	std::vector<VkPipeline> _pipelines;
	uint32_t count = static_cast<uint32_t>(createInfos.size());
	//std::vector<VkGraphicsPipelineCreateInfo> _createInfos(count);
	//int i = 0;
	//for (auto item : createInfos)
	//{
	//	auto _createInfo = dictToVkGraphicsPipelineCreateInfo(item.cast<py::dict>());
	//	//_createInfos.emplace_back(_createInfo);
	//	_createInfos[i] = _createInfo;
	//	i++;
	//}

	////uint32_t count = static_cast<uint32_t>(createInfos.size());
	//py::print("resize VkPipeline list.");
	//py::print(count);
	_pipelines.resize(count);
	//py::print("create VkPipeline");
	//auto _createInfos = dictToVkGraphicsPipelineCreateInfo(createInfos);
	//py::print(_createInfos.size());
	//py::print(_createInfos[0].pVertexInputState->vertexAttributeDescriptionCount);
	//py::print(_createInfos[0].pVertexInputState->vertexBindingDescriptionCount);

	//checkVKResult(_vkCreateGraphicsPipelines(vkHandle, cache.vkHandle, count, _createInfos.data(), nullptr, _pipelines.data()));
	//
	//py::print("VkPipeline created!!!!!!!!!!!");
	//for (auto item : _pipelines) 
	//{
	//	Pipeline p;
	//	p.vkHandle = item;
	//	p._device = vkHandle;
	//	p._vkDestroyPipeline = _vkDestroyPipeline;
	//	out.emplace_back(p);
	//}

	//return out;
}

//std::vector<Pipeline> Device::createGraphicsPipelines(PipelineCache & cache, std::vector<GraphicsPipelineCreateInfo*> createInfos)
//{
//	std::vector<Pipeline> out;
//	std::vector<VkPipeline> _pipelines;
//	
//	uint32_t count = static_cast<uint32_t>(createInfos.size());
//	//auto to_vktype = [](GraphicsPipelineCreateInfo* info) { return info->to_vktype(); };
//	std::vector<VkGraphicsPipelineCreateInfo> _createInfos;
//	//py::print("start transform GraphicsPipelineCreateInfo to VkGraphicsPipelineCreateInfo");
//	//std::transform(createInfos.begin(), createInfos.end(), _createInfos.begin(), to_vktype);
//	//py::print("done.");
//	for (auto item : createInfos)
//	{
//		auto info = item->to_vktype();
//		_createInfos.emplace_back(info);
//	}
//		
//
//	py::print((int)_createInfos[0].pViewportState->sType);
//	_pipelines.resize(count);
//	checkVKResult(_vkCreateGraphicsPipelines(vkHandle, cache.vkHandle, count, _createInfos.data(), nullptr, _pipelines.data()));
//
//	//out.resize(_pipelines.size());
//	for (auto item : _pipelines) 
//	{
//		Pipeline p;
//		p.vkHandle = item;
//		p._device = vkHandle;
//		p._vkDestroyPipeline = _vkDestroyPipeline;
//		out.emplace_back(p);
//	}
//
//	return out;
//}



DeviceQueue::DeviceQueue(Device *device, uint32_t queueFamilyIndex, uint32_t queueIndex)
{
	device->table.vkGetDeviceQueue(device->vkHandle, queueFamilyIndex, queueIndex, &vkHandle);
}

DeviceQueue::~DeviceQueue()
{
	vkHandle = VK_NULL_HANDLE;
}

bool DeviceQueue::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

