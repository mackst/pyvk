#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "volk.h"


namespace py = pybind11;


class Device;
class DeviceMemory;
class BufferCreateInfo;
class CreateBufferViewInfo;


#ifndef BUFFERS_H
#define BUFFERS_H



class Buffer
{
public:
	Buffer();
	Buffer(Device *device, BufferCreateInfo &info);
	~Buffer();

	VkMemoryRequirements* getMemoryRequirements();
	Buffer* bind(DeviceMemory *memory, VkDeviceSize memoryOffset = 0);

	bool isValid();

	VkBuffer vkHandle = VK_NULL_HANDLE;
	Device *_device = nullptr;
};


class BufferView
{
public:
	BufferView();
	BufferView(Device *device, CreateBufferViewInfo &info);
	~BufferView();

	bool isValid();

	VkBufferView vkHandle = VK_NULL_HANDLE;
	Device *_device = nullptr;
};




#endif // !BUFFERS_H

