#include "extensions.h"
#include "instance.h"
#include "exception.h"
#include "vktypes.h"


py::function DebugUtilsMessengerEXT::pycallback;


DebugUtilsMessengerEXT::DebugUtilsMessengerEXT()
{
}

DebugUtilsMessengerEXT::DebugUtilsMessengerEXT(VkInstance &instance, int messageSeverity, int messageType, py::function userCallback) : _instance(instance)
{
	_vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
	_vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT");

	if (_vkCreateDebugUtilsMessengerEXT == nullptr || _vkDestroyDebugUtilsMessengerEXT == nullptr)
		throw ExtensionNotPresent("VK_EXT_debug_report not present.");


	DebugUtilsMessengerEXT::pycallback = userCallback;

	VkDebugUtilsMessengerCreateInfoEXT _createInfo = {};
	_createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	_createInfo.messageSeverity = messageSeverity;
	_createInfo.messageType = messageType;
	_createInfo.pfnUserCallback = DebugUtilsMessengerEXT::debugCallback;

	checkVKResult(_vkCreateDebugUtilsMessengerEXT(_instance, &_createInfo, nullptr, &vkHandle));
	_isValid = true;
}

DebugUtilsMessengerEXT::~DebugUtilsMessengerEXT()
{
	destroy();
}

void DebugUtilsMessengerEXT::destroy()
{
	if (vkHandle != VK_NULL_HANDLE)
	{
		_vkDestroyDebugUtilsMessengerEXT(_instance, vkHandle, nullptr);
		py::print("DebugUtilsMessengerEXT destroyed.");
		DebugUtilsMessengerEXT::pycallback = {};
		_instance = VK_NULL_HANDLE;
		vkHandle = VK_NULL_HANDLE;
		_isValid = false;
	}
}

bool DebugUtilsMessengerEXT::isValid()
{
	return _isValid;
}


VKAPI_ATTR VkBool32 VKAPI_CALL DebugUtilsMessengerEXT::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData, void * pUserData)
{
	py::dict data;
	//data["cmdBufLabelCount"] = pCallbackData->cmdBufLabelCount;
	data["message"] = pCallbackData->pMessage;
	data["messageIdName"] = pCallbackData->pMessageIdName;

	DebugUtilsMessengerEXT::pycallback(messageSeverity, messageType, data);
	return VK_FALSE;
}

SurfaceKHR::SurfaceKHR()
{
}

SurfaceKHR::SurfaceKHR(VkInstance & instance, py::dict createInfo) : _instance(instance)
{
	_createWin32Surface = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(_instance, "vkCreateWin32SurfaceKHR");
	_destroySurfaceKHR = (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(_instance, "vkDestroySurfaceKHR");

	create(createInfo);
}

SurfaceKHR::~SurfaceKHR()
{
	destroy();
}

bool SurfaceKHR::create(py::dict createInfo)
{

#if defined(_WIN32)
	if (_createWin32Surface == nullptr)
		throw ExtensionNotPresent("VK_KHR_win32_surface not present.");

	HWND winId = (HWND)createInfo["winId"].cast<LONG>();
	HINSTANCE hinstance = (HINSTANCE)GetWindowLongA(winId, -6);

	VkWin32SurfaceCreateInfoKHR _createInfo = {};
	_createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	_createInfo.hinstance = hinstance;
	_createInfo.hwnd = winId;

	checkVKResult(_createWin32Surface(_instance, &_createInfo, nullptr, &vkHandle));

#else
	throw std::runtime_error("Unsupported platform.");
#endif


	return false;
}

void SurfaceKHR::destroy()
{
	if (isValid())
	{
		_destroySurfaceKHR(_instance, vkHandle, nullptr);
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

SwapchainKHR::SwapchainKHR(Device * device, py::dict createInfo) : _device(device)
{
	_vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)vkGetDeviceProcAddr(_device->vkHandle, "vkCreateSwapchainKHR");
	if (_vkCreateSwapchainKHR == nullptr)
		throw ExtensionNotPresent("VK_KHR_swapchain not present");

	_vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR)vkGetDeviceProcAddr(_device->vkHandle, "vkDestroySwapchainKHR");
	_vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)vkGetDeviceProcAddr(_device->vkHandle, "vkGetSwapchainImagesKHR");

	_surface = createInfo["surface"].cast<SurfaceKHR*>();
	std::vector<uint32_t> queueFamilyIndices = createInfo["queueFamilyIndices"].cast<std::vector<uint32_t>>();
	
	//VkSwapchainKHR oldSwapchain = VK_NULL_HANDLE;
	SwapchainKHR swapchain;
	if (createInfo.contains("oldSwapchain"))
	{
		auto osc = createInfo["oldSwapchain"];
		if (!osc.is_none())
		{
			swapchain = createInfo["oldSwapchain"].cast<SwapchainKHR>();
		}
	}

	VkSwapchainCreateInfoKHR _createInfo = {};
	_createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	_createInfo.surface = _surface->vkHandle;
	_createInfo.minImageCount = createInfo["minImageCount"].cast<uint32_t>();
	_createInfo.imageFormat = createInfo["imageFormat"].cast<VkFormat>();
	_createInfo.imageColorSpace = createInfo["imageColorSpace"].cast<VkColorSpaceKHR>();
	_createInfo.imageExtent = createInfo["imageExtent"].cast<VkExtent2D>();
	_createInfo.imageArrayLayers = createInfo["imageArrayLayers"].cast<uint32_t>();
	_createInfo.imageUsage = createInfo["imageUsage"].cast<VkImageUsageFlagBits>();
	_createInfo.imageSharingMode = createInfo["imageSharingMode"].cast<VkSharingMode>();
	_createInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilyIndices.size());
	_createInfo.pQueueFamilyIndices = queueFamilyIndices.data();
	_createInfo.preTransform = createInfo["preTransform"].cast<VkSurfaceTransformFlagBitsKHR>();
	_createInfo.compositeAlpha = createInfo["compositeAlpha"].cast<VkCompositeAlphaFlagBitsKHR>();
	_createInfo.presentMode = createInfo["presentMode"].cast<VkPresentModeKHR>();
	_createInfo.clipped = createInfo["clipped"].cast<VkBool32>();
	
	if (swapchain.isValid())
		_createInfo.oldSwapchain = swapchain.vkHandle;
	else
		_createInfo.oldSwapchain = VK_NULL_HANDLE;

	checkVKResult(_vkCreateSwapchainKHR(_device->vkHandle, &_createInfo, nullptr, &vkHandle));
}

SwapchainKHR::~SwapchainKHR()
{
	if (isValid())
	{
		_vkDestroySwapchainKHR(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
		_surface = nullptr;
	}
}

bool SwapchainKHR::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

py::list SwapchainKHR::getImagesKHR()
{
	py::list images;
	if (_device == nullptr || !isValid() || _vkGetSwapchainImagesKHR == nullptr)
		return images;

	uint32_t count;
	checkVKResult(_vkGetSwapchainImagesKHR(_device->vkHandle, vkHandle, &count, nullptr));

	std::vector<VkImage> _images(count);
	checkVKResult(_vkGetSwapchainImagesKHR(_device->vkHandle, vkHandle, &count, _images.data()));

	for (auto item : _images)
	{
		Image im;
		im.vkHandle = item;
		images.append(im);
	}

	return images;
}
