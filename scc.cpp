#include "scc.h"
#include "device.h"

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

bool Fence::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
