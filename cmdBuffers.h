#pragma once


#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "volk.h"


namespace py = pybind11;


class Device;


#ifndef CMDBUFFERS_H
#define CMDBUFFERS_H


class CommandPool
{
public:
	CommandPool();
	CommandPool(Device *device, VkCommandPoolCreateInfo &createInfo);
	~CommandPool();

	bool reset(VkCommandPoolResetFlags flags=0);

	bool isValid();

	VkCommandPool vkHandle = VK_NULL_HANDLE;
	Device *_device = nullptr;

};


class CommandBuffer
{
public:
	CommandBuffer();
	~CommandBuffer();

	bool isValid();

	VkCommandBuffer vkHandle = VK_NULL_HANDLE;
	//VkCommandPool pool = VK_NULL_HANDLE;
	Device *_device = nullptr;
	CommandPool *_cmdPool = nullptr;

};


#endif // !CMDBUFFERS_H


