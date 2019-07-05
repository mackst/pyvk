#include "extensions.h"
#include "instance.h"
#include "exception.h"
#include "image.h"


DebugUtilsMessengerEXT::DebugUtilsMessengerEXT()
{
}

DebugUtilsMessengerEXT::DebugUtilsMessengerEXT(VkInstance & instance, DebugUtilsMessengerCreateInfoEXT & info)
	: _instance(instance), _createInfo(info)
{
	if (vkCreateDebugUtilsMessengerEXT == nullptr || vkDestroyDebugUtilsMessengerEXT == nullptr)
		throw ExtensionNotPresent("VK_EXT_debug_report not present.");

	VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
	_createInfo.getVKStruct(&createInfo);

	checkVKResult(vkCreateDebugUtilsMessengerEXT(_instance, &createInfo, nullptr, &vkHandle));
	_isValid = true;
}

DebugUtilsMessengerEXT::~DebugUtilsMessengerEXT()
{
	destroy();
}

void DebugUtilsMessengerEXT::destroy()
{
	if (isValid())
	{
		vkDestroyDebugUtilsMessengerEXT(_instance, vkHandle, nullptr);
		//py::print("DebugUtilsMessengerEXT destroyed.");
		_createInfo = {};
		_instance = VK_NULL_HANDLE;
		vkHandle = VK_NULL_HANDLE;
		_isValid = false;
	}
}

bool DebugUtilsMessengerEXT::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}



SurfaceKHR::SurfaceKHR()
{
}

SurfaceKHR::SurfaceKHR(VkInstance & instance, long winId) : _instance(instance)
{
	create(winId);
}

SurfaceKHR::~SurfaceKHR()
{
	destroy();
}

bool SurfaceKHR::create(long winId)
{

#if defined(_WIN32)
	if (vkCreateWin32SurfaceKHR == nullptr)
		throw ExtensionNotPresent("VK_KHR_win32_surface not present.");

	HWND _winId = (HWND)winId;
	HINSTANCE hinstance = (HINSTANCE)GetWindowLongA(_winId, -6);

	VkWin32SurfaceCreateInfoKHR _createInfo = {};
	_createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	_createInfo.hinstance = hinstance;
	_createInfo.hwnd = _winId;

	checkVKResult(vkCreateWin32SurfaceKHR(_instance, &_createInfo, nullptr, &vkHandle));

#else
	throw std::runtime_error("Unsupported platform.");
#endif


	return false;
}

void SurfaceKHR::destroy()
{
	if (isValid())
	{
		vkDestroySurfaceKHR(_instance, vkHandle, nullptr);
		_instance = VK_NULL_HANDLE;
		vkHandle = VK_NULL_HANDLE;
	}
}

bool SurfaceKHR::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}


SwapchainKHR::SwapchainKHR()
{
}

SwapchainKHR::SwapchainKHR(Device * device, SwapchainCreateInfoKHR &createInfo) : _device(device)
{
	if (_device->table.vkCreateSwapchainKHR == nullptr)
		throw ExtensionNotPresent("VK_KHR_swapchain not present");

	VkSwapchainCreateInfoKHR _createInfo = {};
	createInfo.getVKStruct(&_createInfo);

	checkVKResult(_device->table.vkCreateSwapchainKHR(_device->vkHandle, &_createInfo, nullptr, &vkHandle));
}

SwapchainKHR::~SwapchainKHR()
{
	if (isValid())
	{
		_device->table.vkDestroySwapchainKHR(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
		//_surface = nullptr;
	}
}

bool SwapchainKHR::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

py::list SwapchainKHR::getImagesKHR()
{
	py::list images;
	if (_device == nullptr || !isValid() || _device->table.vkGetSwapchainImagesKHR == nullptr)
		return images;

	uint32_t count;
	checkVKResult(_device->table.vkGetSwapchainImagesKHR(_device->vkHandle, vkHandle, &count, nullptr));

	std::vector<VkImage> _images(count);
	checkVKResult(_device->table.vkGetSwapchainImagesKHR(_device->vkHandle, vkHandle, &count, _images.data()));

	for (auto item : _images)
	{
		Image im;
		im.vkHandle = item;
		images.append(im);
	}

	return images;
}

uint32_t SwapchainKHR::acquireNextImageKHR(uint64_t timeout, Semaphore * semaphore, Fence * fence)
{
	uint32_t imageIndex;
	VkSemaphore _semaphore = VK_NULL_HANDLE;
	if (semaphore != nullptr)
		_semaphore = semaphore->vkHandle;
	VkFence _fence = VK_NULL_HANDLE;
	if (fence != nullptr)
		_fence = fence->vkHandle;
	checkVKResult(_device->table.vkAcquireNextImageKHR(_device->vkHandle, vkHandle, timeout, _semaphore, _fence, &imageIndex));
	return imageIndex;
}
