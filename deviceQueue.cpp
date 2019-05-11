#include "deviceQueue.h"
#include "device.h"


DeviceQueue::DeviceQueue(Device *device, uint32_t queueFamilyIndex, uint32_t queueIndex)
{
	_vkGetDeviceQueue = (PFN_vkGetDeviceQueue)vkGetDeviceProcAddr(device->vkHandle, "vkGetDeviceQueue");
	_vkGetDeviceQueue(device->vkHandle, queueFamilyIndex, queueIndex, &vkHandle);
}

DeviceQueue::~DeviceQueue()
{
	vkHandle = VK_NULL_HANDLE;
}

bool DeviceQueue::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

