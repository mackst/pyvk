#include "buffers.h"
#include "device.h"
#include "exception.h"


Buffer::Buffer()
{
}

Buffer::Buffer(Device * device, BufferCreateInfo & info)
	:_device(device)
{
	VkBufferCreateInfo createInfo = {};
	info.getVKStruct(&createInfo);
	_device->table.vkCreateBuffer(_device->vkHandle, &createInfo, nullptr, &vkHandle);
}

Buffer::~Buffer()
{
	if (isValid())
	{
		_device->table.vkDestroyBuffer(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
	}
}

VkMemoryRequirements * Buffer::getMemoryRequirements()
{
	auto mr = new VkMemoryRequirements();
	_device->table.vkGetBufferMemoryRequirements(_device->vkHandle, vkHandle, mr);
	return mr;
}

Buffer * Buffer::bind(DeviceMemory * memory, VkDeviceSize memoryOffset)
{
	checkVKResult(_device->table.vkBindBufferMemory(_device->vkHandle, vkHandle, memory->vkHandle, memoryOffset));
	return this;
}

bool Buffer::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

BufferView::BufferView()
{
}

BufferView::BufferView(Device * device, CreateBufferViewInfo & info)
	:_device(device)
{
	VkBufferViewCreateInfo createInfo = {};
	info.getVKStruct(&createInfo);
	_device->table.vkCreateBufferView(_device->vkHandle, &createInfo, nullptr, &vkHandle);
}

BufferView::~BufferView()
{
	if (isValid())
	{
		_device->table.vkDestroyBufferView(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
	}
}

bool BufferView::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
