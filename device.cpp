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

VkPhysicalDeviceMemoryProperties PhysicalDevice::getMemoryProperties()
{
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(vkHandle, &memProperties);
	return memProperties;
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

Queue * Device::getQueue(uint32_t queueFamilyIndex, uint32_t queueIndex)
{
	return new Queue(this, queueFamilyIndex, queueIndex);
}

SwapchainKHR * Device::createSwapchainKHR(SwapchainCreateInfoKHR &createInfo)
{
	return new SwapchainKHR(this, createInfo);
}

py::list Device::getSwapchainImagesKHR(SwapchainKHR & swapchain)
{
	return swapchain.getImagesKHR();
}

ImageView* Device::createImageView(ImageViewCreateInfo &createInfo)
{
	return new ImageView(this, createInfo);
}

ShaderModule * Device::createShaderModule(const std::string &filename)
{
	return new ShaderModule(this, filename);
}

PipelineLayout* Device::createPipelineLayout(PipelineLayoutCreateInfo & createInfo)
{
	//return new PipelineLayout(this, createInfo);
	PipelineLayout *layout = new PipelineLayout();
	VkPipelineLayoutCreateInfo _createInfo = {};
	createInfo.getVKStruct(&_createInfo);
	checkVKResult(table.vkCreatePipelineLayout(vkHandle, &_createInfo, nullptr, &layout->vkHandle));
	layout->_device = this;
	return layout;
}

RenderPass * Device::createRenderPass(RenderPassCreateInfo & createInfo)
{
	return new RenderPass(this, createInfo);
}


std::vector<Pipeline*> Device::createGraphicsPipelines(PipelineCache & cache, std::vector<GraphicsPipelineCreateInfo*> &createInfos)
{
	std::vector<Pipeline*> out;
	std::vector<VkPipeline> _pipelines;
	
	uint32_t count = static_cast<uint32_t>(createInfos.size());
	std::vector<VkGraphicsPipelineCreateInfo> _createInfos;
	for (auto item : createInfos)
	{
		VkGraphicsPipelineCreateInfo info = {};
		item->getVKStruct(&info);
		_createInfos.emplace_back(info);
	}
		
	_pipelines.resize(count);
	checkVKResult(table.vkCreateGraphicsPipelines(vkHandle, cache.vkHandle, count, _createInfos.data(), nullptr, _pipelines.data()));
	//auto result = table.vkCreateGraphicsPipelines(vkHandle, cache.vkHandle, count, _createInfos.data(), nullptr, _pipelines.data());
	//py::print(result);
	for (uint32_t i = 0; i < count; i++)
	{
		Pipeline *p = new Pipeline();
		p->vkHandle = _pipelines[i];
		p->_device = this;
		out.emplace_back(p);
	}
	return out;
}

std::vector<Pipeline*> Device::createComputePipelines(PipelineCache & cache, std::vector<ComputePipelineCreateInfo*>& infos)
{
	std::vector<Pipeline*> out;
	std::vector<VkPipeline> _pipelines;

	uint32_t count = static_cast<uint32_t>(infos.size());
	std::vector<VkComputePipelineCreateInfo> _createInfos;
	for (auto item : infos)
	{
		VkComputePipelineCreateInfo info = {};
		item->getVKStruct(&info);
		_createInfos.emplace_back(info);
	}

	_pipelines.resize(count);
	checkVKResult(table.vkCreateComputePipelines(vkHandle, cache.vkHandle, count, _createInfos.data(), nullptr, _pipelines.data()));

	for (uint32_t i = 0; i < count; i++)
	{
		Pipeline *p = new Pipeline();
		p->vkHandle = _pipelines[i];
		p->_device = this;
		out.emplace_back(p);
	}

	return out;
}

Framebuffer * Device::createFramebuffer(FramebufferCreateInfo & createInfo)
{
	return new Framebuffer(this, createInfo);
}

CommandPool * Device::createCommandPool(VkCommandPoolCreateInfo & createInfo)
{
	return new CommandPool(this, createInfo);
}

std::vector<CommandBuffer*> Device::allocateCommandBuffers(CommandBufferAllocateInfo & createInfo)
{
	std::vector<CommandBuffer*> buffers;
	std::vector<VkCommandBuffer> _cmdBuffers(createInfo.commandBufferCount);

	VkCommandBufferAllocateInfo _createInfo = {};
	createInfo.getVKStruct(&_createInfo);
	checkVKResult(table.vkAllocateCommandBuffers(vkHandle, &_createInfo, _cmdBuffers.data()));

	for (auto buffer : _cmdBuffers)
	{
		CommandBuffer *buf = new CommandBuffer();
		buf->vkHandle = buffer;
		buf->_cmdPool = createInfo.commandPool;
		buf->_device = this;

		buffers.emplace_back(buf);
	}

	return buffers;
}

Semaphore * Device::createSemaphore(VkSemaphoreCreateInfo * createInfo)
{
	auto *semaphore = new Semaphore();
	table.vkCreateSemaphore(vkHandle, createInfo, nullptr, &semaphore->vkHandle);
	semaphore->_device = this;
	return semaphore;
}

Fence * Device::createFence(VkFenceCreateInfo * createInfo)
{
	auto *fence = new Fence();
	table.vkCreateFence(vkHandle, createInfo, nullptr, &fence->vkHandle);
	fence->_device = this;
	return fence;
}

bool Device::waitForFences(std::vector<Fence*>& fences, VkBool32 waitAll, uint64_t timeout)
{
	std::vector<VkFence> _fences;
	for (auto fence : fences)
	{
		_fences.emplace_back(fence->vkHandle);
	}
	auto result = table.vkWaitForFences(vkHandle, static_cast<uint32_t>(_fences.size()), _fences.data(), waitAll, timeout);
	checkVKResult(result);
	return result == VK_SUCCESS;
}

bool Device::resetFences(std::vector<Fence*>& fences)
{
	std::vector<VkFence> _fences;
	for (auto fence : fences)
	{
		_fences.emplace_back(fence->vkHandle);
	}
	auto result = table.vkResetFences(vkHandle, static_cast<uint32_t>(_fences.size()), _fences.data());
	checkVKResult(result);
	return result == VK_SUCCESS;
}

DeviceMemory * Device::allocateMemory(VkMemoryAllocateInfo * info)
{
	auto memory = new DeviceMemory();
	memory->_device = this;
	checkVKResult(table.vkAllocateMemory(vkHandle, info, nullptr, &memory->vkHandle));
	return memory;
}

Buffer * Device::createBuffer(BufferCreateInfo & createInfo)
{
	return new Buffer(this, createInfo);
}

DescriptorSetLayout * Device::createDescriptorSetLayout(DescriptorSetLayoutCreateInfo & createInfo)
{
	auto layout = new DescriptorSetLayout();
	VkDescriptorSetLayoutCreateInfo info = {};
	createInfo.getVKStruct(&info);
	checkVKResult(table.vkCreateDescriptorSetLayout(vkHandle, &info, nullptr, &layout->vkHandle));
	layout->_device = this;
	return layout;
}

DescriptorPool * Device::createDescriptorPool(DescriptorPoolCreateInfo & createInfo)
{
	auto pool = new DescriptorPool();
	VkDescriptorPoolCreateInfo info = {};
	createInfo.getVKStruct(&info);
	checkVKResult(table.vkCreateDescriptorPool(vkHandle, &info, nullptr, &pool->vkHandle));
	pool->_device = this;

	return pool;
}

std::vector<DescriptorSet*> Device::allocateDescriptorSets(DescriptorSetAllocateInfo & info)
{
	std::vector<DescriptorSet*> sets;
	std::vector<VkDescriptorSet> dsets(info.setLayouts.size());

	VkDescriptorSetAllocateInfo allocInfo = {};
	info.getVKStruct(&allocInfo);

	checkVKResult(table.vkAllocateDescriptorSets(vkHandle, &allocInfo, dsets.data()));
	
	for (auto set : dsets)
	{
		auto ds = new DescriptorSet();
		ds->_pool = info.getPool();
		ds->vkHandle = set;
		sets.emplace_back(ds);
	}

	return sets;
}

Device * Device::updateDescriptorSets(std::vector<WriteDescriptorSet>& writes, std::vector<CopyDescriptorSet>& copies)
{
	std::vector<VkWriteDescriptorSet> _writes;
	
	for (auto ws : writes)
	{
		VkWriteDescriptorSet set = {};
		ws.getVKStruct(&set);
		_writes.emplace_back(set);
	}
	auto copyCount = static_cast<uint32_t>(copies.size());
	if (copyCount > 0)
	{
		std::vector<VkCopyDescriptorSet> _copies;
		for (auto cs : copies)
		{
			VkCopyDescriptorSet cset = {};
			cs.getVKStruct(&cset);
			_copies.emplace_back(cset);
		}
		table.vkUpdateDescriptorSets(vkHandle, static_cast<uint32_t>(_writes.size()), _writes.data(), copyCount, _copies.data());
	}
	else
		table.vkUpdateDescriptorSets(vkHandle, static_cast<uint32_t>(_writes.size()), _writes.data(), 0, VK_NULL_HANDLE);
		

	return this;
}

Device * Device::waitIdle()
{
	checkVKResult(table.vkDeviceWaitIdle(vkHandle));
	return this;
}



Queue::Queue(Device *device, uint32_t queueFamilyIndex, uint32_t queueIndex)
	: _device(device)
{
	_device->table.vkGetDeviceQueue(_device->vkHandle, queueFamilyIndex, queueIndex, &vkHandle);
}

Queue::~Queue()
{
	vkHandle = VK_NULL_HANDLE;
	_device = nullptr;
}

Queue * Queue::submit(std::vector<SubmitInfo*>& infos, Fence * fence)
{
	auto count = static_cast<uint32_t>(infos.size());
	std::vector<VkSubmitInfo> submitInfo;
	for (auto info : infos)
	{
		VkSubmitInfo _info = {};
		info->getVKStruct(&_info);
		submitInfo.emplace_back(_info);
	}
	VkFence _fence = VK_NULL_HANDLE;
	if (fence != nullptr)
		_fence = fence->vkHandle;
	checkVKResult(_device->table.vkQueueSubmit(vkHandle, count, submitInfo.data(), _fence));
	return this;
}

Queue * Queue::presentKHR(PresentInfoKHR & info)
{
	VkPresentInfoKHR presentInfo = {};
	info.getVKStruct(&presentInfo);
	checkVKResult(_device->table.vkQueuePresentKHR(vkHandle, &presentInfo));
	return this;
}

Queue * Queue::waitIdle()
{
	checkVKResult(_device->table.vkQueueWaitIdle(vkHandle));
	return this;
}

bool Queue::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

DeviceMemory::DeviceMemory()
{
}

DeviceMemory::~DeviceMemory()
{
	if (isValid())
	{
		_device->table.vkFreeMemory(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
	}
}

py::buffer DeviceMemory::map(VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags)
{
	void* data;
	checkVKResult(_device->table.vkMapMemory(_device->vkHandle, vkHandle, offset, size, flags, &data));

	_memData = (char*)data;

	py::buffer_info info;
	info.format = py::format_descriptor<char>::value;
	info.itemsize = sizeof(char);
	info.ndim = 1;
	info.shape = { (int64_t)size };
	info.size = size;
	info.strides = { sizeof(char) };
	info.ptr = _memData;

	py::memoryview view(info);

	return py::buffer(view);
}

DeviceMemory * DeviceMemory::unmap()
{
	_device->table.vkUnmapMemory(_device->vkHandle, vkHandle);
	_memData = nullptr;
	return this;
}

DeviceMemory * DeviceMemory::copyFromBytes(py::bytes _bytes, uint32_t size)
{
	auto bytes = static_cast<std::string>(_bytes);
	memcpy(_memData, bytes.c_str(), size);
	return this;
}

bool DeviceMemory::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
