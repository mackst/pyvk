#include "scc.h"
#include "device.h"
#include "exception.h"


Semaphore::Semaphore()
{
}

Semaphore::~Semaphore()
{
	if (isValid())
	{
		_device->table.vkDestroySemaphore(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
	}
}

bool Semaphore::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

Fence::Fence()
{
}

Fence::~Fence()
{
	if (isValid())
	{
		_device->table.vkDestroyFence(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
	}
}

bool Fence::wait(uint64_t timeout)
{
	auto result = _device->table.vkWaitForFences(_device->vkHandle, 1, &vkHandle, VK_TRUE, timeout);
	checkVKResult(result);
	return result == VK_SUCCESS;
}

bool Fence::reset()
{
	auto result = _device->table.vkResetFences(_device->vkHandle, 1, &vkHandle);
	checkVKResult(result);
	return result == VK_SUCCESS;
}

bool Fence::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
