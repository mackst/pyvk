#pragma once

#ifndef PYVKINIT_H
#define PYVKINIT_H



//#define VK_NO_PROTOTYPES

#if defined(_WIN32)
#define NOMINMAX
#define VK_USE_PLATFORM_WIN32_KHR

	#include <windows.h>

#else
	#include <dlfcn.h>

#endif


#include <vulkan/vulkan.h>


//extern PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
//extern PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;
//
//bool pyVKInitialize(void);


#endif // !PYVKINIT_H