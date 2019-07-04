#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "volk.h"


namespace py = pybind11;



class Device;



#ifndef SCC_H
#define SCC_H



class Semaphore
{
public:
	Semaphore();
	~Semaphore();

	bool isValid();

	VkSemaphore vkHandle = VK_NULL_HANDLE;
	Device *_device = nullptr;
};


class Fence
{
public:
	Fence();
	~Fence();

	bool isValid();

	VkFence vkHandle = VK_NULL_HANDLE;
	Device *_device = nullptr;
};



#endif // !SCC_h

