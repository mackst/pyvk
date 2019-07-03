#include "cmdBuffers.h"
#include "device.h"
#include "exception.h"


CommandPool::CommandPool()
{
}

CommandPool::CommandPool(Device * device, VkCommandPoolCreateInfo & createInfo)
	: _device(device)
{
	checkVKResult(_device->table.vkCreateCommandPool(_device->vkHandle, &createInfo, nullptr, &vkHandle));
}

CommandPool::~CommandPool()
{
	if (isValid())
	{
		py::print("in CommandPool::~CommandPool().");
		_device->table.vkDestroyCommandPool(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
		py::print("commandPool destroyed.");
	}
}

bool CommandPool::reset(VkCommandPoolResetFlags flags)
{
	if (isValid())
	{
		auto result = _device->table.vkResetCommandPool(_device->vkHandle, vkHandle, flags);
		return result == VK_SUCCESS;
	}
	return false;
}

bool CommandPool::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

CommandBuffer::CommandBuffer()
{
}

CommandBuffer::~CommandBuffer()
{
	if (isValid())
	{
		py::print("in CommandBuffer::~CommandBuffer().");
		_device->table.vkFreeCommandBuffers(_device->vkHandle, _cmdPool->vkHandle, 1, &vkHandle);
		vkHandle = VK_NULL_HANDLE;
		//pool = VK_NULL_HANDLE;
		_cmdPool = nullptr;
		_device = nullptr;
		py::print("commandBuffer freed.");
	}
}

bool CommandBuffer::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
