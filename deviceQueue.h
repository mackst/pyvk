#pragma once
#include "volk.h"


class Device;


#ifndef DEVICEQUEUE_H
#define DEVICEQUEUE_H






class DeviceQueue
{
public:
	DeviceQueue(Device *device, uint32_t queueFamilyIndex, uint32_t queueIndex);
	~DeviceQueue();

	bool isValid();


	VkQueue vkHandle = VK_NULL_HANDLE;
private:

	PFN_vkGetDeviceQueue _vkGetDeviceQueue = nullptr;
};


#endif // !DEVICEQUEUE_H

