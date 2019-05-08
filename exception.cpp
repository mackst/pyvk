#include "exception.h"


void checkVKResult(VkResult result)
{
	if (result == VK_SUCCESS)
		return;
	else if (result == VK_ERROR_OUT_OF_DEVICE_MEMORY)
		throw OutOfDeviceMemory("Out of device memory.");
	else if (result == VK_ERROR_OUT_OF_HOST_MEMORY)
		throw OutOfHostMemory("Out of host memory.");
	else if (result == VK_ERROR_INITIALIZATION_FAILED)
		throw InitializationFailed("Initialization Failed.");
	else if (result == VK_ERROR_LAYER_NOT_PRESENT)
		throw LayerNotPresent("Layer not present.");
	else if (result == VK_ERROR_EXTENSION_NOT_PRESENT)
		throw ExtensionNotPresent("Extension Not Present.");
	else if (result == VK_ERROR_INCOMPATIBLE_DRIVER)
		throw IncompatibleDriver("Incompatible Driver.");
	else
		return;
}
