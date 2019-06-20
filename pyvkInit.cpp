#include "pyvkInit.h"



//bool pyVKInitialize(void)
//{
//#if defined(_WIN32)
//	HMODULE module = LoadLibraryA("vulkan-1.dll");
//	if (!module)
//		return false;
//
//	// note: function pointer is cast through void function pointer to silence cast-function-type warning on gcc8
//	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)(void(*)(void))GetProcAddress(module, "vkGetInstanceProcAddr");
//#elif defined(__APPLE__)
//	void* module = dlopen("libvulkan.dylib", RTLD_NOW | RTLD_LOCAL);
//	if (!module)
//		module = dlopen("libvulkan.dylib.1", RTLD_NOW | RTLD_LOCAL);
//	if (!module)
//		module = dlopen("libMoltenVK.dylib", RTLD_NOW | RTLD_LOCAL);
//	if (!module)
//		return false;
//
//	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)dlsym(module, "vkGetInstanceProcAddr");
//#else
//	void* module = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
//	if (!module)
//		module = dlopen("libvulkan.so.1", RTLD_NOW | RTLD_LOCAL);
//	if (!module)
//		return false;
//
//	vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)dlsym(module, "vkGetInstanceProcAddr");
//#endif
//
//	return true;
//}

