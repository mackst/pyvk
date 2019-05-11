#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include "instance.h"
#include "deviceQueue.h"
#include "image.h"



PYBIND11_MODULE(_vk, m)
{
	m.doc() = "vulkan for python.";

	py::class_<Instance>(m, "Instance")
		.def(py::init<py::dict>())
		.def("create", &Instance::create)
		.def("destroy", &Instance::destroy)
		.def("createDebugUtilsMessengerEXT", &Instance::createDebugUtilsMessengerEXT, 
			py::arg("messageSeverity"), py::arg("messageType"), py::arg("userCallback"),
			py::return_value_policy::reference)
		.def("createSurface", &Instance::createSurface, py::arg("createInfo"), 
			py::return_value_policy::reference)
		.def("getPhysicalDevices", &Instance::getPhysicalDevices)
		.def_property_readonly("isValid", &Instance::isValid)
		.def_static("version", &Instance::version)
		.def_static("getLayerProperties", &Instance::layerProperties)
		.def_static("getExtensionProperties", &Instance::extensionProperties, py::arg("layerName") = nullptr);

	py::class_<PhysicalDevice> PhysicalDeviceClass(m, "PhysicalDevice");
	PhysicalDeviceClass
		.def(py::init<>())
		.def("getSurfaceSupportKHR", &PhysicalDevice::getSurfaceSupportKHR, py::arg("surface"), py::arg("queueFamilyIndex"))
		.def("getLayerProperties", &PhysicalDevice::layerProperties)
		.def("getExtensionProperties", &PhysicalDevice::extensionProperties, py::arg("layerName") = nullptr)
		.def("getSurfaceCapabilitiesKHR", &PhysicalDevice::getSurfaceCapabilitiesKHR, py::arg("surface"))
		.def("getSurfaceFormatsKHR", &PhysicalDevice::getSurfaceFormatsKHR, py::arg("surface"))
		.def("getSurfacePresentModeKHR", &PhysicalDevice::getSurfacePresentModeKHR, py::arg("surface"))
		.def("__repr__", &PhysicalDevice::toString)
		.def_property_readonly("isValid", &PhysicalDevice::isValid)
		.def_property_readonly("properties", &PhysicalDevice::getProperties)
		.def_property_readonly("queueFamilyProperties", &PhysicalDevice::getQueueFamilyProperties);
	py::enum_<VkPhysicalDeviceType>(PhysicalDeviceClass, "DeviceType")
		.value("CPU", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU)
		.value("OTHER", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_OTHER)
		.value("DISCRETE_GPU", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		.value("INTEGRATED_GPU", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
		.value("VIRTUAL_GPU", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU)
		.export_values();

	py::class_<Device>(m, "Device")
		.def(py::init<PhysicalDevice&, py::dict>(), py::arg("physicalDevice"), py::arg("createInfo"))
		.def("getQueue", &Device::getQueue)
		.def("createSwapchainKHR", &Device::createSwapchainKHR, py::arg("createInfo"))
		.def("getSwapchainImagesKHR", &Device::getSwapchainImagesKHR, py::arg("swapchain"))
		.def_property_readonly("isValid", &Device::isValid);

	py::class_<DeviceQueue>(m, "DeviceQueue")
		.def(py::init<Device*, uint32_t, uint32_t>(), py::arg("device"), py::arg("queueFamilyIndex"), py::arg("queueIndex"))
		.def_property_readonly("isValid", &DeviceQueue::isValid);

	py::class_<SwapchainKHR>(m, "SwapchainKHR")
		.def(py::init<Device*, py::dict>())
		.def("getImagesKHR", &SwapchainKHR::getImagesKHR)
		.def_property_readonly("isValid", &SwapchainKHR::isValid);

	py::class_<Image>(m, "Image")
		.def(py::init<>())
		.def_property_readonly("isValid", &Image::isValid);

	py::class_<VkPhysicalDeviceFeatures>(m, "PhysicalDeviceFeatures")
		.def(py::init<>())
		.def_readwrite("robustBufferAccess", &VkPhysicalDeviceFeatures::robustBufferAccess)
		.def_readwrite("fullDrawIndexUint32", &VkPhysicalDeviceFeatures::fullDrawIndexUint32)
		.def_readwrite("imageCubeArray", &VkPhysicalDeviceFeatures::imageCubeArray)
		.def_readwrite("independentBlend", &VkPhysicalDeviceFeatures::independentBlend)
		.def_readwrite("geometryShader", &VkPhysicalDeviceFeatures::geometryShader)
		.def_readwrite("tessellationShader", &VkPhysicalDeviceFeatures::tessellationShader)
		.def_readwrite("sampleRateShading", &VkPhysicalDeviceFeatures::sampleRateShading)
		.def_readwrite("dualSrcBlend", &VkPhysicalDeviceFeatures::dualSrcBlend)
		.def_readwrite("logicOp", &VkPhysicalDeviceFeatures::logicOp)
		.def_readwrite("multiDrawIndirect", &VkPhysicalDeviceFeatures::multiDrawIndirect)
		.def_readwrite("drawIndirectFirstInstance", &VkPhysicalDeviceFeatures::drawIndirectFirstInstance)
		.def_readwrite("depthClamp", &VkPhysicalDeviceFeatures::depthClamp)
		.def_readwrite("depthBiasClamp", &VkPhysicalDeviceFeatures::depthBiasClamp)
		.def_readwrite("fillModeNonSolid", &VkPhysicalDeviceFeatures::fillModeNonSolid)
		.def_readwrite("depthBounds", &VkPhysicalDeviceFeatures::depthBounds)
		.def_readwrite("wideLines", &VkPhysicalDeviceFeatures::wideLines)
		.def_readwrite("largePoints", &VkPhysicalDeviceFeatures::largePoints)
		.def_readwrite("alphaToOne", &VkPhysicalDeviceFeatures::alphaToOne)
		.def_readwrite("multiViewport", &VkPhysicalDeviceFeatures::multiViewport)
		.def_readwrite("samplerAnisotropy", &VkPhysicalDeviceFeatures::samplerAnisotropy)
		.def_readwrite("textureCompressionETC2", &VkPhysicalDeviceFeatures::textureCompressionETC2)
		.def_readwrite("textureCompressionASTC_LDR", &VkPhysicalDeviceFeatures::textureCompressionASTC_LDR)
		.def_readwrite("textureCompressionBC", &VkPhysicalDeviceFeatures::textureCompressionBC)
		.def_readwrite("occlusionQueryPrecise", &VkPhysicalDeviceFeatures::occlusionQueryPrecise)
		.def_readwrite("pipelineStatisticsQuery", &VkPhysicalDeviceFeatures::pipelineStatisticsQuery)
		.def_readwrite("vertexPipelineStoresAndAtomics", &VkPhysicalDeviceFeatures::vertexPipelineStoresAndAtomics)
		.def_readwrite("fragmentStoresAndAtomics", &VkPhysicalDeviceFeatures::fragmentStoresAndAtomics)
		.def_readwrite("shaderTessellationAndGeometryPointSize", &VkPhysicalDeviceFeatures::shaderTessellationAndGeometryPointSize)
		.def_readwrite("shaderImageGatherExtended", &VkPhysicalDeviceFeatures::shaderImageGatherExtended)
		.def_readwrite("shaderStorageImageExtendedFormats", &VkPhysicalDeviceFeatures::shaderStorageImageExtendedFormats)
		.def_readwrite("shaderStorageImageMultisample", &VkPhysicalDeviceFeatures::shaderStorageImageMultisample)
		.def_readwrite("shaderStorageImageReadWithoutFormat", &VkPhysicalDeviceFeatures::shaderStorageImageReadWithoutFormat)
		.def_readwrite("shaderStorageImageWriteWithoutFormat", &VkPhysicalDeviceFeatures::shaderStorageImageWriteWithoutFormat)
		.def_readwrite("shaderUniformBufferArrayDynamicIndexing", &VkPhysicalDeviceFeatures::shaderUniformBufferArrayDynamicIndexing)
		.def_readwrite("shaderSampledImageArrayDynamicIndexing", &VkPhysicalDeviceFeatures::shaderSampledImageArrayDynamicIndexing)
		.def_readwrite("shaderStorageBufferArrayDynamicIndexing", &VkPhysicalDeviceFeatures::shaderStorageBufferArrayDynamicIndexing)
		.def_readwrite("shaderStorageImageArrayDynamicIndexing", &VkPhysicalDeviceFeatures::shaderStorageImageArrayDynamicIndexing)
		.def_readwrite("shaderClipDistance", &VkPhysicalDeviceFeatures::shaderClipDistance)
		.def_readwrite("shaderCullDistance", &VkPhysicalDeviceFeatures::shaderCullDistance)
		.def_readwrite("shaderFloat64", &VkPhysicalDeviceFeatures::shaderFloat64)
		.def_readwrite("shaderInt64", &VkPhysicalDeviceFeatures::shaderInt64)
		.def_readwrite("shaderInt16", &VkPhysicalDeviceFeatures::shaderInt16)
		.def_readwrite("shaderResourceResidency", &VkPhysicalDeviceFeatures::shaderResourceResidency)
		.def_readwrite("shaderResourceMinLod", &VkPhysicalDeviceFeatures::shaderResourceMinLod)
		.def_readwrite("sparseBinding", &VkPhysicalDeviceFeatures::sparseBinding)
		.def_readwrite("sparseResidencyBuffer", &VkPhysicalDeviceFeatures::sparseResidencyBuffer)
		.def_readwrite("sparseResidencyImage2D", &VkPhysicalDeviceFeatures::sparseResidencyImage2D)
		.def_readwrite("sparseResidencyImage3D", &VkPhysicalDeviceFeatures::sparseResidencyImage3D)
		.def_readwrite("sparseResidency2Samples", &VkPhysicalDeviceFeatures::sparseResidency2Samples)
		.def_readwrite("sparseResidency4Samples", &VkPhysicalDeviceFeatures::sparseResidency4Samples)
		.def_readwrite("sparseResidency8Samples", &VkPhysicalDeviceFeatures::sparseResidency8Samples)
		.def_readwrite("sparseResidency16Samples", &VkPhysicalDeviceFeatures::sparseResidency16Samples)
		.def_readwrite("sparseResidencyAliased", &VkPhysicalDeviceFeatures::sparseResidencyAliased)
		.def_readwrite("variableMultisampleRate", &VkPhysicalDeviceFeatures::variableMultisampleRate)
		.def_readwrite("inheritedQueries", &VkPhysicalDeviceFeatures::inheritedQueries);

	py::class_<VkSurfaceCapabilitiesKHR>(m, "SurfaceCapabilitiesKHR")
		.def(py::init<>())
		.def_readwrite("minImageCount", &VkSurfaceCapabilitiesKHR::minImageCount)
		.def_readwrite("maxImageCount", &VkSurfaceCapabilitiesKHR::maxImageCount)
		.def_readwrite("currentExtent", &VkSurfaceCapabilitiesKHR::currentExtent)
		.def_readwrite("minImageExtent", &VkSurfaceCapabilitiesKHR::minImageExtent)
		.def_readwrite("maxImageExtent", &VkSurfaceCapabilitiesKHR::maxImageExtent)
		.def_readwrite("maxImageArrayLayers", &VkSurfaceCapabilitiesKHR::maxImageArrayLayers)
		.def_readwrite("supportedTransforms", &VkSurfaceCapabilitiesKHR::supportedTransforms)
		.def_readwrite("currentTransform", &VkSurfaceCapabilitiesKHR::currentTransform)
		.def_readwrite("supportedCompositeAlpha", &VkSurfaceCapabilitiesKHR::supportedCompositeAlpha)
		.def_readwrite("supportedUsageFlags", &VkSurfaceCapabilitiesKHR::supportedUsageFlags);

	py::class_<VkSurfaceFormatKHR>(m, "SurfaceFormatKHR")
		.def(py::init<>())
		.def_readwrite("colorSpace", &VkSurfaceFormatKHR::colorSpace)
		.def_readwrite("format", &VkSurfaceFormatKHR::format);

	py::class_<VkOffset2D>(m, "Offset2D")
		.def(py::init<>())
		.def_readwrite("x", &VkOffset2D::x)
		.def_readwrite("y", &VkOffset2D::y);

	py::class_<VkOffset3D>(m, "Offset2D3D")
		.def(py::init<>())
		.def_readwrite("x", &VkOffset3D::x)
		.def_readwrite("y", &VkOffset3D::y)
		.def_readwrite("z", &VkOffset3D::z);

	py::class_<VkExtent2D>(m, "Extent2D")
		.def(py::init<>())
		.def_readwrite("width", &VkExtent2D::width)
		.def_readwrite("height", &VkExtent2D::height);

	py::class_<VkExtent3D>(m, "Extent3D")
		.def(py::init<>())
		.def_readwrite("width", &VkExtent3D::width)
		.def_readwrite("height", &VkExtent3D::height)
		.def_readwrite("depth", &VkExtent3D::depth);

	// enums
	py::enum_<VkQueueFlagBits>(m, "QueueFlagBits", py::arithmetic())
		.value("COMPUTE", VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT)
		.value("GRAPHICS", VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT)
		.value("PROTECTED", VkQueueFlagBits::VK_QUEUE_PROTECTED_BIT)
		.value("SPARSE_BINDING", VkQueueFlagBits::VK_QUEUE_SPARSE_BINDING_BIT)
		.value("TRANSFER", VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT);
	py::enum_<VkSurfaceTransformFlagBitsKHR>(m, "SurfaceTransformFlagBitsKHR", py::arithmetic())
		.value("ROTATE_90_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR)
		.value("ROTATE_270_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
		.value("ROTATE_180_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR)
		.value("INHERIT_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR)
		.value("IDENTITY_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
		.value("HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR)
		.value("HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR)
		.value("HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR)
		.value("HORIZONTAL_MIRROR_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR);
	py::enum_<VkCompositeAlphaFlagBitsKHR>(m, "CompositeAlphaFlagBitsKHR", py::arithmetic())
		.value("INHERIT_BIT_KHR", VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR)
		.value("OPAQUE_BIT_KHR", VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
		.value("POST_MULTIPLIED_BIT_KHR", VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR)
		.value("PRE_MULTIPLIED_BIT_KHR", VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR);
	py::enum_<VkImageUsageFlagBits>(m, "ImageUsageFlagBits", py::arithmetic())
		.value("TRANSIENT_ATTACHMENT_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT)
		.value("TRANSFER_SRC_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
		.value("TRANSFER_DST_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_DST_BIT)
		.value("STORAGE_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_STORAGE_BIT)
		.value("SHADING_RATE_IMAGE_BIT_NV", VkImageUsageFlagBits::VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV)
		.value("SAMPLED_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_SAMPLED_BIT)
		.value("INPUT_ATTACHMENT_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT)
		.value("FRAGMENT_DENSITY_MAP_BIT_EXT", VkImageUsageFlagBits::VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT)
		.value("DEPTH_STENCIL_ATTACHMENT_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
		.value("COLOR_ATTACHMENT_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);
	py::enum_<VkFormat>(m, "Format")
		.value("UNDEFINED", VkFormat::VK_FORMAT_UNDEFINED)
		.value("R4G4_UNORM_PACK8", VkFormat::VK_FORMAT_R4G4_UNORM_PACK8)
		.value("R4G4B4A4_UNORM_PACK16", VkFormat::VK_FORMAT_R4G4B4A4_UNORM_PACK16)
		.value("B4G4R4A4_UNORM_PACK16", VkFormat::VK_FORMAT_B4G4R4A4_UNORM_PACK16)
		.value("R5G6B5_UNORM_PACK16", VkFormat::VK_FORMAT_R5G6B5_UNORM_PACK16)
		.value("B5G6R5_UNORM_PACK16", VkFormat::VK_FORMAT_B5G6R5_UNORM_PACK16)
		.value("R5G5B5A1_UNORM_PACK16", VkFormat::VK_FORMAT_R5G5B5A1_UNORM_PACK16)
		.value("B5G5R5A1_UNORM_PACK16", VkFormat::VK_FORMAT_B5G5R5A1_UNORM_PACK16)
		.value("A1R5G5B5_UNORM_PACK16", VkFormat::VK_FORMAT_A1R5G5B5_UNORM_PACK16)
		.value("R8_UNORM", VkFormat::VK_FORMAT_R8_UNORM)
		.value("R8_SNORM", VkFormat::VK_FORMAT_R8_SNORM)
		.value("R8_USCALED", VkFormat::VK_FORMAT_R8_USCALED)
		.value("R8_SSCALED", VkFormat::VK_FORMAT_R8_SSCALED)
		.value("R8_UINT", VkFormat::VK_FORMAT_R8_UINT)
		.value("R8_SINT", VkFormat::VK_FORMAT_R8_SINT)
		.value("R8_SRGB", VkFormat::VK_FORMAT_R8_SRGB)
		.value("R8G8_UNORM", VkFormat::VK_FORMAT_R8G8_UNORM)
		.value("R8G8_SNORM", VkFormat::VK_FORMAT_R8G8_SNORM)
		.value("R8G8_USCALED", VkFormat::VK_FORMAT_R8G8_USCALED)
		.value("R8G8_SSCALED", VkFormat::VK_FORMAT_R8G8_SSCALED)
		.value("R8G8_UINT", VkFormat::VK_FORMAT_R8G8_UINT)
		.value("R8G8_SINT", VkFormat::VK_FORMAT_R8G8_SINT)
		.value("R8G8_SRGB", VkFormat::VK_FORMAT_R8G8_SRGB)
		.value("R8G8B8_UNORM", VkFormat::VK_FORMAT_R8G8B8_UNORM)
		.value("R8G8B8_SNORM", VkFormat::VK_FORMAT_R8G8B8_SNORM)
		.value("R8G8B8_USCALED", VkFormat::VK_FORMAT_R8G8B8_USCALED)
		.value("R8G8B8_SSCALED", VkFormat::VK_FORMAT_R8G8B8_SSCALED)
		.value("R8G8B8_UINT", VkFormat::VK_FORMAT_R8G8B8_UINT)
		.value("R8G8B8_SINT", VkFormat::VK_FORMAT_R8G8B8_SINT)
		.value("R8G8B8_SRGB", VkFormat::VK_FORMAT_R8G8B8_SRGB)
		.value("B8G8R8_UNORM", VkFormat::VK_FORMAT_B8G8R8_UNORM)
		.value("B8G8R8_SNORM", VkFormat::VK_FORMAT_B8G8R8_SNORM)
		.value("B8G8R8_USCALED", VkFormat::VK_FORMAT_B8G8R8_USCALED)
		.value("B8G8R8_SSCALED", VkFormat::VK_FORMAT_B8G8R8_SSCALED)
		.value("B8G8R8_UINT", VkFormat::VK_FORMAT_B8G8R8_UINT)
		.value("B8G8R8_SINT", VkFormat::VK_FORMAT_B8G8R8_SINT)
		.value("B8G8R8_SRGB", VkFormat::VK_FORMAT_B8G8R8_SRGB)
		.value("R8G8B8A8_UNORM", VkFormat::VK_FORMAT_R8G8B8A8_UNORM)
		.value("R8G8B8A8_SNORM", VkFormat::VK_FORMAT_R8G8B8A8_SNORM)
		.value("R8G8B8A8_USCALED", VkFormat::VK_FORMAT_R8G8B8A8_USCALED)
		.value("R8G8B8A8_SSCALED", VkFormat::VK_FORMAT_R8G8B8A8_SSCALED)
		.value("R8G8B8A8_UINT", VkFormat::VK_FORMAT_R8G8B8A8_UINT)
		.value("R8G8B8A8_SINT", VkFormat::VK_FORMAT_R8G8B8A8_SINT)
		.value("R8G8B8A8_SRGB", VkFormat::VK_FORMAT_R8G8B8A8_SRGB)
		.value("B8G8R8A8_UNORM", VkFormat::VK_FORMAT_B8G8R8A8_UNORM)
		.value("B8G8R8A8_SNORM", VkFormat::VK_FORMAT_B8G8R8A8_SNORM)
		.value("B8G8R8A8_USCALED", VkFormat::VK_FORMAT_B8G8R8A8_USCALED)
		.value("B8G8R8A8_SSCALED", VkFormat::VK_FORMAT_B8G8R8A8_SSCALED)
		.value("B8G8R8A8_UINT", VkFormat::VK_FORMAT_B8G8R8A8_UINT)
		.value("B8G8R8A8_SINT", VkFormat::VK_FORMAT_B8G8R8A8_SINT)
		.value("B8G8R8A8_SRGB", VkFormat::VK_FORMAT_B8G8R8A8_SRGB)
		.value("A8B8G8R8_UNORM_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_UNORM_PACK32)
		.value("A8B8G8R8_SNORM_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_SNORM_PACK32)
		.value("A8B8G8R8_USCALED_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_USCALED_PACK32)
		.value("A8B8G8R8_SSCALED_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_SSCALED_PACK32)
		.value("A8B8G8R8_UINT_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_UINT_PACK32)
		.value("A8B8G8R8_SINT_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_SINT_PACK32)
		.value("A8B8G8R8_SRGB_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_SRGB_PACK32)
		.value("A2R10G10B10_UNORM_PACK32", VkFormat::VK_FORMAT_A2R10G10B10_UNORM_PACK32)
		.value("A2R10G10B10_SNORM_PACK32", VkFormat::VK_FORMAT_A2R10G10B10_SNORM_PACK32)
		.value("A2R10G10B10_USCALED_PACK32", VkFormat::VK_FORMAT_A2R10G10B10_USCALED_PACK32)
		.value("A2R10G10B10_SSCALED_PACK32", VkFormat::VK_FORMAT_A2R10G10B10_SSCALED_PACK32)
		.value("A2R10G10B10_UINT_PACK32", VkFormat::VK_FORMAT_A2R10G10B10_UINT_PACK32)
		.value("A2R10G10B10_SINT_PACK32", VkFormat::VK_FORMAT_A2R10G10B10_SINT_PACK32)
		.value("A2B10G10R10_UNORM_PACK32", VkFormat::VK_FORMAT_A2B10G10R10_UNORM_PACK32)
		.value("A2B10G10R10_SNORM_PACK32", VkFormat::VK_FORMAT_A2B10G10R10_SNORM_PACK32)
		.value("A2B10G10R10_USCALED_PACK32", VkFormat::VK_FORMAT_A2B10G10R10_USCALED_PACK32)
		.value("A2B10G10R10_SSCALED_PACK32", VkFormat::VK_FORMAT_A2B10G10R10_SSCALED_PACK32)
		.value("A2B10G10R10_UINT_PACK32", VkFormat::VK_FORMAT_A2B10G10R10_UINT_PACK32)
		.value("A2B10G10R10_SINT_PACK32", VkFormat::VK_FORMAT_A2B10G10R10_SINT_PACK32)
		.value("R16_UNORM", VkFormat::VK_FORMAT_R16_UNORM)
		.value("R16_SNORM", VkFormat::VK_FORMAT_R16_SNORM)
		.value("R16_USCALED", VkFormat::VK_FORMAT_R16_USCALED)
		.value("R16_SSCALED", VkFormat::VK_FORMAT_R16_SSCALED)
		.value("R16_UINT", VkFormat::VK_FORMAT_R16_UINT)
		.value("R16_SINT", VkFormat::VK_FORMAT_R16_SINT)
		.value("R16_SFLOAT", VkFormat::VK_FORMAT_R16_SFLOAT)
		.value("R16G16_UNORM", VkFormat::VK_FORMAT_R16G16_UNORM)
		.value("R16G16_SNORM", VkFormat::VK_FORMAT_R16G16_SNORM)
		.value("R16G16_USCALED", VkFormat::VK_FORMAT_R16G16_USCALED)
		.value("R16G16_SSCALED", VkFormat::VK_FORMAT_R16G16_SSCALED)
		.value("R16G16_UINT", VkFormat::VK_FORMAT_R16G16_UINT)
		.value("R16G16_SINT", VkFormat::VK_FORMAT_R16G16_SINT)
		.value("R16G16_SFLOAT", VkFormat::VK_FORMAT_R16G16_SFLOAT)
		.value("R16G16B16_UNORM", VkFormat::VK_FORMAT_R16G16B16_UNORM)
		.value("R16G16B16_SNORM", VkFormat::VK_FORMAT_R16G16B16_SNORM)
		.value("R16G16B16_USCALED", VkFormat::VK_FORMAT_R16G16B16_USCALED)
		.value("R16G16B16_SSCALED", VkFormat::VK_FORMAT_R16G16B16_SSCALED)
		.value("R16G16B16_UINT", VkFormat::VK_FORMAT_R16G16B16_UINT)
		.value("R16G16B16_SINT", VkFormat::VK_FORMAT_R16G16B16_SINT)
		.value("R16G16B16_SFLOAT", VkFormat::VK_FORMAT_R16G16B16_SFLOAT)
		.value("R16G16B16A16_UNORM", VkFormat::VK_FORMAT_R16G16B16A16_UNORM)
		.value("R16G16B16A16_SNORM", VkFormat::VK_FORMAT_R16G16B16A16_SNORM)
		.value("R16G16B16A16_USCALED", VkFormat::VK_FORMAT_R16G16B16A16_USCALED)
		.value("R16G16B16A16_SSCALED", VkFormat::VK_FORMAT_R16G16B16A16_SSCALED)
		.value("R16G16B16A16_UINT", VkFormat::VK_FORMAT_R16G16B16A16_UINT)
		.value("R16G16B16A16_SINT", VkFormat::VK_FORMAT_R16G16B16A16_SINT)
		.value("R16G16B16A16_SFLOAT", VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT)
		.value("R32_UINT", VkFormat::VK_FORMAT_R32_UINT)
		.value("R32_SINT", VkFormat::VK_FORMAT_R32_SINT)
		.value("R32_SFLOAT", VkFormat::VK_FORMAT_R32_SFLOAT)
		.value("R32G32_UINT", VkFormat::VK_FORMAT_R32G32_UINT)
		.value("R32G32_SINT", VkFormat::VK_FORMAT_R32G32_SINT)
		.value("R32G32_SFLOAT", VkFormat::VK_FORMAT_R32G32_SFLOAT)
		.value("R32G32B32_UINT", VkFormat::VK_FORMAT_R32G32B32_UINT)
		.value("R32G32B32_SINT", VkFormat::VK_FORMAT_R32G32B32_SINT)
		.value("R32G32B32_SFLOAT", VkFormat::VK_FORMAT_R32G32B32_SFLOAT)
		.value("R32G32B32A32_UINT", VkFormat::VK_FORMAT_R32G32B32A32_UINT)
		.value("R32G32B32A32_SINT", VkFormat::VK_FORMAT_R32G32B32A32_SINT)
		.value("R32G32B32A32_SFLOAT", VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT)
		.value("R64_UINT", VkFormat::VK_FORMAT_R64_UINT)
		.value("R64_SINT", VkFormat::VK_FORMAT_R64_SINT)
		.value("R64_SFLOAT", VkFormat::VK_FORMAT_R64_SFLOAT)
		.value("R64G64_UINT", VkFormat::VK_FORMAT_R64G64_UINT)
		.value("R64G64_SINT", VkFormat::VK_FORMAT_R64G64_SINT)
		.value("R64G64_SFLOAT", VkFormat::VK_FORMAT_R64G64_SFLOAT)
		.value("R64G64B64_UINT", VkFormat::VK_FORMAT_R64G64B64_UINT)
		.value("R64G64B64_SINT", VkFormat::VK_FORMAT_R64G64B64_SINT)
		.value("R64G64B64_SFLOAT", VkFormat::VK_FORMAT_R64G64B64_SFLOAT)
		.value("R64G64B64A64_UINT", VkFormat::VK_FORMAT_R64G64B64A64_UINT)
		.value("R64G64B64A64_SINT", VkFormat::VK_FORMAT_R64G64B64A64_SINT)
		.value("R64G64B64A64_SFLOAT", VkFormat::VK_FORMAT_R64G64B64A64_SFLOAT)
		.value("B10G11R11_UFLOAT_PACK32", VkFormat::VK_FORMAT_B10G11R11_UFLOAT_PACK32)
		.value("E5B9G9R9_UFLOAT_PACK32", VkFormat::VK_FORMAT_E5B9G9R9_UFLOAT_PACK32)
		.value("D16_UNORM", VkFormat::VK_FORMAT_D16_UNORM)
		.value("X8_D24_UNORM_PACK32", VkFormat::VK_FORMAT_X8_D24_UNORM_PACK32)
		.value("D32_SFLOAT", VkFormat::VK_FORMAT_D32_SFLOAT)
		.value("S8_UINT", VkFormat::VK_FORMAT_S8_UINT)
		.value("D16_UNORM_S8_UINT", VkFormat::VK_FORMAT_D16_UNORM_S8_UINT)
		.value("D24_UNORM_S8_UINT", VkFormat::VK_FORMAT_D24_UNORM_S8_UINT)
		.value("D32_SFLOAT_S8_UINT", VkFormat::VK_FORMAT_D32_SFLOAT_S8_UINT)
		.value("BC1_RGB_UNORM_BLOCK", VkFormat::VK_FORMAT_BC1_RGB_UNORM_BLOCK)
		.value("BC1_RGB_SRGB_BLOCK", VkFormat::VK_FORMAT_BC1_RGB_SRGB_BLOCK)
		.value("BC1_RGBA_UNORM_BLOCK", VkFormat::VK_FORMAT_BC1_RGBA_UNORM_BLOCK)
		.value("BC1_RGBA_SRGB_BLOCK", VkFormat::VK_FORMAT_BC1_RGBA_SRGB_BLOCK)
		.value("BC2_UNORM_BLOCK", VkFormat::VK_FORMAT_BC2_UNORM_BLOCK)
		.value("BC2_SRGB_BLOCK", VkFormat::VK_FORMAT_BC2_SRGB_BLOCK)
		.value("BC3_UNORM_BLOCK", VkFormat::VK_FORMAT_BC3_UNORM_BLOCK)
		.value("BC3_SRGB_BLOCK", VkFormat::VK_FORMAT_BC3_SRGB_BLOCK)
		.value("BC4_UNORM_BLOCK", VkFormat::VK_FORMAT_BC4_UNORM_BLOCK)
		.value("BC4_SNORM_BLOCK", VkFormat::VK_FORMAT_BC4_SNORM_BLOCK)
		.value("BC5_UNORM_BLOCK", VkFormat::VK_FORMAT_BC5_UNORM_BLOCK)
		.value("BC5_SNORM_BLOCK", VkFormat::VK_FORMAT_BC5_SNORM_BLOCK)
		.value("BC6H_UFLOAT_BLOCK", VkFormat::VK_FORMAT_BC6H_UFLOAT_BLOCK)
		.value("BC6H_SFLOAT_BLOCK", VkFormat::VK_FORMAT_BC6H_SFLOAT_BLOCK)
		.value("BC7_UNORM_BLOCK", VkFormat::VK_FORMAT_BC7_UNORM_BLOCK)
		.value("BC7_SRGB_BLOCK", VkFormat::VK_FORMAT_BC7_SRGB_BLOCK)
		.value("ETC2_R8G8B8_UNORM_BLOCK", VkFormat::VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK)
		.value("ETC2_R8G8B8_SRGB_BLOCK", VkFormat::VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK)
		.value("ETC2_R8G8B8A1_UNORM_BLOCK", VkFormat::VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK)
		.value("ETC2_R8G8B8A1_SRGB_BLOCK", VkFormat::VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK)
		.value("ETC2_R8G8B8A8_UNORM_BLOCK", VkFormat::VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK)
		.value("ETC2_R8G8B8A8_SRGB_BLOCK", VkFormat::VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK)
		.value("EAC_R11_UNORM_BLOCK", VkFormat::VK_FORMAT_EAC_R11_UNORM_BLOCK)
		.value("EAC_R11_SNORM_BLOCK", VkFormat::VK_FORMAT_EAC_R11_SNORM_BLOCK)
		.value("EAC_R11G11_UNORM_BLOCK", VkFormat::VK_FORMAT_EAC_R11G11_UNORM_BLOCK)
		.value("EAC_R11G11_SNORM_BLOCK", VkFormat::VK_FORMAT_EAC_R11G11_SNORM_BLOCK)
		.value("ASTC_4x4_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_4x4_UNORM_BLOCK)
		.value("ASTC_4x4_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_4x4_SRGB_BLOCK)
		.value("ASTC_5x4_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_5x4_UNORM_BLOCK)
		.value("ASTC_5x4_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_5x4_SRGB_BLOCK)
		.value("ASTC_5x5_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_5x5_UNORM_BLOCK)
		.value("ASTC_5x5_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_5x5_SRGB_BLOCK)
		.value("ASTC_6x5_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_6x5_UNORM_BLOCK)
		.value("ASTC_6x5_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_6x5_SRGB_BLOCK)
		.value("ASTC_6x6_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_6x6_UNORM_BLOCK)
		.value("ASTC_6x6_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_6x6_SRGB_BLOCK)
		.value("ASTC_8x5_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_8x5_UNORM_BLOCK)
		.value("ASTC_8x5_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_8x5_SRGB_BLOCK)
		.value("ASTC_8x6_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_8x6_UNORM_BLOCK)
		.value("ASTC_8x6_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_8x6_SRGB_BLOCK)
		.value("ASTC_8x8_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_8x8_UNORM_BLOCK)
		.value("ASTC_8x8_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_8x8_SRGB_BLOCK)
		.value("ASTC_10x5_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_10x5_UNORM_BLOCK)
		.value("ASTC_10x5_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_10x5_SRGB_BLOCK)
		.value("ASTC_10x6_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_10x6_UNORM_BLOCK)
		.value("ASTC_10x6_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_10x6_SRGB_BLOCK)
		.value("ASTC_10x8_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_10x8_UNORM_BLOCK)
		.value("ASTC_10x8_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_10x8_SRGB_BLOCK)
		.value("ASTC_10x10_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_10x10_UNORM_BLOCK)
		.value("ASTC_10x10_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_10x10_SRGB_BLOCK)
		.value("ASTC_12x10_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_12x10_UNORM_BLOCK)
		.value("ASTC_12x10_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_12x10_SRGB_BLOCK)
		.value("ASTC_12x12_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_12x12_UNORM_BLOCK)
		.value("ASTC_12x12_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_12x12_SRGB_BLOCK)
		.value("G8B8G8R8_422_UNORM", VkFormat::VK_FORMAT_G8B8G8R8_422_UNORM)
		.value("B8G8R8G8_422_UNORM", VkFormat::VK_FORMAT_B8G8R8G8_422_UNORM)
		.value("G8_B8_R8_3PLANE_420_UNORM", VkFormat::VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM)
		.value("G8_B8R8_2PLANE_420_UNORM", VkFormat::VK_FORMAT_G8_B8R8_2PLANE_420_UNORM)
		.value("G8_B8_R8_3PLANE_422_UNORM", VkFormat::VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM)
		.value("G8_B8R8_2PLANE_422_UNORM", VkFormat::VK_FORMAT_G8_B8R8_2PLANE_422_UNORM)
		.value("G8_B8_R8_3PLANE_444_UNORM", VkFormat::VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM)
		.value("R10X6_UNORM_PACK16", VkFormat::VK_FORMAT_R10X6_UNORM_PACK16)
		.value("R10X6G10X6_UNORM_2PACK16", VkFormat::VK_FORMAT_R10X6G10X6_UNORM_2PACK16)
		.value("R10X6G10X6B10X6A10X6_UNORM_4PACK16", VkFormat::VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16)
		.value("G10X6B10X6G10X6R10X6_422_UNORM_4PACK16", VkFormat::VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16)
		.value("B10X6G10X6R10X6G10X6_422_UNORM_4PACK16", VkFormat::VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16)
		.value("G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16", VkFormat::VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16)
		.value("G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16", VkFormat::VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16)
		.value("G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16", VkFormat::VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16)
		.value("G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16", VkFormat::VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16)
		.value("G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16", VkFormat::VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16)
		.value("R12X4_UNORM_PACK16", VkFormat::VK_FORMAT_R12X4_UNORM_PACK16)
		.value("R12X4G12X4_UNORM_2PACK16", VkFormat::VK_FORMAT_R12X4G12X4_UNORM_2PACK16)
		.value("R12X4G12X4B12X4A12X4_UNORM_4PACK16", VkFormat::VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16)
		.value("G12X4B12X4G12X4R12X4_422_UNORM_4PACK16", VkFormat::VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16)
		.value("B12X4G12X4R12X4G12X4_422_UNORM_4PACK16", VkFormat::VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16)
		.value("G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16", VkFormat::VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16)
		.value("G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16", VkFormat::VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16)
		.value("G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16", VkFormat::VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16)
		.value("G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16", VkFormat::VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16)
		.value("G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16", VkFormat::VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16)
		.value("G16B16G16R16_422_UNORM", VkFormat::VK_FORMAT_G16B16G16R16_422_UNORM)
		.value("B16G16R16G16_422_UNORM", VkFormat::VK_FORMAT_B16G16R16G16_422_UNORM)
		.value("G16_B16_R16_3PLANE_420_UNORM", VkFormat::VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM)
		.value("G16_B16R16_2PLANE_420_UNORM", VkFormat::VK_FORMAT_G16_B16R16_2PLANE_420_UNORM)
		.value("G16_B16_R16_3PLANE_422_UNORM", VkFormat::VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM)
		.value("G16_B16R16_2PLANE_422_UNORM", VkFormat::VK_FORMAT_G16_B16R16_2PLANE_422_UNORM)
		.value("G16_B16_R16_3PLANE_444_UNORM", VkFormat::VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM)
		.value("PVRTC1_2BPP_UNORM_BLOCK_IMG", VkFormat::VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG)
		.value("PVRTC1_4BPP_UNORM_BLOCK_IMG", VkFormat::VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG)
		.value("PVRTC2_2BPP_UNORM_BLOCK_IMG", VkFormat::VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG)
		.value("PVRTC2_4BPP_UNORM_BLOCK_IMG", VkFormat::VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG)
		.value("PVRTC1_2BPP_SRGB_BLOCK_IMG", VkFormat::VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG)
		.value("PVRTC1_4BPP_SRGB_BLOCK_IMG", VkFormat::VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG)
		.value("PVRTC2_2BPP_SRGB_BLOCK_IMG", VkFormat::VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG)
		.value("PVRTC2_4BPP_SRGB_BLOCK_IMG", VkFormat::VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG)
		.value("G8B8G8R8_422_UNORM_KHR", VkFormat::VK_FORMAT_G8B8G8R8_422_UNORM_KHR)
		.value("B8G8R8G8_422_UNORM_KHR", VkFormat::VK_FORMAT_B8G8R8G8_422_UNORM_KHR)
		.value("G8_B8_R8_3PLANE_420_UNORM_KHR", VkFormat::VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM_KHR)
		.value("G8_B8R8_2PLANE_420_UNORM_KHR", VkFormat::VK_FORMAT_G8_B8R8_2PLANE_420_UNORM_KHR)
		.value("G8_B8_R8_3PLANE_422_UNORM_KHR", VkFormat::VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM_KHR)
		.value("G8_B8R8_2PLANE_422_UNORM_KHR", VkFormat::VK_FORMAT_G8_B8R8_2PLANE_422_UNORM_KHR)
		.value("G8_B8_R8_3PLANE_444_UNORM_KHR", VkFormat::VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM_KHR)
		.value("R10X6_UNORM_PACK16_KHR", VkFormat::VK_FORMAT_R10X6_UNORM_PACK16_KHR)
		.value("R10X6G10X6_UNORM_2PACK16_KHR", VkFormat::VK_FORMAT_R10X6G10X6_UNORM_2PACK16_KHR)
		.value("R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR", VkFormat::VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR)
		.value("G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR", VkFormat::VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR)
		.value("B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR", VkFormat::VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR)
		.value("G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR", VkFormat::VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR)
		.value("G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR", VkFormat::VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR)
		.value("G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR", VkFormat::VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR)
		.value("G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR", VkFormat::VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR)
		.value("G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR", VkFormat::VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR)
		.value("R12X4_UNORM_PACK16_KHR", VkFormat::VK_FORMAT_R12X4_UNORM_PACK16_KHR)
		.value("R12X4G12X4_UNORM_2PACK16_KHR", VkFormat::VK_FORMAT_R12X4G12X4_UNORM_2PACK16_KHR)
		.value("R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR", VkFormat::VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR)
		.value("G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR", VkFormat::VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR)
		.value("B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR", VkFormat::VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR)
		.value("G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR", VkFormat::VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR)
		.value("G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR", VkFormat::VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR)
		.value("G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR", VkFormat::VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR)
		.value("G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR", VkFormat::VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR)
		.value("G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR", VkFormat::VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR)
		.value("G16B16G16R16_422_UNORM_KHR", VkFormat::VK_FORMAT_G16B16G16R16_422_UNORM_KHR)
		.value("B16G16R16G16_422_UNORM_KHR", VkFormat::VK_FORMAT_B16G16R16G16_422_UNORM_KHR)
		.value("G16_B16_R16_3PLANE_420_UNORM_KHR", VkFormat::VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM_KHR)
		.value("G16_B16R16_2PLANE_420_UNORM_KHR", VkFormat::VK_FORMAT_G16_B16R16_2PLANE_420_UNORM_KHR)
		.value("G16_B16_R16_3PLANE_422_UNORM_KHR", VkFormat::VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM_KHR)
		.value("G16_B16R16_2PLANE_422_UNORM_KHR", VkFormat::VK_FORMAT_G16_B16R16_2PLANE_422_UNORM_KHR)
		.value("G16_B16_R16_3PLANE_444_UNORM_KHR", VkFormat::VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM_KHR);
	py::enum_<VkPresentModeKHR>(m, "PresentModeKHR")
		.value("SHARED_DEMAND_REFRESH_KHR", VkPresentModeKHR::VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR)
		.value("SHARED_CONTINUOUS_REFRESH_KHR", VkPresentModeKHR::VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR)
		.value("MAILBOX_KHR", VkPresentModeKHR::VK_PRESENT_MODE_MAILBOX_KHR)
		.value("IMMEDIATE_KHR", VkPresentModeKHR::VK_PRESENT_MODE_IMMEDIATE_KHR)
		.value("FIFO_RELAXED_KHR", VkPresentModeKHR::VK_PRESENT_MODE_FIFO_RELAXED_KHR)
		.value("FIFO_KHR", VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR);
	py::enum_<VkColorSpaceKHR>(m, "ColorSpaceKHR")
		.value("SRGB_NONLINEAR_KHR", VkColorSpaceKHR::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		.value("DISPLAY_P3_NONLINEAR_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT)
		.value("EXTENDED_SRGB_LINEAR_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT)
		.value("DCI_P3_LINEAR_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_DCI_P3_LINEAR_EXT)
		.value("DCI_P3_NONLINEAR_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT)
		.value("BT709_LINEAR_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_BT709_LINEAR_EXT)
		.value("BT709_NONLINEAR_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_BT709_NONLINEAR_EXT)
		.value("BT2020_LINEAR_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_BT2020_LINEAR_EXT)
		.value("HDR10_ST2084_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_HDR10_ST2084_EXT)
		.value("DOLBYVISION_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_DOLBYVISION_EXT)
		.value("HDR10_HLG_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_HDR10_HLG_EXT)
		.value("ADOBERGB_LINEAR_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT)
		.value("ADOBERGB_NONLINEAR_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT)
		.value("PASS_THROUGH_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_PASS_THROUGH_EXT)
		.value("EXTENDED_SRGB_NONLINEAR_EXT", VkColorSpaceKHR::VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT)
		.value("DISPLAY_NATIVE_AMD", VkColorSpaceKHR::VK_COLOR_SPACE_DISPLAY_NATIVE_AMD)
		.value("SRGB_NONLINEAR_KHR", VkColorSpaceKHR::VK_COLORSPACE_SRGB_NONLINEAR_KHR);
	py::enum_<VkSharingMode>(m, "SharingMode")
		.value("CONCURRENT", VkSharingMode::VK_SHARING_MODE_CONCURRENT)
		.value("EXCLUSIVE", VkSharingMode::VK_SHARING_MODE_EXCLUSIVE);

	// extensions
	
	py::class_<SurfaceKHR>(m, "SurfaceKHR")
		.def(py::init<>())
		.def_property_readonly("isValid", &SurfaceKHR::isValid);

	py::class_<DebugUtilsMessengerEXT> DebugUtilsMessengerClass(m, "DebugUtilsMessengerEXT");
	DebugUtilsMessengerClass
		.def(py::init<>())
		.def("destroy", &DebugUtilsMessengerEXT::destroy)
		.def_property_readonly("isValid", &DebugUtilsMessengerEXT::isValid);
	py::enum_<VkDebugUtilsMessageSeverityFlagBitsEXT>(DebugUtilsMessengerClass, "MessageSeverityFlagBits", py::arithmetic())
		.value("MessageSeverityErrorBit", VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
		//.value("", VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT)
		.value("MessageSeverityInfoBit", VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
		.value("MessageSeverityVerboseBit", VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
		.value("MessageSeverityWarningBit", VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		.export_values();
	py::enum_<VkDebugUtilsMessageTypeFlagBitsEXT>(DebugUtilsMessengerClass, "MessageTypeFlagBits", py::arithmetic())
		.value("MessageTypeGeneralBit", VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
		.value("MessageTypePerformanceBit", VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
		.value("MessageTypeValidationBit", VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
		.export_values();


	// exceptions
	static py::exception<OutOfHostMemory> OutOfHostMemory_ex(m, "OutOfHostMemory");
	py::register_exception_translator([](std::exception_ptr p) {
		try {
			if (p) std::rethrow_exception(p);
		}
		catch (const OutOfHostMemory &e) {
			OutOfHostMemory_ex(e.what());
		}
	});

	static py::exception<OutOfDeviceMemory> OutOfDeviceMemory_ex(m, "OutOfDeviceMemory");
	py::register_exception_translator([](std::exception_ptr p) {
		try {
			if (p) std::rethrow_exception(p);
		}
		catch (const OutOfDeviceMemory &e) {
			OutOfDeviceMemory_ex(e.what());
		}
	});

	static py::exception<InitializationFailed> InitializationFailed_ex(m, "InitializationFailed");
	py::register_exception_translator([](std::exception_ptr p) {
		try {
			if (p) std::rethrow_exception(p);
		}
		catch (const InitializationFailed &e) {
			InitializationFailed_ex(e.what());
		}
	});

	static py::exception<LayerNotPresent> LayerNotPresent_ex(m, "LayerNotPresent");
	py::register_exception_translator([](std::exception_ptr p) {
		try {
			if (p) std::rethrow_exception(p);
		}
		catch (const LayerNotPresent &e) {
			LayerNotPresent_ex(e.what());
		}
	});

	static py::exception<ExtensionNotPresent> ExtensionNotPresent_ex(m, "ExtensionNotPresent");
	py::register_exception_translator([](std::exception_ptr p) {
		try {
			if (p) std::rethrow_exception(p);
		}
		catch (const ExtensionNotPresent &e) {
			ExtensionNotPresent_ex(e.what());
		}
	});

	static py::exception<IncompatibleDriver> IncompatibleDriver_ex(m, "IncompatibleDriver");
	py::register_exception_translator([](std::exception_ptr p) {
		try {
			if (p) std::rethrow_exception(p);
		}
		catch (const IncompatibleDriver &e) {
			IncompatibleDriver_ex(e.what());
		}
	});
}

