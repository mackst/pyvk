#include "cmdBuffers.h"
#include "device.h"


CommandPool::CommandPool()
{
}

CommandPool::CommandPool(Device * device, VkCommandPoolCreateInfo & createInfo)
{
}

CommandPool::~CommandPool()
{
	if (isValid())
	{
		_device->table.vkDestroyCommandPool(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
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
		_device->table.vkFreeCommandBuffers(_device->vkHandle, _cmdPool->vkHandle, 1, &vkHandle);
		vkHandle = VK_NULL_HANDLE;
		//pool = VK_NULL_HANDLE;
		_cmdPool = nullptr;
		_device = nullptr;
	}
}

bool CommandBuffer::isValid()
{
	return false;
}
