#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>

#include "instance.h"
//#include "deviceQueue.h"
//#include "descriptors.h"
//#include "vktypes.h"
//#include "createInfo.h"


PYBIND11_MODULE(_vk, m)
{
	m.doc() = "vulkan for python.";

	//m.def("initialize", []() { checkVKResult(volkInitialize()); return true; });

	py::class_<Instance>(m, "Instance")
		//.def(py::init<>())
		//.def(py::init<py::dict>())
		.def(py::init<InstanceCreateInfo&>(), py::arg("createInfo"))
		//.def("create", &Instance::create, py::arg("createInfo"))
		//.def("create2", &Instance::create2, py::arg("createInfo"))
		.def("destroy", &Instance::destroy)
		//.def("createDebugUtilsMessengerEXT", &Instance::createDebugUtilsMessengerEXT, 
		//	py::arg("messageSeverity"), py::arg("messageType"), py::arg("userCallback"),
		//	py::return_value_policy::reference)
		//.def("createSurface", &Instance::createSurface, py::arg("createInfo"), 
		//	py::return_value_policy::reference)
		//.def("getPhysicalDevices", &Instance::getPhysicalDevices)
		.def_property_readonly("isValid", &Instance::isValid)
		.def_static("version", &Instance::version)
		.def_static("getLayerProperties", &Instance::layerProperties)
		.def_static("getExtensionProperties", &Instance::extensionProperties, py::arg("layerName") = nullptr);

	//py::class_<PhysicalDevice> PhysicalDeviceClass(m, "PhysicalDevice");
	//PhysicalDeviceClass
	//	.def(py::init<>())
	//	.def("getSurfaceSupportKHR", &PhysicalDevice::getSurfaceSupportKHR, py::arg("surface"), py::arg("queueFamilyIndex"))
	//	.def("getLayerProperties", &PhysicalDevice::layerProperties)
	//	.def("getExtensionProperties", &PhysicalDevice::extensionProperties, py::arg("layerName") = nullptr)
	//	.def("getSurfaceCapabilitiesKHR", &PhysicalDevice::getSurfaceCapabilitiesKHR, py::arg("surface"))
	//	.def("getSurfaceFormatsKHR", &PhysicalDevice::getSurfaceFormatsKHR, py::arg("surface"))
	//	.def("getSurfacePresentModeKHR", &PhysicalDevice::getSurfacePresentModeKHR, py::arg("surface"))
	//	.def("__repr__", &PhysicalDevice::toString)
	//	.def_property_readonly("isValid", &PhysicalDevice::isValid)
	//	.def_property_readonly("properties", &PhysicalDevice::getProperties)
	//	.def_property_readonly("queueFamilyProperties", &PhysicalDevice::getQueueFamilyProperties);
	//py::enum_<VkPhysicalDeviceType>(PhysicalDeviceClass, "DeviceType")
	//	.value("CPU", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU)
	//	.value("OTHER", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_OTHER)
	//	.value("DISCRETE_GPU", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
	//	.value("INTEGRATED_GPU", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
	//	.value("VIRTUAL_GPU", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU)
	//	.export_values();

	//py::class_<Device>(m, "Device")
	//	.def(py::init<PhysicalDevice&, py::dict>(), py::arg("physicalDevice"), py::arg("createInfo"))
	//	.def("getQueue", &Device::getQueue)
	//	.def("createSwapchainKHR", &Device::createSwapchainKHR, py::arg("createInfo"))
	//	.def("getSwapchainImagesKHR", &Device::getSwapchainImagesKHR, py::arg("swapchain"))
	//	.def("createImageView", &Device::createImageView, py::arg("createInfo"))
	//	.def("createShaderModule", &Device::createShaderModule, py::arg("filename"))
	//	.def("createPipelineLayout", &Device::createPipelineLayout, py::arg("createInfo").noconvert())
	//	.def("createRenderPass", &Device::createRenderPass, py::arg("createInfo"))
	//	.def("createGraphicsPipelines", &Device::createGraphicsPipelines, py::arg("cache"), py::arg("createInfos"))
	//	.def_property_readonly("isValid", &Device::isValid);

	//py::class_<DeviceQueue>(m, "DeviceQueue")
	//	.def(py::init<Device*, uint32_t, uint32_t>(), py::arg("device"), py::arg("queueFamilyIndex"), py::arg("queueIndex"))
	//	.def_property_readonly("isValid", &DeviceQueue::isValid);

	//py::class_<SwapchainKHR>(m, "SwapchainKHR")
	//	.def(py::init<Device*, py::dict>())
	//	.def("getImagesKHR", &SwapchainKHR::getImagesKHR)
	//	.def_property_readonly("isValid", &SwapchainKHR::isValid);

	//py::class_<Image>(m, "Image")
	//	.def(py::init<>())
	//	.def_property_readonly("isValid", &Image::isValid);

	//py::class_<ImageView>(m, "ImageView")
	//	.def(py::init<>())
	//	.def_property_readonly("isValid", &ImageView::isValid);

	//py::class_<ShaderModule>(m, "ShaderModule")
	//	.def(py::init<>())
	//	.def_property_readonly("isValid", &ShaderModule::isValid);

	//py::class_<PipelineLayout>(m, "PipelineLayout")
	//	.def(py::init<>())
	//	.def_property_readonly("isValid", &PipelineLayout::isValid);

	//py::class_<RenderPass>(m, "RenderPass")
	//	.def(py::init<>())
	//	.def_property_readonly("isValid", &RenderPass::isValid);

	//py::class_<SubpassDescription>(m, "SubpassDescription")
	//	.def(py::init<>())
	//	.def_readwrite("colorAttachments", &SubpassDescription::colorAttachments)
	//	.def_readwrite("depthStencilAttachment", &SubpassDescription::depthStencilAttachment)
	//	.def_readwrite("inputAttachments", &SubpassDescription::inputAttachments)
	//	.def_readwrite("pipelineBindPoint", &SubpassDescription::pipelineBindPoint)
	//	.def_readwrite("preserveAttachments", &SubpassDescription::preserveAttachments)
	//	.def_readwrite("resolveAttachments", &SubpassDescription::resolveAttachments);

	py::class_<ApplicationInfo>(m, "ApplicationInfo")
		.def(py::init<>())
		.def(py::init<std::string, std::string, uint32_t, uint32_t, uint32_t>(),
			py::arg("appName"), py::arg("engineName"), py::arg("appVersion"), py::arg("engineVersion"), py::arg("apiVersion"))
		.def_readwrite("apiVersion", &ApplicationInfo::apiVersion)
		.def_readwrite("applicationName", &ApplicationInfo::appName)
		.def_readwrite("applicationVersion", &ApplicationInfo::appVersion)
		.def_readwrite("engineName", &ApplicationInfo::engineName)
		.def_readwrite("engineVersion", &ApplicationInfo::engineVersion);
		//.def_property("engineVersion", &ApplicationInfo::getEngineVersion, &ApplicationInfo::setEngineVersion)
		//.def_property("engineName", &ApplicationInfo::getEngineName, &ApplicationInfo::setEngineName)
		//.def_property("applicationVersion", &ApplicationInfo::getApplicationVersion, &ApplicationInfo::setApplicationVersion)
		//.def_property("applicationName", &ApplicationInfo::getApplicationName, &ApplicationInfo::setApplicationName)
		//.def_property("apiVersion", &ApplicationInfo::getApiVersion, &ApplicationInfo::setApiVersion)
		//.def("__repr__", &ApplicationInfo::toString);

	py::class_<InstanceCreateInfo>(m, "InstanceCreateInfo")
		.def(py::init<>())
		.def(py::init<ApplicationInfo *, std::vector<std::string> &, std::vector<std::string> &>(),
			py::arg("appInfo"), py::arg("layerNames"), py::arg("extentsionNames"))
		.def_readwrite("applicationInfo", &InstanceCreateInfo::appInfo)
		.def_readwrite("enabledExtensionNames", &InstanceCreateInfo::extensionNames)
		.def_readwrite("enabledLayerNames", &InstanceCreateInfo::layerNames);
		/*.def_property("applicationInfo", &InstanceCreateInfo::getApplicationInfo, &InstanceCreateInfo::setApplicationInfo)
		.def_property("enabledLayerNames", &InstanceCreateInfo::getApplicationInfo, &InstanceCreateInfo::setEnabledLayerNames)
		.def_property("enabledExtensionNames", &InstanceCreateInfo::getApplicationInfo, &InstanceCreateInfo::setEnabledExtensionNames);*/

	//py::class_<VkDebugUtilsMessengerCreateInfoEXT>(m, "DebugUtilsMessengerCreateInfoEXT")
	//	.def(py::init<>())
	//	.def_readwrite("messageSeverity", &VkDebugUtilsMessengerCreateInfoEXT::messageSeverity)
	//	.def_readwrite("messageType", &VkDebugUtilsMessengerCreateInfoEXT::messageType)
	//	.def_property("", []() { return nullptr; }, [](VkDebugUtilsMessengerCreateInfoEXT &info, std::function<VKAPI_ATTR VkBool32 VKAPI_CALL(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT *, void *)> &f) { info.pfnUserCallback = (PFN_vkDebugUtilsMessengerCallbackEXT*)f; });

	py::class_<VkDebugUtilsMessengerCallbackDataEXT>(m, "DebugUtilsMessengerCallbackDataEXT")
		.def(py::init<>())
		.def_readonly("messageIdName", &VkDebugUtilsMessengerCallbackDataEXT::pMessageIdName)
		.def_readonly("messageIdName", &VkDebugUtilsMessengerCallbackDataEXT::pMessage)
		.def_readwrite("messageIdNumber", &VkDebugUtilsMessengerCallbackDataEXT::messageIdNumber)
		.def_property_readonly("queueLabels", [](VkDebugUtilsMessengerCallbackDataEXT &data) { std::vector<VkDebugUtilsLabelEXT> labels(data.queueLabelCount); for (auto i = 0; i < data.queueLabelCount; i++) { labels[i] = *data.pQueueLabels; data.pQueueLabels++; } return labels; })
		.def_property_readonly("cmdBufLabels", [](VkDebugUtilsMessengerCallbackDataEXT &data) { std::vector<VkDebugUtilsLabelEXT> labels(data.cmdBufLabelCount); for (auto i = 0; i < data.cmdBufLabelCount; i++) { labels[i] = *data.pCmdBufLabels; data.pCmdBufLabels++; } return labels; })
		.def_property_readonly("objects", [](VkDebugUtilsMessengerCallbackDataEXT &data) { std::vector<VkDebugUtilsObjectNameInfoEXT> labels(data.objectCount); for (auto i = 0; i < data.objectCount; i++) { labels[i] = *data.pObjects; data.pCmdBufLabels++; } return labels; });

	py::class_<VkDebugUtilsLabelEXT>(m, "DebugUtilsLabelEXT")
		.def(py::init<>())
		.def_readonly("pNext", &VkDebugUtilsLabelEXT::pNext)
		.def_readonly("labelName", &VkDebugUtilsLabelEXT::pLabelName)
		.def_property_readonly("color", [](VkDebugUtilsLabelEXT &label) { py::list col; for (auto i = 0; i < 4; i++) col.append(py::float_(label.color[i])); return col; });

	py::class_<VkDebugUtilsObjectNameInfoEXT>(m, "DebugUtilsObjectNameInfoEXT")
		.def(py::init<>())
		.def_readonly("pNext", &VkDebugUtilsObjectNameInfoEXT::pNext)
		.def_readonly("objectName", &VkDebugUtilsObjectNameInfoEXT::pObjectName)
		.def_readwrite("objectHandle", &VkDebugUtilsObjectNameInfoEXT::objectHandle)
		.def_readwrite("objectType", &VkDebugUtilsObjectNameInfoEXT::objectType);

	py::class_<VkClearColorValue>(m, "ClearColorValue")
		.def(py::init([](float r, float g, float b, float a) { VkClearColorValue out; out.float32[0] = r; out.float32[1] = g; out.float32[2] = b; out.float32[3] = a; return out; }), py::arg("r"), py::arg("g"), py::arg("b"), py::arg("a"))
		.def(py::init([](int r, int g, int b, int a) { VkClearColorValue out; out.int32[0] = r; out.int32[1] = g; out.int32[2] = b; out.int32[3] = a; return out; }), py::arg("r"), py::arg("g"), py::arg("b"), py::arg("a"))
		.def(py::init([](uint32_t r, uint32_t g, uint32_t b, uint32_t a) { VkClearColorValue out; out.uint32[0] = r; out.uint32[1] = g; out.uint32[2] = b; out.uint32[3] = a; return out; }), py::arg("r"), py::arg("g"), py::arg("b"), py::arg("a"));

	py::class_<VkClearValue>(m, "ClearValue")
		.def(py::init([](VkClearColorValue &val) { VkClearValue out; out.color = val; return out; }), py::arg("color"))
		.def(py::init([](VkClearDepthStencilValue &val) { VkClearValue out; out.depthStencil = val; return out; }), py::arg("depthStencil"))
		.def_property("color", [](VkClearValue &v) { return v.color; }, [](VkClearValue &v, VkClearColorValue &color) { v.color = color; })
		.def_property("depthStencil", [](VkClearValue &v) { return v.depthStencil; }, [](VkClearValue &v, VkClearDepthStencilValue &dv) { v.depthStencil = dv; });

	py::class_<VkPerformanceValueDataINTEL>(m, "PerformanceValueDataINTEL")
		.def(py::init([](uint32_t v) { VkPerformanceValueDataINTEL out; out.value32 = v; return out; }), py::arg("value"))
		.def(py::init([](uint64_t v) { VkPerformanceValueDataINTEL out; out.value64 = v; return out; }), py::arg("value"))
		.def(py::init([](float v) { VkPerformanceValueDataINTEL out; out.valueFloat = v; return out; }), py::arg("value"))
		.def(py::init([](VkBool32 v) { VkPerformanceValueDataINTEL out; out.valueBool = v; return out; }), py::arg("value"))
		.def(py::init([](const char* v) { VkPerformanceValueDataINTEL out; out.valueString = v; return out; }), py::arg("value"));

	py::class_<VkOffset2D>(m, "Offset2D")
		.def(py::init<>())
		.def_readwrite("x", &VkOffset2D::x)
		.def_readwrite("y", &VkOffset2D::y);

	py::class_<VkOffset3D>(m, "Offset3D")
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

	py::class_<VkViewport>(m, "Viewport")
		.def(py::init<>())
		.def_readwrite("x", &VkViewport::x)
		.def_readwrite("y", &VkViewport::y)
		.def_readwrite("width", &VkViewport::width)
		.def_readwrite("height", &VkViewport::height)
		.def_readwrite("minDepth", &VkViewport::minDepth)
		.def_readwrite("maxDepth", &VkViewport::maxDepth);

	py::class_<VkExtensionProperties>(m, "ExtensionProperties")
		.def(py::init<>())
		.def_readonly("extensionName", &VkExtensionProperties::extensionName)
		.def_readwrite("specVersion", &VkExtensionProperties::specVersion);

	py::class_<VkLayerProperties>(m, "LayerProperties")
		.def(py::init<>())
		.def_readonly("layerName", &VkLayerProperties::layerName)
		.def_readwrite("specVersion", &VkLayerProperties::specVersion)
		.def_readwrite("implementationVersion", &VkLayerProperties::implementationVersion)
		.def_readonly("description", &VkLayerProperties::description);

	py::class_<VkMemoryRequirements>(m, "MemoryRequirements")
		.def(py::init<>())
		.def_readwrite("size", &VkMemoryRequirements::size)
		.def_readwrite("alignment", &VkMemoryRequirements::alignment)
		.def_readwrite("memoryTypeBits", &VkMemoryRequirements::memoryTypeBits);

	py::class_<VkMemoryType>(m, "MemoryType")
		.def(py::init<>())
		.def_readwrite("propertyFlags", &VkMemoryType::propertyFlags)
		.def_readwrite("heapIndex", &VkMemoryType::heapIndex);

	py::class_<VkMemoryHeap>(m, "MemoryHeap")
		.def(py::init<>())
		.def_readwrite("size", &VkMemoryHeap::size)
		.def_readwrite("flags", &VkMemoryHeap::flags);

	py::class_<VkFormatProperties>(m, "FormatProperties")
		.def(py::init<>())
		.def_readwrite("linearTilingFeatures", &VkFormatProperties::linearTilingFeatures)
		.def_readwrite("optimalTilingFeatures", &VkFormatProperties::optimalTilingFeatures)
		.def_readwrite("bufferFeatures", &VkFormatProperties::bufferFeatures);

	py::class_<VkImageSubresource>(m, "ImageSubresource")
		.def(py::init<>())
		.def_readwrite("aspectMask", &VkImageSubresource::aspectMask)
		.def_readwrite("mipLevel", &VkImageSubresource::mipLevel)
		.def_readwrite("arrayLayer", &VkImageSubresource::arrayLayer);

	py::class_<VkImageSubresourceLayers>(m, "ImageSubresourceLayers")
		.def(py::init<>())
		.def_readwrite("aspectMask", &VkImageSubresourceLayers::aspectMask)
		.def_readwrite("mipLevel", &VkImageSubresourceLayers::mipLevel)
		.def_readwrite("baseArrayLayer", &VkImageSubresourceLayers::baseArrayLayer)
		.def_readwrite("layerCount", &VkImageSubresourceLayers::layerCount);

	py::class_<VkImageSubresourceRange>(m, "ImageSubresourceRange")
		.def(py::init<>())
		.def_readwrite("aspectMask", &VkImageSubresourceRange::aspectMask)
		.def_readwrite("baseMipLevel", &VkImageSubresourceRange::baseMipLevel)
		.def_readwrite("levelCount", &VkImageSubresourceRange::levelCount)
		.def_readwrite("baseArrayLayer", &VkImageSubresourceRange::baseArrayLayer)
		.def_readwrite("layerCount", &VkImageSubresourceRange::layerCount);

	py::class_<VkSubresourceLayout>(m, "SubresourceLayout")
		.def(py::init<>())
		.def_readwrite("offset", &VkSubresourceLayout::offset)
		.def_readwrite("size", &VkSubresourceLayout::size)
		.def_readwrite("rowPitch", &VkSubresourceLayout::rowPitch)
		.def_readwrite("arrayPitch", &VkSubresourceLayout::arrayPitch)
		.def_readwrite("depthPitch", &VkSubresourceLayout::depthPitch);

	py::class_<VkBufferCopy>(m, "BufferCopy")
		.def(py::init<>())
		.def_readwrite("srcOffset", &VkBufferCopy::srcOffset)
		.def_readwrite("dstOffset", &VkBufferCopy::dstOffset)
		.def_readwrite("size", &VkBufferCopy::size);

	py::class_<VkSpecializationMapEntry>(m, "SpecializationMapEntry")
		.def(py::init<>())
		.def_readwrite("constantID", &VkSpecializationMapEntry::constantID)
		.def_readwrite("offset", &VkSpecializationMapEntry::offset)
		.def_readwrite("size", &VkSpecializationMapEntry::size);

	py::class_<VkPushConstantRange>(m, "PushConstantRange")
		.def(py::init<>())
		.def_readwrite("stageFlags", &VkPushConstantRange::stageFlags)
		.def_readwrite("offset", &VkPushConstantRange::offset)
		.def_readwrite("size", &VkPushConstantRange::size);

	py::class_<VkClearDepthStencilValue>(m, "ClearDepthStencilValue")
		.def(py::init<>())
		.def_readwrite("depth", &VkClearDepthStencilValue::depth)
		.def_readwrite("stencil", &VkClearDepthStencilValue::stencil);

	py::class_<VkSubpassDependency>(m, "SubpassDependency")
		.def(py::init<>())
		.def_readwrite("srcSubpass", &VkSubpassDependency::srcSubpass)
		.def_readwrite("dstSubpass", &VkSubpassDependency::dstSubpass)
		.def_readwrite("srcStageMask", &VkSubpassDependency::srcStageMask)
		.def_readwrite("dstStageMask", &VkSubpassDependency::dstStageMask)
		.def_readwrite("srcAccessMask", &VkSubpassDependency::srcAccessMask)
		.def_readwrite("dstAccessMask", &VkSubpassDependency::dstAccessMask)
		.def_readwrite("dependencyFlags", &VkSubpassDependency::dependencyFlags);

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

	py::class_<VkPhysicalDeviceSparseProperties>(m, "PhysicalDeviceSparseProperties")
		.def(py::init<>())
		.def_readwrite("residencyStandard2DBlockShape", &VkPhysicalDeviceSparseProperties::residencyStandard2DBlockShape)
		.def_readwrite("residencyStandard2DMultisampleBlockShape", &VkPhysicalDeviceSparseProperties::residencyStandard2DMultisampleBlockShape)
		.def_readwrite("residencyStandard3DBlockShape", &VkPhysicalDeviceSparseProperties::residencyStandard3DBlockShape)
		.def_readwrite("residencyAlignedMipSize", &VkPhysicalDeviceSparseProperties::residencyAlignedMipSize)
		.def_readwrite("residencyNonResidentStrict", &VkPhysicalDeviceSparseProperties::residencyNonResidentStrict);

	py::class_<VkPhysicalDeviceLimits>(m, "PhysicalDeviceLimits")
		.def(py::init<>())
		.def_readwrite("maxImageDimension1D", &VkPhysicalDeviceLimits::maxImageDimension1D)
		.def_readwrite("maxImageDimension2D", &VkPhysicalDeviceLimits::maxImageDimension2D)
		.def_readwrite("maxImageDimension3D", &VkPhysicalDeviceLimits::maxImageDimension3D)
		.def_readwrite("maxImageDimensionCube", &VkPhysicalDeviceLimits::maxImageDimensionCube)
		.def_readwrite("maxImageArrayLayers", &VkPhysicalDeviceLimits::maxImageArrayLayers)
		.def_readwrite("maxTexelBufferElements", &VkPhysicalDeviceLimits::maxTexelBufferElements)
		.def_readwrite("maxUniformBufferRange", &VkPhysicalDeviceLimits::maxUniformBufferRange)
		.def_readwrite("maxStorageBufferRange", &VkPhysicalDeviceLimits::maxStorageBufferRange)
		.def_readwrite("maxPushConstantsSize", &VkPhysicalDeviceLimits::maxPushConstantsSize)
		.def_readwrite("maxMemoryAllocationCount", &VkPhysicalDeviceLimits::maxMemoryAllocationCount)
		.def_readwrite("maxSamplerAllocationCount", &VkPhysicalDeviceLimits::maxSamplerAllocationCount)
		.def_readwrite("bufferImageGranularity", &VkPhysicalDeviceLimits::bufferImageGranularity)
		.def_readwrite("sparseAddressSpaceSize", &VkPhysicalDeviceLimits::sparseAddressSpaceSize)
		.def_readwrite("maxBoundDescriptorSets", &VkPhysicalDeviceLimits::maxBoundDescriptorSets)
		.def_readwrite("maxPerStageDescriptorSamplers", &VkPhysicalDeviceLimits::maxPerStageDescriptorSamplers)
		.def_readwrite("maxPerStageDescriptorUniformBuffers", &VkPhysicalDeviceLimits::maxPerStageDescriptorUniformBuffers)
		.def_readwrite("maxPerStageDescriptorStorageBuffers", &VkPhysicalDeviceLimits::maxPerStageDescriptorStorageBuffers)
		.def_readwrite("maxPerStageDescriptorSampledImages", &VkPhysicalDeviceLimits::maxPerStageDescriptorSampledImages)
		.def_readwrite("maxPerStageDescriptorStorageImages", &VkPhysicalDeviceLimits::maxPerStageDescriptorStorageImages)
		.def_readwrite("maxPerStageDescriptorInputAttachments", &VkPhysicalDeviceLimits::maxPerStageDescriptorInputAttachments)
		.def_readwrite("maxPerStageResources", &VkPhysicalDeviceLimits::maxPerStageResources)
		.def_readwrite("maxDescriptorSetSamplers", &VkPhysicalDeviceLimits::maxDescriptorSetSamplers)
		.def_readwrite("maxDescriptorSetUniformBuffers", &VkPhysicalDeviceLimits::maxDescriptorSetUniformBuffers)
		.def_readwrite("maxDescriptorSetUniformBuffersDynamic", &VkPhysicalDeviceLimits::maxDescriptorSetUniformBuffersDynamic)
		.def_readwrite("maxDescriptorSetStorageBuffers", &VkPhysicalDeviceLimits::maxDescriptorSetStorageBuffers)
		.def_readwrite("maxDescriptorSetStorageBuffersDynamic", &VkPhysicalDeviceLimits::maxDescriptorSetStorageBuffersDynamic)
		.def_readwrite("maxDescriptorSetSampledImages", &VkPhysicalDeviceLimits::maxDescriptorSetSampledImages)
		.def_readwrite("maxDescriptorSetStorageImages", &VkPhysicalDeviceLimits::maxDescriptorSetStorageImages)
		.def_readwrite("maxDescriptorSetInputAttachments", &VkPhysicalDeviceLimits::maxDescriptorSetInputAttachments)
		.def_readwrite("maxVertexInputAttributes", &VkPhysicalDeviceLimits::maxVertexInputAttributes)
		.def_readwrite("maxVertexInputBindings", &VkPhysicalDeviceLimits::maxVertexInputBindings)
		.def_readwrite("maxVertexInputAttributeOffset", &VkPhysicalDeviceLimits::maxVertexInputAttributeOffset)
		.def_readwrite("maxVertexInputBindingStride", &VkPhysicalDeviceLimits::maxVertexInputBindingStride)
		.def_readwrite("maxVertexOutputComponents", &VkPhysicalDeviceLimits::maxVertexOutputComponents)
		.def_readwrite("maxTessellationGenerationLevel", &VkPhysicalDeviceLimits::maxTessellationGenerationLevel)
		.def_readwrite("maxTessellationPatchSize", &VkPhysicalDeviceLimits::maxTessellationPatchSize)
		.def_readwrite("maxTessellationControlPerVertexInputComponents", &VkPhysicalDeviceLimits::maxTessellationControlPerVertexInputComponents)
		.def_readwrite("maxTessellationControlPerVertexOutputComponents", &VkPhysicalDeviceLimits::maxTessellationControlPerVertexOutputComponents)
		.def_readwrite("maxTessellationControlPerPatchOutputComponents", &VkPhysicalDeviceLimits::maxTessellationControlPerPatchOutputComponents)
		.def_readwrite("maxTessellationControlTotalOutputComponents", &VkPhysicalDeviceLimits::maxTessellationControlTotalOutputComponents)
		.def_readwrite("maxTessellationEvaluationInputComponents", &VkPhysicalDeviceLimits::maxTessellationEvaluationInputComponents)
		.def_readwrite("maxTessellationEvaluationOutputComponents", &VkPhysicalDeviceLimits::maxTessellationEvaluationOutputComponents)
		.def_readwrite("maxGeometryShaderInvocations", &VkPhysicalDeviceLimits::maxGeometryShaderInvocations)
		.def_readwrite("maxGeometryInputComponents", &VkPhysicalDeviceLimits::maxGeometryInputComponents)
		.def_readwrite("maxGeometryOutputComponents", &VkPhysicalDeviceLimits::maxGeometryOutputComponents)
		.def_readwrite("maxGeometryOutputVertices", &VkPhysicalDeviceLimits::maxGeometryOutputVertices)
		.def_readwrite("maxGeometryTotalOutputComponents", &VkPhysicalDeviceLimits::maxGeometryTotalOutputComponents)
		.def_readwrite("maxFragmentInputComponents", &VkPhysicalDeviceLimits::maxFragmentInputComponents)
		.def_readwrite("maxFragmentOutputAttachments", &VkPhysicalDeviceLimits::maxFragmentOutputAttachments)
		.def_readwrite("maxFragmentDualSrcAttachments", &VkPhysicalDeviceLimits::maxFragmentDualSrcAttachments)
		.def_readwrite("maxFragmentCombinedOutputResources", &VkPhysicalDeviceLimits::maxFragmentCombinedOutputResources)
		.def_readwrite("maxComputeSharedMemorySize", &VkPhysicalDeviceLimits::maxComputeSharedMemorySize)
		.def_property_readonly("maxComputeWorkGroupCount", [](VkPhysicalDeviceLimits &limits) { py::list out; for (auto i : limits.maxComputeWorkGroupCount) out.append(i); return out; })
		.def_readwrite("maxComputeWorkGroupInvocations", &VkPhysicalDeviceLimits::maxComputeWorkGroupInvocations)
		.def_property_readonly("maxComputeWorkGroupSize", [](VkPhysicalDeviceLimits &limits) { py::list out; for (auto i : limits.maxComputeWorkGroupSize) out.append(i); return out; })//&VkPhysicalDeviceLimits::maxComputeWorkGroupSize)
		.def_readwrite("subPixelPrecisionBits", &VkPhysicalDeviceLimits::subPixelPrecisionBits)
		.def_readwrite("subTexelPrecisionBits", &VkPhysicalDeviceLimits::subTexelPrecisionBits)
		.def_readwrite("mipmapPrecisionBits", &VkPhysicalDeviceLimits::mipmapPrecisionBits)
		.def_readwrite("maxDrawIndexedIndexValue", &VkPhysicalDeviceLimits::maxDrawIndexedIndexValue)
		.def_readwrite("maxDrawIndirectCount", &VkPhysicalDeviceLimits::maxDrawIndirectCount)
		.def_readwrite("maxSamplerLodBias", &VkPhysicalDeviceLimits::maxSamplerLodBias)
		.def_readwrite("maxSamplerAnisotropy", &VkPhysicalDeviceLimits::maxSamplerAnisotropy)
		.def_readwrite("maxViewports", &VkPhysicalDeviceLimits::maxViewports)
		.def_property_readonly("maxViewportDimensions", [](VkPhysicalDeviceLimits &limits) { py::list out; for (auto i : limits.maxViewportDimensions) out.append(i); return out; })
		.def_property_readonly("viewportBoundsRange", [](VkPhysicalDeviceLimits &limits) { py::list out; for (auto i : limits.viewportBoundsRange) out.append(i); return out; })
		.def_readwrite("viewportSubPixelBits", &VkPhysicalDeviceLimits::viewportSubPixelBits)
		.def_readwrite("minMemoryMapAlignment", &VkPhysicalDeviceLimits::minMemoryMapAlignment)
		.def_readwrite("minTexelBufferOffsetAlignment", &VkPhysicalDeviceLimits::minTexelBufferOffsetAlignment)
		.def_readwrite("minUniformBufferOffsetAlignment", &VkPhysicalDeviceLimits::minUniformBufferOffsetAlignment)
		.def_readwrite("minStorageBufferOffsetAlignment", &VkPhysicalDeviceLimits::minStorageBufferOffsetAlignment)
		.def_readwrite("minTexelOffset", &VkPhysicalDeviceLimits::minTexelOffset)
		.def_readwrite("maxTexelOffset", &VkPhysicalDeviceLimits::maxTexelOffset)
		.def_readwrite("minTexelGatherOffset", &VkPhysicalDeviceLimits::minTexelGatherOffset)
		.def_readwrite("maxTexelGatherOffset", &VkPhysicalDeviceLimits::maxTexelGatherOffset)
		.def_readwrite("minInterpolationOffset", &VkPhysicalDeviceLimits::minInterpolationOffset)
		.def_readwrite("maxInterpolationOffset", &VkPhysicalDeviceLimits::maxInterpolationOffset)
		.def_readwrite("subPixelInterpolationOffsetBits", &VkPhysicalDeviceLimits::subPixelInterpolationOffsetBits)
		.def_readwrite("maxFramebufferWidth", &VkPhysicalDeviceLimits::maxFramebufferWidth)
		.def_readwrite("maxFramebufferHeight", &VkPhysicalDeviceLimits::maxFramebufferHeight)
		.def_readwrite("maxFramebufferLayers", &VkPhysicalDeviceLimits::maxFramebufferLayers)
		.def_readwrite("framebufferColorSampleCounts", &VkPhysicalDeviceLimits::framebufferColorSampleCounts)
		.def_readwrite("framebufferDepthSampleCounts", &VkPhysicalDeviceLimits::framebufferDepthSampleCounts)
		.def_readwrite("framebufferStencilSampleCounts", &VkPhysicalDeviceLimits::framebufferStencilSampleCounts)
		.def_readwrite("framebufferNoAttachmentsSampleCounts", &VkPhysicalDeviceLimits::framebufferNoAttachmentsSampleCounts)
		.def_readwrite("maxColorAttachments", &VkPhysicalDeviceLimits::maxColorAttachments)
		.def_readwrite("sampledImageColorSampleCounts", &VkPhysicalDeviceLimits::sampledImageColorSampleCounts)
		.def_readwrite("sampledImageIntegerSampleCounts", &VkPhysicalDeviceLimits::sampledImageIntegerSampleCounts)
		.def_readwrite("sampledImageDepthSampleCounts", &VkPhysicalDeviceLimits::sampledImageDepthSampleCounts)
		.def_readwrite("sampledImageStencilSampleCounts", &VkPhysicalDeviceLimits::sampledImageStencilSampleCounts)
		.def_readwrite("storageImageSampleCounts", &VkPhysicalDeviceLimits::storageImageSampleCounts)
		.def_readwrite("maxSampleMaskWords", &VkPhysicalDeviceLimits::maxSampleMaskWords)
		.def_readwrite("timestampComputeAndGraphics", &VkPhysicalDeviceLimits::timestampComputeAndGraphics)
		.def_readwrite("timestampPeriod", &VkPhysicalDeviceLimits::timestampPeriod)
		.def_readwrite("maxClipDistances", &VkPhysicalDeviceLimits::maxClipDistances)
		.def_readwrite("maxCullDistances", &VkPhysicalDeviceLimits::maxCullDistances)
		.def_readwrite("maxCombinedClipAndCullDistances", &VkPhysicalDeviceLimits::maxCombinedClipAndCullDistances)
		.def_readwrite("discreteQueuePriorities", &VkPhysicalDeviceLimits::discreteQueuePriorities)
		.def_property_readonly("pointSizeRange", [](VkPhysicalDeviceLimits &limits) { py::list out; for (auto i : limits.pointSizeRange) out.append(i); return out; })
		.def_property_readonly("lineWidthRange", [](VkPhysicalDeviceLimits &limits) { py::list out; for (auto i : limits.lineWidthRange) out.append(i); return out; })
		.def_readwrite("pointSizeGranularity", &VkPhysicalDeviceLimits::pointSizeGranularity)
		.def_readwrite("lineWidthGranularity", &VkPhysicalDeviceLimits::lineWidthGranularity)
		.def_readwrite("strictLines", &VkPhysicalDeviceLimits::strictLines)
		.def_readwrite("standardSampleLocations", &VkPhysicalDeviceLimits::standardSampleLocations)
		.def_readwrite("optimalBufferCopyOffsetAlignment", &VkPhysicalDeviceLimits::optimalBufferCopyOffsetAlignment)
		.def_readwrite("optimalBufferCopyRowPitchAlignment", &VkPhysicalDeviceLimits::optimalBufferCopyRowPitchAlignment)
		.def_readwrite("nonCoherentAtomSize", &VkPhysicalDeviceLimits::nonCoherentAtomSize);

	py::class_<VkDrawIndirectCommand>(m, "DrawIndirectCommand")
		.def(py::init<>())
		.def_readwrite("vertexCount", &VkDrawIndirectCommand::vertexCount)
		.def_readwrite("instanceCount", &VkDrawIndirectCommand::instanceCount)
		.def_readwrite("firstVertex", &VkDrawIndirectCommand::firstVertex)
		.def_readwrite("firstInstance", &VkDrawIndirectCommand::firstInstance);

	py::class_<VkDrawIndexedIndirectCommand>(m, "DrawIndexedIndirectCommand")
		.def(py::init<>())
		.def_readwrite("indexCount", &VkDrawIndexedIndirectCommand::indexCount)
		.def_readwrite("instanceCount", &VkDrawIndexedIndirectCommand::instanceCount)
		.def_readwrite("firstIndex", &VkDrawIndexedIndirectCommand::firstIndex)
		.def_readwrite("vertexOffset", &VkDrawIndexedIndirectCommand::vertexOffset)
		.def_readwrite("firstInstance", &VkDrawIndexedIndirectCommand::firstInstance);

	py::class_<VkDispatchIndirectCommand>(m, "DispatchIndirectCommand")
		.def(py::init<>())
		.def_readwrite("x", &VkDispatchIndirectCommand::x)
		.def_readwrite("y", &VkDispatchIndirectCommand::y)
		.def_readwrite("z", &VkDispatchIndirectCommand::z);

	py::class_<VkConformanceVersionKHR>(m, "ConformanceVersionKHR")
		.def(py::init<>())
		.def_readwrite("major", &VkConformanceVersionKHR::major)
		.def_readwrite("minor", &VkConformanceVersionKHR::minor)
		.def_readwrite("subminor", &VkConformanceVersionKHR::subminor)
		.def_readwrite("patch", &VkConformanceVersionKHR::patch);

	py::class_<VkExternalMemoryProperties>(m, "ExternalMemoryProperties")
		.def(py::init<>())
		.def_readwrite("externalMemoryFeatures", &VkExternalMemoryProperties::externalMemoryFeatures)
		.def_readwrite("exportFromImportedHandleTypes", &VkExternalMemoryProperties::exportFromImportedHandleTypes)
		.def_readwrite("compatibleHandleTypes", &VkExternalMemoryProperties::compatibleHandleTypes);

	py::class_<VkXYColorEXT>(m, "XYColorEXT")
		.def(py::init<>())
		.def_readwrite("x", &VkXYColorEXT::x)
		.def_readwrite("y", &VkXYColorEXT::y);

	py::class_<VkRefreshCycleDurationGOOGLE>(m, "RefreshCycleDurationGOOGLE")
		.def(py::init<>())
		.def_readwrite("refreshDuration", &VkRefreshCycleDurationGOOGLE::refreshDuration);

	py::class_<VkPastPresentationTimingGOOGLE>(m, "PastPresentationTimingGOOGLE")
		.def(py::init<>())
		.def_readwrite("presentID", &VkPastPresentationTimingGOOGLE::presentID)
		.def_readwrite("desiredPresentTime", &VkPastPresentationTimingGOOGLE::desiredPresentTime)
		.def_readwrite("actualPresentTime", &VkPastPresentationTimingGOOGLE::actualPresentTime)
		.def_readwrite("earliestPresentTime", &VkPastPresentationTimingGOOGLE::earliestPresentTime)
		.def_readwrite("presentMargin", &VkPastPresentationTimingGOOGLE::presentMargin);

	py::class_<VkPresentTimeGOOGLE>(m, "PresentTimeGOOGLE")
		.def(py::init<>())
		.def_readwrite("presentID", &VkPresentTimeGOOGLE::presentID)
		.def_readwrite("desiredPresentTime", &VkPresentTimeGOOGLE::desiredPresentTime);

	py::class_<VkViewportWScalingNV>(m, "ViewportWScalingNV")
		.def(py::init<>())
		.def_readwrite("xcoeff", &VkViewportWScalingNV::xcoeff)
		.def_readwrite("ycoeff", &VkViewportWScalingNV::ycoeff);

	py::class_<VkInputAttachmentAspectReference>(m, "InputAttachmentAspectReference")
		.def(py::init<>())
		.def_readwrite("subpass", &VkInputAttachmentAspectReference::subpass)
		.def_readwrite("inputAttachmentIndex", &VkInputAttachmentAspectReference::inputAttachmentIndex)
		.def_readwrite("aspectMask", &VkInputAttachmentAspectReference::aspectMask);

	py::class_<VkSampleLocationEXT>(m, "SampleLocationEXT")
		.def(py::init<>())
		.def_readwrite("x", &VkSampleLocationEXT::x)
		.def_readwrite("y", &VkSampleLocationEXT::y);

	py::class_<VkShaderResourceUsageAMD>(m, "ShaderResourceUsageAMD")
		.def(py::init<>())
		.def_readwrite("numUsedVgprs", &VkShaderResourceUsageAMD::numUsedVgprs)
		.def_readwrite("numUsedSgprs", &VkShaderResourceUsageAMD::numUsedSgprs)
		.def_readwrite("ldsSizePerLocalWorkGroup", &VkShaderResourceUsageAMD::ldsSizePerLocalWorkGroup)
		.def_readwrite("ldsUsageSizeInBytes", &VkShaderResourceUsageAMD::ldsUsageSizeInBytes)
		.def_readwrite("scratchMemUsageInBytes", &VkShaderResourceUsageAMD::scratchMemUsageInBytes);

	py::class_<VkVertexInputBindingDivisorDescriptionEXT>(m, "VertexInputBindingDivisorDescriptionEXT")
		.def(py::init<>())
		.def_readwrite("binding", &VkVertexInputBindingDivisorDescriptionEXT::binding)
		.def_readwrite("divisor", &VkVertexInputBindingDivisorDescriptionEXT::divisor);

	py::class_<VkCoarseSampleLocationNV>(m, "CoarseSampleLocationNV")
		.def(py::init<>())
		.def_readwrite("pixelX", &VkCoarseSampleLocationNV::pixelX)
		.def_readwrite("pixelY", &VkCoarseSampleLocationNV::pixelY)
		.def_readwrite("sample", &VkCoarseSampleLocationNV::sample);

	py::class_<VkDrawMeshTasksIndirectCommandNV>(m, "DrawMeshTasksIndirectCommandNV")
		.def(py::init<>())
		.def_readwrite("taskCount", &VkDrawMeshTasksIndirectCommandNV::taskCount)
		.def_readwrite("firstTask", &VkDrawMeshTasksIndirectCommandNV::firstTask);

	py::class_<VkDrmFormatModifierPropertiesEXT>(m, "DrmFormatModifierPropertiesEXT")
		.def(py::init<>())
		.def_readwrite("drmFormatModifier", &VkDrmFormatModifierPropertiesEXT::drmFormatModifier)
		.def_readwrite("drmFormatModifierPlaneCount", &VkDrmFormatModifierPropertiesEXT::drmFormatModifierPlaneCount)
		.def_readwrite("drmFormatModifierTilingFeatures", &VkDrmFormatModifierPropertiesEXT::drmFormatModifierTilingFeatures);

	py::class_<VkPipelineCreationFeedbackEXT>(m, "PipelineCreationFeedbackEXT")
		.def(py::init<>())
		.def_readwrite("flags", &VkPipelineCreationFeedbackEXT::flags)
		.def_readwrite("duration", &VkPipelineCreationFeedbackEXT::duration);

	//-------------------- enums binding ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------m.attr(VK_MAX_PHYSICAL_DEVICE_NAME_SIZE) = py::int_(VK_MAX_PHYSICAL_DEVICE_NAME_SIZE);
	m.attr("VK_UUID_SIZE") = py::int_(VK_UUID_SIZE);
	m.attr("VK_LUID_SIZE") = py::int_(VK_LUID_SIZE);
	m.attr("VK_LUID_SIZE_KHR") = py::int_(VK_LUID_SIZE_KHR);
	m.attr("VK_MAX_EXTENSION_NAME_SIZE") = py::int_(VK_MAX_EXTENSION_NAME_SIZE);
	m.attr("VK_MAX_DESCRIPTION_SIZE") = py::int_(VK_MAX_DESCRIPTION_SIZE);
	m.attr("VK_MAX_MEMORY_TYPES") = py::int_(VK_MAX_MEMORY_TYPES);
	m.attr("VK_MAX_MEMORY_HEAPS") = py::int_(VK_MAX_MEMORY_HEAPS);
	m.attr("VK_LOD_CLAMP_NONE") = py::float_(VK_LOD_CLAMP_NONE);
	m.attr("VK_REMAINING_MIP_LEVELS") = py::int_(VK_REMAINING_MIP_LEVELS);
	m.attr("VK_REMAINING_ARRAY_LAYERS") = py::int_(VK_REMAINING_ARRAY_LAYERS);
	m.attr("VK_WHOLE_SIZE") = py::int_(VK_WHOLE_SIZE);
	m.attr("VK_ATTACHMENT_UNUSED") = py::int_(VK_ATTACHMENT_UNUSED);
	m.attr("VK_TRUE") = py::int_(VK_TRUE);
	m.attr("VK_FALSE") = py::int_(VK_FALSE);
	m.attr("VK_QUEUE_FAMILY_IGNORED") = py::int_(VK_QUEUE_FAMILY_IGNORED);
	m.attr("VK_QUEUE_FAMILY_EXTERNAL") = py::int_(VK_QUEUE_FAMILY_EXTERNAL);
	m.attr("VK_QUEUE_FAMILY_EXTERNAL_KHR") = py::int_(VK_QUEUE_FAMILY_EXTERNAL_KHR);
	m.attr("VK_QUEUE_FAMILY_FOREIGN_EXT") = py::int_(VK_QUEUE_FAMILY_FOREIGN_EXT);
	m.attr("VK_SUBPASS_EXTERNAL") = py::int_(VK_SUBPASS_EXTERNAL);
	m.attr("VK_MAX_DEVICE_GROUP_SIZE") = py::int_(VK_MAX_DEVICE_GROUP_SIZE);
	m.attr("VK_MAX_DEVICE_GROUP_SIZE_KHR") = py::int_(VK_MAX_DEVICE_GROUP_SIZE_KHR);
	m.attr("VK_MAX_DRIVER_NAME_SIZE_KHR") = py::int_(VK_MAX_DRIVER_NAME_SIZE_KHR);
	m.attr("VK_MAX_DRIVER_INFO_SIZE_KHR") = py::int_(VK_MAX_DRIVER_INFO_SIZE_KHR);
	m.attr("VK_SHADER_UNUSED_NV") = py::int_(VK_SHADER_UNUSED_NV);

	py::enum_<VkImageLayout>(m, "ImageLayout", py::arithmetic())
		.value("VK_IMAGE_LAYOUT_UNDEFINED", VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED)
		.value("VK_IMAGE_LAYOUT_GENERAL", VkImageLayout::VK_IMAGE_LAYOUT_GENERAL)
		.value("VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL", VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)
		.value("VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL", VkImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
		.value("VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL", VkImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL)
		.value("VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL", VkImageLayout::VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
		.value("VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL", VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL)
		.value("VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL", VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
		.value("VK_IMAGE_LAYOUT_PREINITIALIZED", VkImageLayout::VK_IMAGE_LAYOUT_PREINITIALIZED)
		.export_values();
	py::enum_<VkAttachmentLoadOp>(m, "AttachmentLoadOp", py::arithmetic())
		.value("VK_ATTACHMENT_LOAD_OP_LOAD", VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_LOAD)
		.value("VK_ATTACHMENT_LOAD_OP_CLEAR", VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR)
		.value("VK_ATTACHMENT_LOAD_OP_DONT_CARE", VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE)
		.export_values();
	py::enum_<VkAttachmentStoreOp>(m, "AttachmentStoreOp", py::arithmetic())
		.value("VK_ATTACHMENT_STORE_OP_STORE", VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE)
		.value("VK_ATTACHMENT_STORE_OP_DONT_CARE", VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE)
		.export_values();
	py::enum_<VkImageType>(m, "ImageType", py::arithmetic())
		.value("VK_IMAGE_TYPE_1D", VkImageType::VK_IMAGE_TYPE_1D)
		.value("VK_IMAGE_TYPE_2D", VkImageType::VK_IMAGE_TYPE_2D)
		.value("VK_IMAGE_TYPE_3D", VkImageType::VK_IMAGE_TYPE_3D)
		.export_values();
	py::enum_<VkImageTiling>(m, "ImageTiling", py::arithmetic())
		.value("VK_IMAGE_TILING_OPTIMAL", VkImageTiling::VK_IMAGE_TILING_OPTIMAL)
		.value("VK_IMAGE_TILING_LINEAR", VkImageTiling::VK_IMAGE_TILING_LINEAR)
		.export_values();
	py::enum_<VkImageViewType>(m, "ImageViewType", py::arithmetic())
		.value("VK_IMAGE_VIEW_TYPE_1D", VkImageViewType::VK_IMAGE_VIEW_TYPE_1D)
		.value("VK_IMAGE_VIEW_TYPE_2D", VkImageViewType::VK_IMAGE_VIEW_TYPE_2D)
		.value("VK_IMAGE_VIEW_TYPE_3D", VkImageViewType::VK_IMAGE_VIEW_TYPE_3D)
		.value("VK_IMAGE_VIEW_TYPE_CUBE", VkImageViewType::VK_IMAGE_VIEW_TYPE_CUBE)
		.value("VK_IMAGE_VIEW_TYPE_1D_ARRAY", VkImageViewType::VK_IMAGE_VIEW_TYPE_1D_ARRAY)
		.value("VK_IMAGE_VIEW_TYPE_2D_ARRAY", VkImageViewType::VK_IMAGE_VIEW_TYPE_2D_ARRAY)
		.value("VK_IMAGE_VIEW_TYPE_CUBE_ARRAY", VkImageViewType::VK_IMAGE_VIEW_TYPE_CUBE_ARRAY)
		.export_values();
	py::enum_<VkCommandBufferLevel>(m, "CommandBufferLevel", py::arithmetic())
		.value("VK_COMMAND_BUFFER_LEVEL_PRIMARY", VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY)
		.value("VK_COMMAND_BUFFER_LEVEL_SECONDARY", VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_SECONDARY)
		.export_values();
	py::enum_<VkComponentSwizzle>(m, "ComponentSwizzle", py::arithmetic())
		.value("VK_COMPONENT_SWIZZLE_IDENTITY", VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY)
		.value("VK_COMPONENT_SWIZZLE_ZERO", VkComponentSwizzle::VK_COMPONENT_SWIZZLE_ZERO)
		.value("VK_COMPONENT_SWIZZLE_ONE", VkComponentSwizzle::VK_COMPONENT_SWIZZLE_ONE)
		.value("VK_COMPONENT_SWIZZLE_R", VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R)
		.value("VK_COMPONENT_SWIZZLE_G", VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G)
		.value("VK_COMPONENT_SWIZZLE_B", VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B)
		.value("VK_COMPONENT_SWIZZLE_A", VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A)
		.export_values();
	py::enum_<VkDescriptorType>(m, "DescriptorType", py::arithmetic())
		.value("VK_DESCRIPTOR_TYPE_SAMPLER", VkDescriptorType::VK_DESCRIPTOR_TYPE_SAMPLER)
		.value("VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER", VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
		.value("VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE", VkDescriptorType::VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE)
		.value("VK_DESCRIPTOR_TYPE_STORAGE_IMAGE", VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_IMAGE)
		.value("VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER", VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER)
		.value("VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER", VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER)
		.value("VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER", VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
		.value("VK_DESCRIPTOR_TYPE_STORAGE_BUFFER", VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_BUFFER)
		.value("VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC", VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC)
		.value("VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC", VkDescriptorType::VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC)
		.value("VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT", VkDescriptorType::VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT)
		.export_values();
	py::enum_<VkQueryType>(m, "QueryType", py::arithmetic())
		.value("VK_QUERY_TYPE_OCCLUSION", VkQueryType::VK_QUERY_TYPE_OCCLUSION)
		.value("VK_QUERY_TYPE_PIPELINE_STATISTICS", VkQueryType::VK_QUERY_TYPE_PIPELINE_STATISTICS)
		.value("VK_QUERY_TYPE_TIMESTAMP", VkQueryType::VK_QUERY_TYPE_TIMESTAMP)
		.export_values();
	py::enum_<VkBorderColor>(m, "BorderColor", py::arithmetic())
		.value("VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK", VkBorderColor::VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK)
		.value("VK_BORDER_COLOR_INT_TRANSPARENT_BLACK", VkBorderColor::VK_BORDER_COLOR_INT_TRANSPARENT_BLACK)
		.value("VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK", VkBorderColor::VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK)
		.value("VK_BORDER_COLOR_INT_OPAQUE_BLACK", VkBorderColor::VK_BORDER_COLOR_INT_OPAQUE_BLACK)
		.value("VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE", VkBorderColor::VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE)
		.value("VK_BORDER_COLOR_INT_OPAQUE_WHITE", VkBorderColor::VK_BORDER_COLOR_INT_OPAQUE_WHITE)
		.export_values();
	py::enum_<VkPipelineBindPoint>(m, "PipelineBindPoint", py::arithmetic())
		.value("VK_PIPELINE_BIND_POINT_GRAPHICS", VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS)
		.value("VK_PIPELINE_BIND_POINT_COMPUTE", VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_COMPUTE)
		.export_values();
	py::enum_<VkPipelineCacheHeaderVersion>(m, "PipelineCacheHeaderVersion", py::arithmetic())
		.value("VK_PIPELINE_CACHE_HEADER_VERSION_ONE", VkPipelineCacheHeaderVersion::VK_PIPELINE_CACHE_HEADER_VERSION_ONE)
		.export_values();
	py::enum_<VkPrimitiveTopology>(m, "PrimitiveTopology", py::arithmetic())
		.value("VK_PRIMITIVE_TOPOLOGY_POINT_LIST", VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_POINT_LIST)
		.value("VK_PRIMITIVE_TOPOLOGY_LINE_LIST", VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_LINE_LIST)
		.value("VK_PRIMITIVE_TOPOLOGY_LINE_STRIP", VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_LINE_STRIP)
		.value("VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST", VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
		.value("VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP", VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP)
		.value("VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN", VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN)
		.value("VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY", VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY)
		.value("VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY", VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY)
		.value("VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY", VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY)
		.value("VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY", VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY)
		.value("VK_PRIMITIVE_TOPOLOGY_PATCH_LIST", VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_PATCH_LIST)
		.export_values();
	py::enum_<VkSharingMode>(m, "SharingMode", py::arithmetic())
		.value("VK_SHARING_MODE_EXCLUSIVE", VkSharingMode::VK_SHARING_MODE_EXCLUSIVE)
		.value("VK_SHARING_MODE_CONCURRENT", VkSharingMode::VK_SHARING_MODE_CONCURRENT)
		.export_values();
	py::enum_<VkIndexType>(m, "IndexType", py::arithmetic())
		.value("VK_INDEX_TYPE_UINT16", VkIndexType::VK_INDEX_TYPE_UINT16)
		.value("VK_INDEX_TYPE_UINT32", VkIndexType::VK_INDEX_TYPE_UINT32)
		.export_values();
	py::enum_<VkFilter>(m, "Filter", py::arithmetic())
		.value("VK_FILTER_NEAREST", VkFilter::VK_FILTER_NEAREST)
		.value("VK_FILTER_LINEAR", VkFilter::VK_FILTER_LINEAR)
		.export_values();
	py::enum_<VkSamplerMipmapMode>(m, "SamplerMipmapMode", py::arithmetic())
		.value("VK_SAMPLER_MIPMAP_MODE_NEAREST", VkSamplerMipmapMode::VK_SAMPLER_MIPMAP_MODE_NEAREST)
		.value("VK_SAMPLER_MIPMAP_MODE_LINEAR", VkSamplerMipmapMode::VK_SAMPLER_MIPMAP_MODE_LINEAR)
		.export_values();
	py::enum_<VkSamplerAddressMode>(m, "SamplerAddressMode", py::arithmetic())
		.value("VK_SAMPLER_ADDRESS_MODE_REPEAT", VkSamplerAddressMode::VK_SAMPLER_ADDRESS_MODE_REPEAT)
		.value("VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT", VkSamplerAddressMode::VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT)
		.value("VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE", VkSamplerAddressMode::VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE)
		.value("VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER", VkSamplerAddressMode::VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER)
		.export_values();
	py::enum_<VkCompareOp>(m, "CompareOp", py::arithmetic())
		.value("VK_COMPARE_OP_NEVER", VkCompareOp::VK_COMPARE_OP_NEVER)
		.value("VK_COMPARE_OP_LESS", VkCompareOp::VK_COMPARE_OP_LESS)
		.value("VK_COMPARE_OP_EQUAL", VkCompareOp::VK_COMPARE_OP_EQUAL)
		.value("VK_COMPARE_OP_LESS_OR_EQUAL", VkCompareOp::VK_COMPARE_OP_LESS_OR_EQUAL)
		.value("VK_COMPARE_OP_GREATER", VkCompareOp::VK_COMPARE_OP_GREATER)
		.value("VK_COMPARE_OP_NOT_EQUAL", VkCompareOp::VK_COMPARE_OP_NOT_EQUAL)
		.value("VK_COMPARE_OP_GREATER_OR_EQUAL", VkCompareOp::VK_COMPARE_OP_GREATER_OR_EQUAL)
		.value("VK_COMPARE_OP_ALWAYS", VkCompareOp::VK_COMPARE_OP_ALWAYS)
		.export_values();
	py::enum_<VkPolygonMode>(m, "PolygonMode", py::arithmetic())
		.value("VK_POLYGON_MODE_FILL", VkPolygonMode::VK_POLYGON_MODE_FILL)
		.value("VK_POLYGON_MODE_LINE", VkPolygonMode::VK_POLYGON_MODE_LINE)
		.value("VK_POLYGON_MODE_POINT", VkPolygonMode::VK_POLYGON_MODE_POINT)
		.export_values();
	py::enum_<VkCullModeFlagBits>(m, "CullModeFlagBits", py::arithmetic())
		.value("VK_CULL_MODE_NONE", VkCullModeFlagBits::VK_CULL_MODE_NONE)
		.value("VK_CULL_MODE_FRONT_BIT", VkCullModeFlagBits::VK_CULL_MODE_FRONT_BIT)
		.value("VK_CULL_MODE_BACK_BIT", VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT)
		.value("VK_CULL_MODE_FRONT_AND_BACK", VkCullModeFlagBits::VK_CULL_MODE_FRONT_AND_BACK)
		.export_values();
	py::enum_<VkFrontFace>(m, "FrontFace", py::arithmetic())
		.value("VK_FRONT_FACE_COUNTER_CLOCKWISE", VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE)
		.value("VK_FRONT_FACE_CLOCKWISE", VkFrontFace::VK_FRONT_FACE_CLOCKWISE)
		.export_values();
	py::enum_<VkBlendFactor>(m, "BlendFactor", py::arithmetic())
		.value("VK_BLEND_FACTOR_ZERO", VkBlendFactor::VK_BLEND_FACTOR_ZERO)
		.value("VK_BLEND_FACTOR_ONE", VkBlendFactor::VK_BLEND_FACTOR_ONE)
		.value("VK_BLEND_FACTOR_SRC_COLOR", VkBlendFactor::VK_BLEND_FACTOR_SRC_COLOR)
		.value("VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR", VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR)
		.value("VK_BLEND_FACTOR_DST_COLOR", VkBlendFactor::VK_BLEND_FACTOR_DST_COLOR)
		.value("VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR", VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR)
		.value("VK_BLEND_FACTOR_SRC_ALPHA", VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA)
		.value("VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA", VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA)
		.value("VK_BLEND_FACTOR_DST_ALPHA", VkBlendFactor::VK_BLEND_FACTOR_DST_ALPHA)
		.value("VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA", VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA)
		.value("VK_BLEND_FACTOR_CONSTANT_COLOR", VkBlendFactor::VK_BLEND_FACTOR_CONSTANT_COLOR)
		.value("VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR", VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR)
		.value("VK_BLEND_FACTOR_CONSTANT_ALPHA", VkBlendFactor::VK_BLEND_FACTOR_CONSTANT_ALPHA)
		.value("VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA", VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA)
		.value("VK_BLEND_FACTOR_SRC_ALPHA_SATURATE", VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA_SATURATE)
		.value("VK_BLEND_FACTOR_SRC1_COLOR", VkBlendFactor::VK_BLEND_FACTOR_SRC1_COLOR)
		.value("VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR", VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR)
		.value("VK_BLEND_FACTOR_SRC1_ALPHA", VkBlendFactor::VK_BLEND_FACTOR_SRC1_ALPHA)
		.value("VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA", VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA)
		.export_values();
	py::enum_<VkBlendOp>(m, "BlendOp", py::arithmetic())
		.value("VK_BLEND_OP_ADD", VkBlendOp::VK_BLEND_OP_ADD)
		.value("VK_BLEND_OP_SUBTRACT", VkBlendOp::VK_BLEND_OP_SUBTRACT)
		.value("VK_BLEND_OP_REVERSE_SUBTRACT", VkBlendOp::VK_BLEND_OP_REVERSE_SUBTRACT)
		.value("VK_BLEND_OP_MIN", VkBlendOp::VK_BLEND_OP_MIN)
		.value("VK_BLEND_OP_MAX", VkBlendOp::VK_BLEND_OP_MAX)
		.export_values();
	py::enum_<VkStencilOp>(m, "StencilOp", py::arithmetic())
		.value("VK_STENCIL_OP_KEEP", VkStencilOp::VK_STENCIL_OP_KEEP)
		.value("VK_STENCIL_OP_ZERO", VkStencilOp::VK_STENCIL_OP_ZERO)
		.value("VK_STENCIL_OP_REPLACE", VkStencilOp::VK_STENCIL_OP_REPLACE)
		.value("VK_STENCIL_OP_INCREMENT_AND_CLAMP", VkStencilOp::VK_STENCIL_OP_INCREMENT_AND_CLAMP)
		.value("VK_STENCIL_OP_DECREMENT_AND_CLAMP", VkStencilOp::VK_STENCIL_OP_DECREMENT_AND_CLAMP)
		.value("VK_STENCIL_OP_INVERT", VkStencilOp::VK_STENCIL_OP_INVERT)
		.value("VK_STENCIL_OP_INCREMENT_AND_WRAP", VkStencilOp::VK_STENCIL_OP_INCREMENT_AND_WRAP)
		.value("VK_STENCIL_OP_DECREMENT_AND_WRAP", VkStencilOp::VK_STENCIL_OP_DECREMENT_AND_WRAP)
		.export_values();
	py::enum_<VkLogicOp>(m, "LogicOp", py::arithmetic())
		.value("VK_LOGIC_OP_CLEAR", VkLogicOp::VK_LOGIC_OP_CLEAR)
		.value("VK_LOGIC_OP_AND", VkLogicOp::VK_LOGIC_OP_AND)
		.value("VK_LOGIC_OP_AND_REVERSE", VkLogicOp::VK_LOGIC_OP_AND_REVERSE)
		.value("VK_LOGIC_OP_COPY", VkLogicOp::VK_LOGIC_OP_COPY)
		.value("VK_LOGIC_OP_AND_INVERTED", VkLogicOp::VK_LOGIC_OP_AND_INVERTED)
		.value("VK_LOGIC_OP_NO_OP", VkLogicOp::VK_LOGIC_OP_NO_OP)
		.value("VK_LOGIC_OP_XOR", VkLogicOp::VK_LOGIC_OP_XOR)
		.value("VK_LOGIC_OP_OR", VkLogicOp::VK_LOGIC_OP_OR)
		.value("VK_LOGIC_OP_NOR", VkLogicOp::VK_LOGIC_OP_NOR)
		.value("VK_LOGIC_OP_EQUIVALENT", VkLogicOp::VK_LOGIC_OP_EQUIVALENT)
		.value("VK_LOGIC_OP_INVERT", VkLogicOp::VK_LOGIC_OP_INVERT)
		.value("VK_LOGIC_OP_OR_REVERSE", VkLogicOp::VK_LOGIC_OP_OR_REVERSE)
		.value("VK_LOGIC_OP_COPY_INVERTED", VkLogicOp::VK_LOGIC_OP_COPY_INVERTED)
		.value("VK_LOGIC_OP_OR_INVERTED", VkLogicOp::VK_LOGIC_OP_OR_INVERTED)
		.value("VK_LOGIC_OP_NAND", VkLogicOp::VK_LOGIC_OP_NAND)
		.value("VK_LOGIC_OP_SET", VkLogicOp::VK_LOGIC_OP_SET)
		.export_values();
	py::enum_<VkInternalAllocationType>(m, "InternalAllocationType", py::arithmetic())
		.value("VK_INTERNAL_ALLOCATION_TYPE_EXECUTABLE", VkInternalAllocationType::VK_INTERNAL_ALLOCATION_TYPE_EXECUTABLE)
		.export_values();
	py::enum_<VkSystemAllocationScope>(m, "SystemAllocationScope", py::arithmetic())
		.value("VK_SYSTEM_ALLOCATION_SCOPE_COMMAND", VkSystemAllocationScope::VK_SYSTEM_ALLOCATION_SCOPE_COMMAND)
		.value("VK_SYSTEM_ALLOCATION_SCOPE_OBJECT", VkSystemAllocationScope::VK_SYSTEM_ALLOCATION_SCOPE_OBJECT)
		.value("VK_SYSTEM_ALLOCATION_SCOPE_CACHE", VkSystemAllocationScope::VK_SYSTEM_ALLOCATION_SCOPE_CACHE)
		.value("VK_SYSTEM_ALLOCATION_SCOPE_DEVICE", VkSystemAllocationScope::VK_SYSTEM_ALLOCATION_SCOPE_DEVICE)
		.value("VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE", VkSystemAllocationScope::VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE)
		.export_values();
	py::enum_<VkPhysicalDeviceType>(m, "PhysicalDeviceType", py::arithmetic())
		.value("VK_PHYSICAL_DEVICE_TYPE_OTHER", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_OTHER)
		.value("VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
		.value("VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		.value("VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU)
		.value("VK_PHYSICAL_DEVICE_TYPE_CPU", VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU)
		.export_values();
	py::enum_<VkVertexInputRate>(m, "VertexInputRate", py::arithmetic())
		.value("VK_VERTEX_INPUT_RATE_VERTEX", VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX)
		.value("VK_VERTEX_INPUT_RATE_INSTANCE", VkVertexInputRate::VK_VERTEX_INPUT_RATE_INSTANCE)
		.export_values();
	py::enum_<VkFormat>(m, "Format", py::arithmetic())
		.value("VK_FORMAT_UNDEFINED", VkFormat::VK_FORMAT_UNDEFINED)
		.value("VK_FORMAT_R4G4_UNORM_PACK8", VkFormat::VK_FORMAT_R4G4_UNORM_PACK8)
		.value("VK_FORMAT_R4G4B4A4_UNORM_PACK16", VkFormat::VK_FORMAT_R4G4B4A4_UNORM_PACK16)
		.value("VK_FORMAT_B4G4R4A4_UNORM_PACK16", VkFormat::VK_FORMAT_B4G4R4A4_UNORM_PACK16)
		.value("VK_FORMAT_R5G6B5_UNORM_PACK16", VkFormat::VK_FORMAT_R5G6B5_UNORM_PACK16)
		.value("VK_FORMAT_B5G6R5_UNORM_PACK16", VkFormat::VK_FORMAT_B5G6R5_UNORM_PACK16)
		.value("VK_FORMAT_R5G5B5A1_UNORM_PACK16", VkFormat::VK_FORMAT_R5G5B5A1_UNORM_PACK16)
		.value("VK_FORMAT_B5G5R5A1_UNORM_PACK16", VkFormat::VK_FORMAT_B5G5R5A1_UNORM_PACK16)
		.value("VK_FORMAT_A1R5G5B5_UNORM_PACK16", VkFormat::VK_FORMAT_A1R5G5B5_UNORM_PACK16)
		.value("VK_FORMAT_R8_UNORM", VkFormat::VK_FORMAT_R8_UNORM)
		.value("VK_FORMAT_R8_SNORM", VkFormat::VK_FORMAT_R8_SNORM)
		.value("VK_FORMAT_R8_USCALED", VkFormat::VK_FORMAT_R8_USCALED)
		.value("VK_FORMAT_R8_SSCALED", VkFormat::VK_FORMAT_R8_SSCALED)
		.value("VK_FORMAT_R8_UINT", VkFormat::VK_FORMAT_R8_UINT)
		.value("VK_FORMAT_R8_SINT", VkFormat::VK_FORMAT_R8_SINT)
		.value("VK_FORMAT_R8_SRGB", VkFormat::VK_FORMAT_R8_SRGB)
		.value("VK_FORMAT_R8G8_UNORM", VkFormat::VK_FORMAT_R8G8_UNORM)
		.value("VK_FORMAT_R8G8_SNORM", VkFormat::VK_FORMAT_R8G8_SNORM)
		.value("VK_FORMAT_R8G8_USCALED", VkFormat::VK_FORMAT_R8G8_USCALED)
		.value("VK_FORMAT_R8G8_SSCALED", VkFormat::VK_FORMAT_R8G8_SSCALED)
		.value("VK_FORMAT_R8G8_UINT", VkFormat::VK_FORMAT_R8G8_UINT)
		.value("VK_FORMAT_R8G8_SINT", VkFormat::VK_FORMAT_R8G8_SINT)
		.value("VK_FORMAT_R8G8_SRGB", VkFormat::VK_FORMAT_R8G8_SRGB)
		.value("VK_FORMAT_R8G8B8_UNORM", VkFormat::VK_FORMAT_R8G8B8_UNORM)
		.value("VK_FORMAT_R8G8B8_SNORM", VkFormat::VK_FORMAT_R8G8B8_SNORM)
		.value("VK_FORMAT_R8G8B8_USCALED", VkFormat::VK_FORMAT_R8G8B8_USCALED)
		.value("VK_FORMAT_R8G8B8_SSCALED", VkFormat::VK_FORMAT_R8G8B8_SSCALED)
		.value("VK_FORMAT_R8G8B8_UINT", VkFormat::VK_FORMAT_R8G8B8_UINT)
		.value("VK_FORMAT_R8G8B8_SINT", VkFormat::VK_FORMAT_R8G8B8_SINT)
		.value("VK_FORMAT_R8G8B8_SRGB", VkFormat::VK_FORMAT_R8G8B8_SRGB)
		.value("VK_FORMAT_B8G8R8_UNORM", VkFormat::VK_FORMAT_B8G8R8_UNORM)
		.value("VK_FORMAT_B8G8R8_SNORM", VkFormat::VK_FORMAT_B8G8R8_SNORM)
		.value("VK_FORMAT_B8G8R8_USCALED", VkFormat::VK_FORMAT_B8G8R8_USCALED)
		.value("VK_FORMAT_B8G8R8_SSCALED", VkFormat::VK_FORMAT_B8G8R8_SSCALED)
		.value("VK_FORMAT_B8G8R8_UINT", VkFormat::VK_FORMAT_B8G8R8_UINT)
		.value("VK_FORMAT_B8G8R8_SINT", VkFormat::VK_FORMAT_B8G8R8_SINT)
		.value("VK_FORMAT_B8G8R8_SRGB", VkFormat::VK_FORMAT_B8G8R8_SRGB)
		.value("VK_FORMAT_R8G8B8A8_UNORM", VkFormat::VK_FORMAT_R8G8B8A8_UNORM)
		.value("VK_FORMAT_R8G8B8A8_SNORM", VkFormat::VK_FORMAT_R8G8B8A8_SNORM)
		.value("VK_FORMAT_R8G8B8A8_USCALED", VkFormat::VK_FORMAT_R8G8B8A8_USCALED)
		.value("VK_FORMAT_R8G8B8A8_SSCALED", VkFormat::VK_FORMAT_R8G8B8A8_SSCALED)
		.value("VK_FORMAT_R8G8B8A8_UINT", VkFormat::VK_FORMAT_R8G8B8A8_UINT)
		.value("VK_FORMAT_R8G8B8A8_SINT", VkFormat::VK_FORMAT_R8G8B8A8_SINT)
		.value("VK_FORMAT_R8G8B8A8_SRGB", VkFormat::VK_FORMAT_R8G8B8A8_SRGB)
		.value("VK_FORMAT_B8G8R8A8_UNORM", VkFormat::VK_FORMAT_B8G8R8A8_UNORM)
		.value("VK_FORMAT_B8G8R8A8_SNORM", VkFormat::VK_FORMAT_B8G8R8A8_SNORM)
		.value("VK_FORMAT_B8G8R8A8_USCALED", VkFormat::VK_FORMAT_B8G8R8A8_USCALED)
		.value("VK_FORMAT_B8G8R8A8_SSCALED", VkFormat::VK_FORMAT_B8G8R8A8_SSCALED)
		.value("VK_FORMAT_B8G8R8A8_UINT", VkFormat::VK_FORMAT_B8G8R8A8_UINT)
		.value("VK_FORMAT_B8G8R8A8_SINT", VkFormat::VK_FORMAT_B8G8R8A8_SINT)
		.value("VK_FORMAT_B8G8R8A8_SRGB", VkFormat::VK_FORMAT_B8G8R8A8_SRGB)
		.value("VK_FORMAT_A8B8G8R8_UNORM_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_UNORM_PACK32)
		.value("VK_FORMAT_A8B8G8R8_SNORM_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_SNORM_PACK32)
		.value("VK_FORMAT_A8B8G8R8_USCALED_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_USCALED_PACK32)
		.value("VK_FORMAT_A8B8G8R8_SSCALED_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_SSCALED_PACK32)
		.value("VK_FORMAT_A8B8G8R8_UINT_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_UINT_PACK32)
		.value("VK_FORMAT_A8B8G8R8_SINT_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_SINT_PACK32)
		.value("VK_FORMAT_A8B8G8R8_SRGB_PACK32", VkFormat::VK_FORMAT_A8B8G8R8_SRGB_PACK32)
		.value("VK_FORMAT_A2R10G10B10_UNORM_PACK32", VkFormat::VK_FORMAT_A2R10G10B10_UNORM_PACK32)
		.value("VK_FORMAT_A2R10G10B10_SNORM_PACK32", VkFormat::VK_FORMAT_A2R10G10B10_SNORM_PACK32)
		.value("VK_FORMAT_A2R10G10B10_USCALED_PACK32", VkFormat::VK_FORMAT_A2R10G10B10_USCALED_PACK32)
		.value("VK_FORMAT_A2R10G10B10_SSCALED_PACK32", VkFormat::VK_FORMAT_A2R10G10B10_SSCALED_PACK32)
		.value("VK_FORMAT_A2R10G10B10_UINT_PACK32", VkFormat::VK_FORMAT_A2R10G10B10_UINT_PACK32)
		.value("VK_FORMAT_A2R10G10B10_SINT_PACK32", VkFormat::VK_FORMAT_A2R10G10B10_SINT_PACK32)
		.value("VK_FORMAT_A2B10G10R10_UNORM_PACK32", VkFormat::VK_FORMAT_A2B10G10R10_UNORM_PACK32)
		.value("VK_FORMAT_A2B10G10R10_SNORM_PACK32", VkFormat::VK_FORMAT_A2B10G10R10_SNORM_PACK32)
		.value("VK_FORMAT_A2B10G10R10_USCALED_PACK32", VkFormat::VK_FORMAT_A2B10G10R10_USCALED_PACK32)
		.value("VK_FORMAT_A2B10G10R10_SSCALED_PACK32", VkFormat::VK_FORMAT_A2B10G10R10_SSCALED_PACK32)
		.value("VK_FORMAT_A2B10G10R10_UINT_PACK32", VkFormat::VK_FORMAT_A2B10G10R10_UINT_PACK32)
		.value("VK_FORMAT_A2B10G10R10_SINT_PACK32", VkFormat::VK_FORMAT_A2B10G10R10_SINT_PACK32)
		.value("VK_FORMAT_R16_UNORM", VkFormat::VK_FORMAT_R16_UNORM)
		.value("VK_FORMAT_R16_SNORM", VkFormat::VK_FORMAT_R16_SNORM)
		.value("VK_FORMAT_R16_USCALED", VkFormat::VK_FORMAT_R16_USCALED)
		.value("VK_FORMAT_R16_SSCALED", VkFormat::VK_FORMAT_R16_SSCALED)
		.value("VK_FORMAT_R16_UINT", VkFormat::VK_FORMAT_R16_UINT)
		.value("VK_FORMAT_R16_SINT", VkFormat::VK_FORMAT_R16_SINT)
		.value("VK_FORMAT_R16_SFLOAT", VkFormat::VK_FORMAT_R16_SFLOAT)
		.value("VK_FORMAT_R16G16_UNORM", VkFormat::VK_FORMAT_R16G16_UNORM)
		.value("VK_FORMAT_R16G16_SNORM", VkFormat::VK_FORMAT_R16G16_SNORM)
		.value("VK_FORMAT_R16G16_USCALED", VkFormat::VK_FORMAT_R16G16_USCALED)
		.value("VK_FORMAT_R16G16_SSCALED", VkFormat::VK_FORMAT_R16G16_SSCALED)
		.value("VK_FORMAT_R16G16_UINT", VkFormat::VK_FORMAT_R16G16_UINT)
		.value("VK_FORMAT_R16G16_SINT", VkFormat::VK_FORMAT_R16G16_SINT)
		.value("VK_FORMAT_R16G16_SFLOAT", VkFormat::VK_FORMAT_R16G16_SFLOAT)
		.value("VK_FORMAT_R16G16B16_UNORM", VkFormat::VK_FORMAT_R16G16B16_UNORM)
		.value("VK_FORMAT_R16G16B16_SNORM", VkFormat::VK_FORMAT_R16G16B16_SNORM)
		.value("VK_FORMAT_R16G16B16_USCALED", VkFormat::VK_FORMAT_R16G16B16_USCALED)
		.value("VK_FORMAT_R16G16B16_SSCALED", VkFormat::VK_FORMAT_R16G16B16_SSCALED)
		.value("VK_FORMAT_R16G16B16_UINT", VkFormat::VK_FORMAT_R16G16B16_UINT)
		.value("VK_FORMAT_R16G16B16_SINT", VkFormat::VK_FORMAT_R16G16B16_SINT)
		.value("VK_FORMAT_R16G16B16_SFLOAT", VkFormat::VK_FORMAT_R16G16B16_SFLOAT)
		.value("VK_FORMAT_R16G16B16A16_UNORM", VkFormat::VK_FORMAT_R16G16B16A16_UNORM)
		.value("VK_FORMAT_R16G16B16A16_SNORM", VkFormat::VK_FORMAT_R16G16B16A16_SNORM)
		.value("VK_FORMAT_R16G16B16A16_USCALED", VkFormat::VK_FORMAT_R16G16B16A16_USCALED)
		.value("VK_FORMAT_R16G16B16A16_SSCALED", VkFormat::VK_FORMAT_R16G16B16A16_SSCALED)
		.value("VK_FORMAT_R16G16B16A16_UINT", VkFormat::VK_FORMAT_R16G16B16A16_UINT)
		.value("VK_FORMAT_R16G16B16A16_SINT", VkFormat::VK_FORMAT_R16G16B16A16_SINT)
		.value("VK_FORMAT_R16G16B16A16_SFLOAT", VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT)
		.value("VK_FORMAT_R32_UINT", VkFormat::VK_FORMAT_R32_UINT)
		.value("VK_FORMAT_R32_SINT", VkFormat::VK_FORMAT_R32_SINT)
		.value("VK_FORMAT_R32_SFLOAT", VkFormat::VK_FORMAT_R32_SFLOAT)
		.value("VK_FORMAT_R32G32_UINT", VkFormat::VK_FORMAT_R32G32_UINT)
		.value("VK_FORMAT_R32G32_SINT", VkFormat::VK_FORMAT_R32G32_SINT)
		.value("VK_FORMAT_R32G32_SFLOAT", VkFormat::VK_FORMAT_R32G32_SFLOAT)
		.value("VK_FORMAT_R32G32B32_UINT", VkFormat::VK_FORMAT_R32G32B32_UINT)
		.value("VK_FORMAT_R32G32B32_SINT", VkFormat::VK_FORMAT_R32G32B32_SINT)
		.value("VK_FORMAT_R32G32B32_SFLOAT", VkFormat::VK_FORMAT_R32G32B32_SFLOAT)
		.value("VK_FORMAT_R32G32B32A32_UINT", VkFormat::VK_FORMAT_R32G32B32A32_UINT)
		.value("VK_FORMAT_R32G32B32A32_SINT", VkFormat::VK_FORMAT_R32G32B32A32_SINT)
		.value("VK_FORMAT_R32G32B32A32_SFLOAT", VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT)
		.value("VK_FORMAT_R64_UINT", VkFormat::VK_FORMAT_R64_UINT)
		.value("VK_FORMAT_R64_SINT", VkFormat::VK_FORMAT_R64_SINT)
		.value("VK_FORMAT_R64_SFLOAT", VkFormat::VK_FORMAT_R64_SFLOAT)
		.value("VK_FORMAT_R64G64_UINT", VkFormat::VK_FORMAT_R64G64_UINT)
		.value("VK_FORMAT_R64G64_SINT", VkFormat::VK_FORMAT_R64G64_SINT)
		.value("VK_FORMAT_R64G64_SFLOAT", VkFormat::VK_FORMAT_R64G64_SFLOAT)
		.value("VK_FORMAT_R64G64B64_UINT", VkFormat::VK_FORMAT_R64G64B64_UINT)
		.value("VK_FORMAT_R64G64B64_SINT", VkFormat::VK_FORMAT_R64G64B64_SINT)
		.value("VK_FORMAT_R64G64B64_SFLOAT", VkFormat::VK_FORMAT_R64G64B64_SFLOAT)
		.value("VK_FORMAT_R64G64B64A64_UINT", VkFormat::VK_FORMAT_R64G64B64A64_UINT)
		.value("VK_FORMAT_R64G64B64A64_SINT", VkFormat::VK_FORMAT_R64G64B64A64_SINT)
		.value("VK_FORMAT_R64G64B64A64_SFLOAT", VkFormat::VK_FORMAT_R64G64B64A64_SFLOAT)
		.value("VK_FORMAT_B10G11R11_UFLOAT_PACK32", VkFormat::VK_FORMAT_B10G11R11_UFLOAT_PACK32)
		.value("VK_FORMAT_E5B9G9R9_UFLOAT_PACK32", VkFormat::VK_FORMAT_E5B9G9R9_UFLOAT_PACK32)
		.value("VK_FORMAT_D16_UNORM", VkFormat::VK_FORMAT_D16_UNORM)
		.value("VK_FORMAT_X8_D24_UNORM_PACK32", VkFormat::VK_FORMAT_X8_D24_UNORM_PACK32)
		.value("VK_FORMAT_D32_SFLOAT", VkFormat::VK_FORMAT_D32_SFLOAT)
		.value("VK_FORMAT_S8_UINT", VkFormat::VK_FORMAT_S8_UINT)
		.value("VK_FORMAT_D16_UNORM_S8_UINT", VkFormat::VK_FORMAT_D16_UNORM_S8_UINT)
		.value("VK_FORMAT_D24_UNORM_S8_UINT", VkFormat::VK_FORMAT_D24_UNORM_S8_UINT)
		.value("VK_FORMAT_D32_SFLOAT_S8_UINT", VkFormat::VK_FORMAT_D32_SFLOAT_S8_UINT)
		.value("VK_FORMAT_BC1_RGB_UNORM_BLOCK", VkFormat::VK_FORMAT_BC1_RGB_UNORM_BLOCK)
		.value("VK_FORMAT_BC1_RGB_SRGB_BLOCK", VkFormat::VK_FORMAT_BC1_RGB_SRGB_BLOCK)
		.value("VK_FORMAT_BC1_RGBA_UNORM_BLOCK", VkFormat::VK_FORMAT_BC1_RGBA_UNORM_BLOCK)
		.value("VK_FORMAT_BC1_RGBA_SRGB_BLOCK", VkFormat::VK_FORMAT_BC1_RGBA_SRGB_BLOCK)
		.value("VK_FORMAT_BC2_UNORM_BLOCK", VkFormat::VK_FORMAT_BC2_UNORM_BLOCK)
		.value("VK_FORMAT_BC2_SRGB_BLOCK", VkFormat::VK_FORMAT_BC2_SRGB_BLOCK)
		.value("VK_FORMAT_BC3_UNORM_BLOCK", VkFormat::VK_FORMAT_BC3_UNORM_BLOCK)
		.value("VK_FORMAT_BC3_SRGB_BLOCK", VkFormat::VK_FORMAT_BC3_SRGB_BLOCK)
		.value("VK_FORMAT_BC4_UNORM_BLOCK", VkFormat::VK_FORMAT_BC4_UNORM_BLOCK)
		.value("VK_FORMAT_BC4_SNORM_BLOCK", VkFormat::VK_FORMAT_BC4_SNORM_BLOCK)
		.value("VK_FORMAT_BC5_UNORM_BLOCK", VkFormat::VK_FORMAT_BC5_UNORM_BLOCK)
		.value("VK_FORMAT_BC5_SNORM_BLOCK", VkFormat::VK_FORMAT_BC5_SNORM_BLOCK)
		.value("VK_FORMAT_BC6H_UFLOAT_BLOCK", VkFormat::VK_FORMAT_BC6H_UFLOAT_BLOCK)
		.value("VK_FORMAT_BC6H_SFLOAT_BLOCK", VkFormat::VK_FORMAT_BC6H_SFLOAT_BLOCK)
		.value("VK_FORMAT_BC7_UNORM_BLOCK", VkFormat::VK_FORMAT_BC7_UNORM_BLOCK)
		.value("VK_FORMAT_BC7_SRGB_BLOCK", VkFormat::VK_FORMAT_BC7_SRGB_BLOCK)
		.value("VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK", VkFormat::VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK)
		.value("VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK", VkFormat::VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK)
		.value("VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK", VkFormat::VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK)
		.value("VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK", VkFormat::VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK)
		.value("VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK", VkFormat::VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK)
		.value("VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK", VkFormat::VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK)
		.value("VK_FORMAT_EAC_R11_UNORM_BLOCK", VkFormat::VK_FORMAT_EAC_R11_UNORM_BLOCK)
		.value("VK_FORMAT_EAC_R11_SNORM_BLOCK", VkFormat::VK_FORMAT_EAC_R11_SNORM_BLOCK)
		.value("VK_FORMAT_EAC_R11G11_UNORM_BLOCK", VkFormat::VK_FORMAT_EAC_R11G11_UNORM_BLOCK)
		.value("VK_FORMAT_EAC_R11G11_SNORM_BLOCK", VkFormat::VK_FORMAT_EAC_R11G11_SNORM_BLOCK)
		.value("VK_FORMAT_ASTC_4x4_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_4x4_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_4x4_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_4x4_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_5x4_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_5x4_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_5x4_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_5x4_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_5x5_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_5x5_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_5x5_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_5x5_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_6x5_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_6x5_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_6x5_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_6x5_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_6x6_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_6x6_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_6x6_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_6x6_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_8x5_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_8x5_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_8x5_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_8x5_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_8x6_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_8x6_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_8x6_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_8x6_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_8x8_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_8x8_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_8x8_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_8x8_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_10x5_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_10x5_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_10x5_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_10x5_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_10x6_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_10x6_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_10x6_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_10x6_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_10x8_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_10x8_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_10x8_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_10x8_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_10x10_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_10x10_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_10x10_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_10x10_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_12x10_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_12x10_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_12x10_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_12x10_SRGB_BLOCK)
		.value("VK_FORMAT_ASTC_12x12_UNORM_BLOCK", VkFormat::VK_FORMAT_ASTC_12x12_UNORM_BLOCK)
		.value("VK_FORMAT_ASTC_12x12_SRGB_BLOCK", VkFormat::VK_FORMAT_ASTC_12x12_SRGB_BLOCK)
		.export_values();
	py::enum_<VkStructureType>(m, "StructureType", py::arithmetic())
		.value("VK_STRUCTURE_TYPE_APPLICATION_INFO", VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO)
		.value("VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_SUBMIT_INFO", VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO)
		.value("VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO)
		.value("VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE", VkStructureType::VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE)
		.value("VK_STRUCTURE_TYPE_BIND_SPARSE_INFO", VkStructureType::VK_STRUCTURE_TYPE_BIND_SPARSE_INFO)
		.value("VK_STRUCTURE_TYPE_FENCE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_EVENT_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_EVENT_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO)
		.value("VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET", VkStructureType::VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET)
		.value("VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET", VkStructureType::VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET)
		.value("VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO)
		.value("VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO", VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO)
		.value("VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO", VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO)
		.value("VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO", VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO)
		.value("VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER", VkStructureType::VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER)
		.value("VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER", VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER)
		.value("VK_STRUCTURE_TYPE_MEMORY_BARRIER", VkStructureType::VK_STRUCTURE_TYPE_MEMORY_BARRIER)
		.value("VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO)
		.value("VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO", VkStructureType::VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO)
		.export_values();
	py::enum_<VkSubpassContents>(m, "SubpassContents", py::arithmetic())
		.value("VK_SUBPASS_CONTENTS_INLINE", VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE)
		.value("VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS", VkSubpassContents::VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS)
		.export_values();
	py::enum_<VkResult>(m, "Result", py::arithmetic())
		.value("VK_SUCCESS", VkResult::VK_SUCCESS)
		.value("VK_NOT_READY", VkResult::VK_NOT_READY)
		.value("VK_TIMEOUT", VkResult::VK_TIMEOUT)
		.value("VK_EVENT_SET", VkResult::VK_EVENT_SET)
		.value("VK_EVENT_RESET", VkResult::VK_EVENT_RESET)
		.value("VK_INCOMPLETE", VkResult::VK_INCOMPLETE)
		.value("VK_ERROR_OUT_OF_HOST_MEMORY", VkResult::VK_ERROR_OUT_OF_HOST_MEMORY)
		.value("VK_ERROR_OUT_OF_DEVICE_MEMORY", VkResult::VK_ERROR_OUT_OF_DEVICE_MEMORY)
		.value("VK_ERROR_INITIALIZATION_FAILED", VkResult::VK_ERROR_INITIALIZATION_FAILED)
		.value("VK_ERROR_DEVICE_LOST", VkResult::VK_ERROR_DEVICE_LOST)
		.value("VK_ERROR_MEMORY_MAP_FAILED", VkResult::VK_ERROR_MEMORY_MAP_FAILED)
		.value("VK_ERROR_LAYER_NOT_PRESENT", VkResult::VK_ERROR_LAYER_NOT_PRESENT)
		.value("VK_ERROR_EXTENSION_NOT_PRESENT", VkResult::VK_ERROR_EXTENSION_NOT_PRESENT)
		.value("VK_ERROR_FEATURE_NOT_PRESENT", VkResult::VK_ERROR_FEATURE_NOT_PRESENT)
		.value("VK_ERROR_INCOMPATIBLE_DRIVER", VkResult::VK_ERROR_INCOMPATIBLE_DRIVER)
		.value("VK_ERROR_TOO_MANY_OBJECTS", VkResult::VK_ERROR_TOO_MANY_OBJECTS)
		.value("VK_ERROR_FORMAT_NOT_SUPPORTED", VkResult::VK_ERROR_FORMAT_NOT_SUPPORTED)
		.value("VK_ERROR_FRAGMENTED_POOL", VkResult::VK_ERROR_FRAGMENTED_POOL)
		.export_values();
	py::enum_<VkDynamicState>(m, "DynamicState", py::arithmetic())
		.value("VK_DYNAMIC_STATE_VIEWPORT", VkDynamicState::VK_DYNAMIC_STATE_VIEWPORT)
		.value("VK_DYNAMIC_STATE_SCISSOR", VkDynamicState::VK_DYNAMIC_STATE_SCISSOR)
		.value("VK_DYNAMIC_STATE_LINE_WIDTH", VkDynamicState::VK_DYNAMIC_STATE_LINE_WIDTH)
		.value("VK_DYNAMIC_STATE_DEPTH_BIAS", VkDynamicState::VK_DYNAMIC_STATE_DEPTH_BIAS)
		.value("VK_DYNAMIC_STATE_BLEND_CONSTANTS", VkDynamicState::VK_DYNAMIC_STATE_BLEND_CONSTANTS)
		.value("VK_DYNAMIC_STATE_DEPTH_BOUNDS", VkDynamicState::VK_DYNAMIC_STATE_DEPTH_BOUNDS)
		.value("VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK", VkDynamicState::VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK)
		.value("VK_DYNAMIC_STATE_STENCIL_WRITE_MASK", VkDynamicState::VK_DYNAMIC_STATE_STENCIL_WRITE_MASK)
		.value("VK_DYNAMIC_STATE_STENCIL_REFERENCE", VkDynamicState::VK_DYNAMIC_STATE_STENCIL_REFERENCE)
		.export_values();
	py::enum_<VkDescriptorUpdateTemplateType>(m, "DescriptorUpdateTemplateType", py::arithmetic())
		.value("VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET", VkDescriptorUpdateTemplateType::VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET)
		.export_values();
	py::enum_<VkObjectType>(m, "ObjectType", py::arithmetic())
		.value("VK_OBJECT_TYPE_UNKNOWN", VkObjectType::VK_OBJECT_TYPE_UNKNOWN)
		.value("VK_OBJECT_TYPE_INSTANCE", VkObjectType::VK_OBJECT_TYPE_INSTANCE)
		.value("VK_OBJECT_TYPE_PHYSICAL_DEVICE", VkObjectType::VK_OBJECT_TYPE_PHYSICAL_DEVICE)
		.value("VK_OBJECT_TYPE_DEVICE", VkObjectType::VK_OBJECT_TYPE_DEVICE)
		.value("VK_OBJECT_TYPE_QUEUE", VkObjectType::VK_OBJECT_TYPE_QUEUE)
		.value("VK_OBJECT_TYPE_SEMAPHORE", VkObjectType::VK_OBJECT_TYPE_SEMAPHORE)
		.value("VK_OBJECT_TYPE_COMMAND_BUFFER", VkObjectType::VK_OBJECT_TYPE_COMMAND_BUFFER)
		.value("VK_OBJECT_TYPE_FENCE", VkObjectType::VK_OBJECT_TYPE_FENCE)
		.value("VK_OBJECT_TYPE_DEVICE_MEMORY", VkObjectType::VK_OBJECT_TYPE_DEVICE_MEMORY)
		.value("VK_OBJECT_TYPE_BUFFER", VkObjectType::VK_OBJECT_TYPE_BUFFER)
		.value("VK_OBJECT_TYPE_IMAGE", VkObjectType::VK_OBJECT_TYPE_IMAGE)
		.value("VK_OBJECT_TYPE_EVENT", VkObjectType::VK_OBJECT_TYPE_EVENT)
		.value("VK_OBJECT_TYPE_QUERY_POOL", VkObjectType::VK_OBJECT_TYPE_QUERY_POOL)
		.value("VK_OBJECT_TYPE_BUFFER_VIEW", VkObjectType::VK_OBJECT_TYPE_BUFFER_VIEW)
		.value("VK_OBJECT_TYPE_IMAGE_VIEW", VkObjectType::VK_OBJECT_TYPE_IMAGE_VIEW)
		.value("VK_OBJECT_TYPE_SHADER_MODULE", VkObjectType::VK_OBJECT_TYPE_SHADER_MODULE)
		.value("VK_OBJECT_TYPE_PIPELINE_CACHE", VkObjectType::VK_OBJECT_TYPE_PIPELINE_CACHE)
		.value("VK_OBJECT_TYPE_PIPELINE_LAYOUT", VkObjectType::VK_OBJECT_TYPE_PIPELINE_LAYOUT)
		.value("VK_OBJECT_TYPE_RENDER_PASS", VkObjectType::VK_OBJECT_TYPE_RENDER_PASS)
		.value("VK_OBJECT_TYPE_PIPELINE", VkObjectType::VK_OBJECT_TYPE_PIPELINE)
		.value("VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT", VkObjectType::VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT)
		.value("VK_OBJECT_TYPE_SAMPLER", VkObjectType::VK_OBJECT_TYPE_SAMPLER)
		.value("VK_OBJECT_TYPE_DESCRIPTOR_POOL", VkObjectType::VK_OBJECT_TYPE_DESCRIPTOR_POOL)
		.value("VK_OBJECT_TYPE_DESCRIPTOR_SET", VkObjectType::VK_OBJECT_TYPE_DESCRIPTOR_SET)
		.value("VK_OBJECT_TYPE_FRAMEBUFFER", VkObjectType::VK_OBJECT_TYPE_FRAMEBUFFER)
		.value("VK_OBJECT_TYPE_COMMAND_POOL", VkObjectType::VK_OBJECT_TYPE_COMMAND_POOL)
		.export_values();
	py::enum_<VkQueueFlagBits>(m, "QueueFlagBits", py::arithmetic())
		.value("VK_QUEUE_GRAPHICS_BIT", VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT)
		.value("VK_QUEUE_COMPUTE_BIT", VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT)
		.value("VK_QUEUE_TRANSFER_BIT", VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT)
		.value("VK_QUEUE_SPARSE_BINDING_BIT", VkQueueFlagBits::VK_QUEUE_SPARSE_BINDING_BIT)
		.export_values();
	py::enum_<VkMemoryPropertyFlagBits>(m, "MemoryPropertyFlagBits", py::arithmetic())
		.value("VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT", VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
		.value("VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT", VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
		.value("VK_MEMORY_PROPERTY_HOST_COHERENT_BIT", VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
		.value("VK_MEMORY_PROPERTY_HOST_CACHED_BIT", VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
		.value("VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT", VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)
		.export_values();
	py::enum_<VkMemoryHeapFlagBits>(m, "MemoryHeapFlagBits", py::arithmetic())
		.value("VK_MEMORY_HEAP_DEVICE_LOCAL_BIT", VkMemoryHeapFlagBits::VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
		.export_values();
	py::enum_<VkAccessFlagBits>(m, "AccessFlagBits", py::arithmetic())
		.value("VK_ACCESS_INDIRECT_COMMAND_READ_BIT", VkAccessFlagBits::VK_ACCESS_INDIRECT_COMMAND_READ_BIT)
		.value("VK_ACCESS_INDEX_READ_BIT", VkAccessFlagBits::VK_ACCESS_INDEX_READ_BIT)
		.value("VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT", VkAccessFlagBits::VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT)
		.value("VK_ACCESS_UNIFORM_READ_BIT", VkAccessFlagBits::VK_ACCESS_UNIFORM_READ_BIT)
		.value("VK_ACCESS_INPUT_ATTACHMENT_READ_BIT", VkAccessFlagBits::VK_ACCESS_INPUT_ATTACHMENT_READ_BIT)
		.value("VK_ACCESS_SHADER_READ_BIT", VkAccessFlagBits::VK_ACCESS_SHADER_READ_BIT)
		.value("VK_ACCESS_SHADER_WRITE_BIT", VkAccessFlagBits::VK_ACCESS_SHADER_WRITE_BIT)
		.value("VK_ACCESS_COLOR_ATTACHMENT_READ_BIT", VkAccessFlagBits::VK_ACCESS_COLOR_ATTACHMENT_READ_BIT)
		.value("VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT", VkAccessFlagBits::VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT)
		.value("VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT", VkAccessFlagBits::VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT)
		.value("VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT", VkAccessFlagBits::VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT)
		.value("VK_ACCESS_TRANSFER_READ_BIT", VkAccessFlagBits::VK_ACCESS_TRANSFER_READ_BIT)
		.value("VK_ACCESS_TRANSFER_WRITE_BIT", VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT)
		.value("VK_ACCESS_HOST_READ_BIT", VkAccessFlagBits::VK_ACCESS_HOST_READ_BIT)
		.value("VK_ACCESS_HOST_WRITE_BIT", VkAccessFlagBits::VK_ACCESS_HOST_WRITE_BIT)
		.value("VK_ACCESS_MEMORY_READ_BIT", VkAccessFlagBits::VK_ACCESS_MEMORY_READ_BIT)
		.value("VK_ACCESS_MEMORY_WRITE_BIT", VkAccessFlagBits::VK_ACCESS_MEMORY_WRITE_BIT)
		.export_values();
	py::enum_<VkBufferUsageFlagBits>(m, "BufferUsageFlagBits", py::arithmetic())
		.value("VK_BUFFER_USAGE_TRANSFER_SRC_BIT", VkBufferUsageFlagBits::VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
		.value("VK_BUFFER_USAGE_TRANSFER_DST_BIT", VkBufferUsageFlagBits::VK_BUFFER_USAGE_TRANSFER_DST_BIT)
		.value("VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT", VkBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT)
		.value("VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT", VkBufferUsageFlagBits::VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT)
		.value("VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT", VkBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
		.value("VK_BUFFER_USAGE_STORAGE_BUFFER_BIT", VkBufferUsageFlagBits::VK_BUFFER_USAGE_STORAGE_BUFFER_BIT)
		.value("VK_BUFFER_USAGE_INDEX_BUFFER_BIT", VkBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
		.value("VK_BUFFER_USAGE_VERTEX_BUFFER_BIT", VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
		.value("VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT", VkBufferUsageFlagBits::VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT)
		.export_values();
	py::enum_<VkBufferCreateFlagBits>(m, "BufferCreateFlagBits", py::arithmetic())
		.value("VK_BUFFER_CREATE_SPARSE_BINDING_BIT", VkBufferCreateFlagBits::VK_BUFFER_CREATE_SPARSE_BINDING_BIT)
		.value("VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT", VkBufferCreateFlagBits::VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT)
		.value("VK_BUFFER_CREATE_SPARSE_ALIASED_BIT", VkBufferCreateFlagBits::VK_BUFFER_CREATE_SPARSE_ALIASED_BIT)
		.export_values();
	py::enum_<VkShaderStageFlagBits>(m, "ShaderStageFlagBits", py::arithmetic())
		.value("VK_SHADER_STAGE_VERTEX_BIT", VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT)
		.value("VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT", VkShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT)
		.value("VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT", VkShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT)
		.value("VK_SHADER_STAGE_GEOMETRY_BIT", VkShaderStageFlagBits::VK_SHADER_STAGE_GEOMETRY_BIT)
		.value("VK_SHADER_STAGE_FRAGMENT_BIT", VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT)
		.value("VK_SHADER_STAGE_COMPUTE_BIT", VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT)
		.value("VK_SHADER_STAGE_ALL_GRAPHICS", VkShaderStageFlagBits::VK_SHADER_STAGE_ALL_GRAPHICS)
		.value("VK_SHADER_STAGE_ALL", VkShaderStageFlagBits::VK_SHADER_STAGE_ALL)
		.export_values();
	py::enum_<VkImageUsageFlagBits>(m, "ImageUsageFlagBits", py::arithmetic())
		.value("VK_IMAGE_USAGE_TRANSFER_SRC_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
		.value("VK_IMAGE_USAGE_TRANSFER_DST_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_DST_BIT)
		.value("VK_IMAGE_USAGE_SAMPLED_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_SAMPLED_BIT)
		.value("VK_IMAGE_USAGE_STORAGE_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_STORAGE_BIT)
		.value("VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
		.value("VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
		.value("VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT)
		.value("VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT", VkImageUsageFlagBits::VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT)
		.export_values();
	py::enum_<VkImageCreateFlagBits>(m, "ImageCreateFlagBits", py::arithmetic())
		.value("VK_IMAGE_CREATE_SPARSE_BINDING_BIT", VkImageCreateFlagBits::VK_IMAGE_CREATE_SPARSE_BINDING_BIT)
		.value("VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT", VkImageCreateFlagBits::VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT)
		.value("VK_IMAGE_CREATE_SPARSE_ALIASED_BIT", VkImageCreateFlagBits::VK_IMAGE_CREATE_SPARSE_ALIASED_BIT)
		.value("VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT", VkImageCreateFlagBits::VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT)
		.value("VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT", VkImageCreateFlagBits::VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT)
		.export_values();
	py::enum_<VkImageViewCreateFlagBits>(m, "ImageViewCreateFlagBits", py::arithmetic())
		.export_values();
	py::enum_<VkSamplerCreateFlagBits>(m, "SamplerCreateFlagBits", py::arithmetic())
		.export_values();
	py::enum_<VkPipelineCreateFlagBits>(m, "PipelineCreateFlagBits", py::arithmetic())
		.value("VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT", VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT)
		.value("VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT", VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT)
		.value("VK_PIPELINE_CREATE_DERIVATIVE_BIT", VkPipelineCreateFlagBits::VK_PIPELINE_CREATE_DERIVATIVE_BIT)
		.export_values();
	py::enum_<VkColorComponentFlagBits>(m, "ColorComponentFlagBits", py::arithmetic())
		.value("VK_COLOR_COMPONENT_R_BIT", VkColorComponentFlagBits::VK_COLOR_COMPONENT_R_BIT)
		.value("VK_COLOR_COMPONENT_G_BIT", VkColorComponentFlagBits::VK_COLOR_COMPONENT_G_BIT)
		.value("VK_COLOR_COMPONENT_B_BIT", VkColorComponentFlagBits::VK_COLOR_COMPONENT_B_BIT)
		.value("VK_COLOR_COMPONENT_A_BIT", VkColorComponentFlagBits::VK_COLOR_COMPONENT_A_BIT)
		.export_values();
	py::enum_<VkFenceCreateFlagBits>(m, "FenceCreateFlagBits", py::arithmetic())
		.value("VK_FENCE_CREATE_SIGNALED_BIT", VkFenceCreateFlagBits::VK_FENCE_CREATE_SIGNALED_BIT)
		.export_values();
	py::enum_<VkFormatFeatureFlagBits>(m, "FormatFeatureFlagBits", py::arithmetic())
		.value("VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
		.value("VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT)
		.value("VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT)
		.value("VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT)
		.value("VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT)
		.value("VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT)
		.value("VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT)
		.value("VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
		.value("VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT)
		.value("VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
		.value("VK_FORMAT_FEATURE_BLIT_SRC_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_BLIT_SRC_BIT)
		.value("VK_FORMAT_FEATURE_BLIT_DST_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_BLIT_DST_BIT)
		.value("VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT", VkFormatFeatureFlagBits::VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)
		.export_values();
	py::enum_<VkQueryControlFlagBits>(m, "QueryControlFlagBits", py::arithmetic())
		.value("VK_QUERY_CONTROL_PRECISE_BIT", VkQueryControlFlagBits::VK_QUERY_CONTROL_PRECISE_BIT)
		.export_values();
	py::enum_<VkQueryResultFlagBits>(m, "QueryResultFlagBits", py::arithmetic())
		.value("VK_QUERY_RESULT_64_BIT", VkQueryResultFlagBits::VK_QUERY_RESULT_64_BIT)
		.value("VK_QUERY_RESULT_WAIT_BIT", VkQueryResultFlagBits::VK_QUERY_RESULT_WAIT_BIT)
		.value("VK_QUERY_RESULT_WITH_AVAILABILITY_BIT", VkQueryResultFlagBits::VK_QUERY_RESULT_WITH_AVAILABILITY_BIT)
		.value("VK_QUERY_RESULT_PARTIAL_BIT", VkQueryResultFlagBits::VK_QUERY_RESULT_PARTIAL_BIT)
		.export_values();
	py::enum_<VkCommandBufferUsageFlagBits>(m, "CommandBufferUsageFlagBits", py::arithmetic())
		.value("VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT", VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT)
		.value("VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT", VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT)
		.value("VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT", VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT)
		.export_values();
	py::enum_<VkQueryPipelineStatisticFlagBits>(m, "QueryPipelineStatisticFlagBits", py::arithmetic())
		.value("VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT", VkQueryPipelineStatisticFlagBits::VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT)
		.value("VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT", VkQueryPipelineStatisticFlagBits::VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT)
		.value("VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT", VkQueryPipelineStatisticFlagBits::VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT)
		.value("VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_INVOCATIONS_BIT", VkQueryPipelineStatisticFlagBits::VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_INVOCATIONS_BIT)
		.value("VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_PRIMITIVES_BIT", VkQueryPipelineStatisticFlagBits::VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_PRIMITIVES_BIT)
		.value("VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT", VkQueryPipelineStatisticFlagBits::VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT)
		.value("VK_QUERY_PIPELINE_STATISTIC_CLIPPING_PRIMITIVES_BIT", VkQueryPipelineStatisticFlagBits::VK_QUERY_PIPELINE_STATISTIC_CLIPPING_PRIMITIVES_BIT)
		.value("VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT", VkQueryPipelineStatisticFlagBits::VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT)
		.value("VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_CONTROL_SHADER_PATCHES_BIT", VkQueryPipelineStatisticFlagBits::VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_CONTROL_SHADER_PATCHES_BIT)
		.value("VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_EVALUATION_SHADER_INVOCATIONS_BIT", VkQueryPipelineStatisticFlagBits::VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_EVALUATION_SHADER_INVOCATIONS_BIT)
		.value("VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT", VkQueryPipelineStatisticFlagBits::VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT)
		.export_values();
	py::enum_<VkImageAspectFlagBits>(m, "ImageAspectFlagBits", py::arithmetic())
		.value("VK_IMAGE_ASPECT_COLOR_BIT", VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT)
		.value("VK_IMAGE_ASPECT_DEPTH_BIT", VkImageAspectFlagBits::VK_IMAGE_ASPECT_DEPTH_BIT)
		.value("VK_IMAGE_ASPECT_STENCIL_BIT", VkImageAspectFlagBits::VK_IMAGE_ASPECT_STENCIL_BIT)
		.value("VK_IMAGE_ASPECT_METADATA_BIT", VkImageAspectFlagBits::VK_IMAGE_ASPECT_METADATA_BIT)
		.export_values();
	py::enum_<VkSparseImageFormatFlagBits>(m, "SparseImageFormatFlagBits", py::arithmetic())
		.value("VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT", VkSparseImageFormatFlagBits::VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT)
		.value("VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT", VkSparseImageFormatFlagBits::VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT)
		.value("VK_SPARSE_IMAGE_FORMAT_NONSTANDARD_BLOCK_SIZE_BIT", VkSparseImageFormatFlagBits::VK_SPARSE_IMAGE_FORMAT_NONSTANDARD_BLOCK_SIZE_BIT)
		.export_values();
	py::enum_<VkSparseMemoryBindFlagBits>(m, "SparseMemoryBindFlagBits", py::arithmetic())
		.value("VK_SPARSE_MEMORY_BIND_METADATA_BIT", VkSparseMemoryBindFlagBits::VK_SPARSE_MEMORY_BIND_METADATA_BIT)
		.export_values();
	py::enum_<VkPipelineStageFlagBits>(m, "PipelineStageFlagBits", py::arithmetic())
		.value("VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT)
		.value("VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT)
		.value("VK_PIPELINE_STAGE_VERTEX_INPUT_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_VERTEX_INPUT_BIT)
		.value("VK_PIPELINE_STAGE_VERTEX_SHADER_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_VERTEX_SHADER_BIT)
		.value("VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT)
		.value("VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT)
		.value("VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT)
		.value("VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT)
		.value("VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT)
		.value("VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT)
		.value("VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT)
		.value("VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT)
		.value("VK_PIPELINE_STAGE_TRANSFER_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT)
		.value("VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT)
		.value("VK_PIPELINE_STAGE_HOST_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_HOST_BIT)
		.value("VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT)
		.value("VK_PIPELINE_STAGE_ALL_COMMANDS_BIT", VkPipelineStageFlagBits::VK_PIPELINE_STAGE_ALL_COMMANDS_BIT)
		.export_values();
	py::enum_<VkCommandPoolCreateFlagBits>(m, "CommandPoolCreateFlagBits", py::arithmetic())
		.value("VK_COMMAND_POOL_CREATE_TRANSIENT_BIT", VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_TRANSIENT_BIT)
		.value("VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT", VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
		.export_values();
	py::enum_<VkCommandPoolResetFlagBits>(m, "CommandPoolResetFlagBits", py::arithmetic())
		.value("VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT", VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT)
		.export_values();
	py::enum_<VkCommandBufferResetFlagBits>(m, "CommandBufferResetFlagBits", py::arithmetic())
		.value("VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT", VkCommandBufferResetFlagBits::VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT)
		.export_values();
	py::enum_<VkSampleCountFlagBits>(m, "SampleCountFlagBits", py::arithmetic())
		.value("VK_SAMPLE_COUNT_1_BIT", VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT)
		.value("VK_SAMPLE_COUNT_2_BIT", VkSampleCountFlagBits::VK_SAMPLE_COUNT_2_BIT)
		.value("VK_SAMPLE_COUNT_4_BIT", VkSampleCountFlagBits::VK_SAMPLE_COUNT_4_BIT)
		.value("VK_SAMPLE_COUNT_8_BIT", VkSampleCountFlagBits::VK_SAMPLE_COUNT_8_BIT)
		.value("VK_SAMPLE_COUNT_16_BIT", VkSampleCountFlagBits::VK_SAMPLE_COUNT_16_BIT)
		.value("VK_SAMPLE_COUNT_32_BIT", VkSampleCountFlagBits::VK_SAMPLE_COUNT_32_BIT)
		.value("VK_SAMPLE_COUNT_64_BIT", VkSampleCountFlagBits::VK_SAMPLE_COUNT_64_BIT)
		.export_values();
	py::enum_<VkAttachmentDescriptionFlagBits>(m, "AttachmentDescriptionFlagBits", py::arithmetic())
		.value("VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT", VkAttachmentDescriptionFlagBits::VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT)
		.export_values();
	py::enum_<VkStencilFaceFlagBits>(m, "StencilFaceFlagBits", py::arithmetic())
		.value("VK_STENCIL_FACE_FRONT_BIT", VkStencilFaceFlagBits::VK_STENCIL_FACE_FRONT_BIT)
		.value("VK_STENCIL_FACE_BACK_BIT", VkStencilFaceFlagBits::VK_STENCIL_FACE_BACK_BIT)
		.value("VK_STENCIL_FRONT_AND_BACK", VkStencilFaceFlagBits::VK_STENCIL_FRONT_AND_BACK)
		.export_values();
	py::enum_<VkDescriptorPoolCreateFlagBits>(m, "DescriptorPoolCreateFlagBits", py::arithmetic())
		.value("VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT", VkDescriptorPoolCreateFlagBits::VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)
		.export_values();
	py::enum_<VkDependencyFlagBits>(m, "DependencyFlagBits", py::arithmetic())
		.value("VK_DEPENDENCY_BY_REGION_BIT", VkDependencyFlagBits::VK_DEPENDENCY_BY_REGION_BIT)
		.export_values();
	py::enum_<VkPresentModeKHR>(m, "PresentModeKHR", py::arithmetic())
		.value("VK_PRESENT_MODE_IMMEDIATE_KHR", VkPresentModeKHR::VK_PRESENT_MODE_IMMEDIATE_KHR)
		.value("VK_PRESENT_MODE_MAILBOX_KHR", VkPresentModeKHR::VK_PRESENT_MODE_MAILBOX_KHR)
		.value("VK_PRESENT_MODE_FIFO_KHR", VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR)
		.value("VK_PRESENT_MODE_FIFO_RELAXED_KHR", VkPresentModeKHR::VK_PRESENT_MODE_FIFO_RELAXED_KHR)
		.export_values();
	py::enum_<VkColorSpaceKHR>(m, "ColorSpaceKHR", py::arithmetic())
		.value("VK_COLOR_SPACE_SRGB_NONLINEAR_KHR", VkColorSpaceKHR::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		.value("VK_COLORSPACE_SRGB_NONLINEAR_KHR", VkColorSpaceKHR::VK_COLORSPACE_SRGB_NONLINEAR_KHR)
		.export_values();
	py::enum_<VkDisplayPlaneAlphaFlagBitsKHR>(m, "DisplayPlaneAlphaFlagBitsKHR", py::arithmetic())
		.value("VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR", VkDisplayPlaneAlphaFlagBitsKHR::VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR)
		.value("VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR", VkDisplayPlaneAlphaFlagBitsKHR::VK_DISPLAY_PLANE_ALPHA_GLOBAL_BIT_KHR)
		.value("VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR", VkDisplayPlaneAlphaFlagBitsKHR::VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_BIT_KHR)
		.value("VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR", VkDisplayPlaneAlphaFlagBitsKHR::VK_DISPLAY_PLANE_ALPHA_PER_PIXEL_PREMULTIPLIED_BIT_KHR)
		.export_values();
	py::enum_<VkCompositeAlphaFlagBitsKHR>(m, "CompositeAlphaFlagBitsKHR", py::arithmetic())
		.value("VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR", VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)
		.value("VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR", VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR)
		.value("VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR", VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR)
		.value("VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR", VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR)
		.export_values();
	py::enum_<VkSurfaceTransformFlagBitsKHR>(m, "SurfaceTransformFlagBitsKHR", py::arithmetic())
		.value("VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
		.value("VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR)
		.value("VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR)
		.value("VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
		.value("VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR)
		.value("VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR)
		.value("VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR)
		.value("VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR)
		.value("VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR", VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR)
		.export_values();
	py::enum_<VkTimeDomainEXT>(m, "TimeDomainEXT", py::arithmetic())
		.value("VK_TIME_DOMAIN_DEVICE_EXT", VkTimeDomainEXT::VK_TIME_DOMAIN_DEVICE_EXT)
		.value("VK_TIME_DOMAIN_CLOCK_MONOTONIC_EXT", VkTimeDomainEXT::VK_TIME_DOMAIN_CLOCK_MONOTONIC_EXT)
		.value("VK_TIME_DOMAIN_CLOCK_MONOTONIC_RAW_EXT", VkTimeDomainEXT::VK_TIME_DOMAIN_CLOCK_MONOTONIC_RAW_EXT)
		.value("VK_TIME_DOMAIN_QUERY_PERFORMANCE_COUNTER_EXT", VkTimeDomainEXT::VK_TIME_DOMAIN_QUERY_PERFORMANCE_COUNTER_EXT)
		.export_values();
	py::enum_<VkDebugReportFlagBitsEXT>(m, "DebugReportFlagBitsEXT", py::arithmetic())
		.value("VK_DEBUG_REPORT_INFORMATION_BIT_EXT", VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_INFORMATION_BIT_EXT)
		.value("VK_DEBUG_REPORT_WARNING_BIT_EXT", VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_WARNING_BIT_EXT)
		.value("VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT", VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT)
		.value("VK_DEBUG_REPORT_ERROR_BIT_EXT", VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_ERROR_BIT_EXT)
		.value("VK_DEBUG_REPORT_DEBUG_BIT_EXT", VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT)
		.export_values();
	py::enum_<VkDebugReportObjectTypeEXT>(m, "DebugReportObjectTypeEXT", py::arithmetic())
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_PHYSICAL_DEVICE_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_QUEUE_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_SEMAPHORE_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_BUFFER_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_FENCE_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_EVENT_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_QUERY_POOL_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_BUFFER_VIEW_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_IMAGE_VIEW_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_SHADER_MODULE_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_CACHE_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_RENDER_PASS_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_SAMPLER_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_POOL_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_DESCRIPTOR_SET_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_FRAMEBUFFER_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_COMMAND_POOL_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_SURFACE_KHR_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_SWAPCHAIN_KHR_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_DEBUG_REPORT_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_DEBUG_REPORT_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_KHR_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_MODE_KHR_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_DISPLAY_MODE_KHR_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_OBJECT_TABLE_NVX_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_INDIRECT_COMMANDS_LAYOUT_NVX_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT_EXT)
		.value("VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT", VkDebugReportObjectTypeEXT::VK_DEBUG_REPORT_OBJECT_TYPE_VALIDATION_CACHE_EXT)
		.export_values();
	py::enum_<VkRasterizationOrderAMD>(m, "RasterizationOrderAMD", py::arithmetic())
		.value("VK_RASTERIZATION_ORDER_STRICT_AMD", VkRasterizationOrderAMD::VK_RASTERIZATION_ORDER_STRICT_AMD)
		.value("VK_RASTERIZATION_ORDER_RELAXED_AMD", VkRasterizationOrderAMD::VK_RASTERIZATION_ORDER_RELAXED_AMD)
		.export_values();
	py::enum_<VkExternalMemoryHandleTypeFlagBitsNV>(m, "ExternalMemoryHandleTypeFlagBitsNV", py::arithmetic())
		.value("VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT_NV", VkExternalMemoryHandleTypeFlagBitsNV::VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT_NV)
		.value("VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT_NV", VkExternalMemoryHandleTypeFlagBitsNV::VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT_NV)
		.value("VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_BIT_NV", VkExternalMemoryHandleTypeFlagBitsNV::VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_BIT_NV)
		.value("VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_KMT_BIT_NV", VkExternalMemoryHandleTypeFlagBitsNV::VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_IMAGE_KMT_BIT_NV)
		.export_values();
	py::enum_<VkExternalMemoryFeatureFlagBitsNV>(m, "ExternalMemoryFeatureFlagBitsNV", py::arithmetic())
		.value("VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT_NV", VkExternalMemoryFeatureFlagBitsNV::VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT_NV)
		.value("VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT_NV", VkExternalMemoryFeatureFlagBitsNV::VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT_NV)
		.value("VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT_NV", VkExternalMemoryFeatureFlagBitsNV::VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT_NV)
		.export_values();
	py::enum_<VkValidationCheckEXT>(m, "ValidationCheckEXT", py::arithmetic())
		.value("VK_VALIDATION_CHECK_ALL_EXT", VkValidationCheckEXT::VK_VALIDATION_CHECK_ALL_EXT)
		.value("VK_VALIDATION_CHECK_SHADERS_EXT", VkValidationCheckEXT::VK_VALIDATION_CHECK_SHADERS_EXT)
		.export_values();
	py::enum_<VkValidationFeatureEnableEXT>(m, "ValidationFeatureEnableEXT", py::arithmetic())
		.value("VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT", VkValidationFeatureEnableEXT::VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT)
		.value("VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT", VkValidationFeatureEnableEXT::VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT)
		.export_values();
	py::enum_<VkValidationFeatureDisableEXT>(m, "ValidationFeatureDisableEXT", py::arithmetic())
		.value("VK_VALIDATION_FEATURE_DISABLE_ALL_EXT", VkValidationFeatureDisableEXT::VK_VALIDATION_FEATURE_DISABLE_ALL_EXT)
		.value("VK_VALIDATION_FEATURE_DISABLE_SHADERS_EXT", VkValidationFeatureDisableEXT::VK_VALIDATION_FEATURE_DISABLE_SHADERS_EXT)
		.value("VK_VALIDATION_FEATURE_DISABLE_THREAD_SAFETY_EXT", VkValidationFeatureDisableEXT::VK_VALIDATION_FEATURE_DISABLE_THREAD_SAFETY_EXT)
		.value("VK_VALIDATION_FEATURE_DISABLE_API_PARAMETERS_EXT", VkValidationFeatureDisableEXT::VK_VALIDATION_FEATURE_DISABLE_API_PARAMETERS_EXT)
		.value("VK_VALIDATION_FEATURE_DISABLE_OBJECT_LIFETIMES_EXT", VkValidationFeatureDisableEXT::VK_VALIDATION_FEATURE_DISABLE_OBJECT_LIFETIMES_EXT)
		.value("VK_VALIDATION_FEATURE_DISABLE_CORE_CHECKS_EXT", VkValidationFeatureDisableEXT::VK_VALIDATION_FEATURE_DISABLE_CORE_CHECKS_EXT)
		.value("VK_VALIDATION_FEATURE_DISABLE_UNIQUE_HANDLES_EXT", VkValidationFeatureDisableEXT::VK_VALIDATION_FEATURE_DISABLE_UNIQUE_HANDLES_EXT)
		.export_values();
	py::enum_<VkSubgroupFeatureFlagBits>(m, "SubgroupFeatureFlagBits", py::arithmetic())
		.value("VK_SUBGROUP_FEATURE_BASIC_BIT", VkSubgroupFeatureFlagBits::VK_SUBGROUP_FEATURE_BASIC_BIT)
		.value("VK_SUBGROUP_FEATURE_VOTE_BIT", VkSubgroupFeatureFlagBits::VK_SUBGROUP_FEATURE_VOTE_BIT)
		.value("VK_SUBGROUP_FEATURE_ARITHMETIC_BIT", VkSubgroupFeatureFlagBits::VK_SUBGROUP_FEATURE_ARITHMETIC_BIT)
		.value("VK_SUBGROUP_FEATURE_BALLOT_BIT", VkSubgroupFeatureFlagBits::VK_SUBGROUP_FEATURE_BALLOT_BIT)
		.value("VK_SUBGROUP_FEATURE_SHUFFLE_BIT", VkSubgroupFeatureFlagBits::VK_SUBGROUP_FEATURE_SHUFFLE_BIT)
		.value("VK_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_BIT", VkSubgroupFeatureFlagBits::VK_SUBGROUP_FEATURE_SHUFFLE_RELATIVE_BIT)
		.value("VK_SUBGROUP_FEATURE_CLUSTERED_BIT", VkSubgroupFeatureFlagBits::VK_SUBGROUP_FEATURE_CLUSTERED_BIT)
		.value("VK_SUBGROUP_FEATURE_QUAD_BIT", VkSubgroupFeatureFlagBits::VK_SUBGROUP_FEATURE_QUAD_BIT)
		.export_values();
	py::enum_<VkIndirectCommandsLayoutUsageFlagBitsNVX>(m, "IndirectCommandsLayoutUsageFlagBitsNVX", py::arithmetic())
		.value("VK_INDIRECT_COMMANDS_LAYOUT_USAGE_UNORDERED_SEQUENCES_BIT_NVX", VkIndirectCommandsLayoutUsageFlagBitsNVX::VK_INDIRECT_COMMANDS_LAYOUT_USAGE_UNORDERED_SEQUENCES_BIT_NVX)
		.value("VK_INDIRECT_COMMANDS_LAYOUT_USAGE_SPARSE_SEQUENCES_BIT_NVX", VkIndirectCommandsLayoutUsageFlagBitsNVX::VK_INDIRECT_COMMANDS_LAYOUT_USAGE_SPARSE_SEQUENCES_BIT_NVX)
		.value("VK_INDIRECT_COMMANDS_LAYOUT_USAGE_EMPTY_EXECUTIONS_BIT_NVX", VkIndirectCommandsLayoutUsageFlagBitsNVX::VK_INDIRECT_COMMANDS_LAYOUT_USAGE_EMPTY_EXECUTIONS_BIT_NVX)
		.value("VK_INDIRECT_COMMANDS_LAYOUT_USAGE_INDEXED_SEQUENCES_BIT_NVX", VkIndirectCommandsLayoutUsageFlagBitsNVX::VK_INDIRECT_COMMANDS_LAYOUT_USAGE_INDEXED_SEQUENCES_BIT_NVX)
		.export_values();
	py::enum_<VkObjectEntryUsageFlagBitsNVX>(m, "ObjectEntryUsageFlagBitsNVX", py::arithmetic())
		.value("VK_OBJECT_ENTRY_USAGE_GRAPHICS_BIT_NVX", VkObjectEntryUsageFlagBitsNVX::VK_OBJECT_ENTRY_USAGE_GRAPHICS_BIT_NVX)
		.value("VK_OBJECT_ENTRY_USAGE_COMPUTE_BIT_NVX", VkObjectEntryUsageFlagBitsNVX::VK_OBJECT_ENTRY_USAGE_COMPUTE_BIT_NVX)
		.export_values();
	py::enum_<VkIndirectCommandsTokenTypeNVX>(m, "IndirectCommandsTokenTypeNVX", py::arithmetic())
		.value("VK_INDIRECT_COMMANDS_TOKEN_TYPE_PIPELINE_NVX", VkIndirectCommandsTokenTypeNVX::VK_INDIRECT_COMMANDS_TOKEN_TYPE_PIPELINE_NVX)
		.value("VK_INDIRECT_COMMANDS_TOKEN_TYPE_DESCRIPTOR_SET_NVX", VkIndirectCommandsTokenTypeNVX::VK_INDIRECT_COMMANDS_TOKEN_TYPE_DESCRIPTOR_SET_NVX)
		.value("VK_INDIRECT_COMMANDS_TOKEN_TYPE_INDEX_BUFFER_NVX", VkIndirectCommandsTokenTypeNVX::VK_INDIRECT_COMMANDS_TOKEN_TYPE_INDEX_BUFFER_NVX)
		.value("VK_INDIRECT_COMMANDS_TOKEN_TYPE_VERTEX_BUFFER_NVX", VkIndirectCommandsTokenTypeNVX::VK_INDIRECT_COMMANDS_TOKEN_TYPE_VERTEX_BUFFER_NVX)
		.value("VK_INDIRECT_COMMANDS_TOKEN_TYPE_PUSH_CONSTANT_NVX", VkIndirectCommandsTokenTypeNVX::VK_INDIRECT_COMMANDS_TOKEN_TYPE_PUSH_CONSTANT_NVX)
		.value("VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_INDEXED_NVX", VkIndirectCommandsTokenTypeNVX::VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_INDEXED_NVX)
		.value("VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_NVX", VkIndirectCommandsTokenTypeNVX::VK_INDIRECT_COMMANDS_TOKEN_TYPE_DRAW_NVX)
		.value("VK_INDIRECT_COMMANDS_TOKEN_TYPE_DISPATCH_NVX", VkIndirectCommandsTokenTypeNVX::VK_INDIRECT_COMMANDS_TOKEN_TYPE_DISPATCH_NVX)
		.export_values();
	py::enum_<VkObjectEntryTypeNVX>(m, "ObjectEntryTypeNVX", py::arithmetic())
		.value("VK_OBJECT_ENTRY_TYPE_DESCRIPTOR_SET_NVX", VkObjectEntryTypeNVX::VK_OBJECT_ENTRY_TYPE_DESCRIPTOR_SET_NVX)
		.value("VK_OBJECT_ENTRY_TYPE_PIPELINE_NVX", VkObjectEntryTypeNVX::VK_OBJECT_ENTRY_TYPE_PIPELINE_NVX)
		.value("VK_OBJECT_ENTRY_TYPE_INDEX_BUFFER_NVX", VkObjectEntryTypeNVX::VK_OBJECT_ENTRY_TYPE_INDEX_BUFFER_NVX)
		.value("VK_OBJECT_ENTRY_TYPE_VERTEX_BUFFER_NVX", VkObjectEntryTypeNVX::VK_OBJECT_ENTRY_TYPE_VERTEX_BUFFER_NVX)
		.value("VK_OBJECT_ENTRY_TYPE_PUSH_CONSTANT_NVX", VkObjectEntryTypeNVX::VK_OBJECT_ENTRY_TYPE_PUSH_CONSTANT_NVX)
		.export_values();
	py::enum_<VkDescriptorSetLayoutCreateFlagBits>(m, "DescriptorSetLayoutCreateFlagBits", py::arithmetic())
		.export_values();
	py::enum_<VkExternalMemoryHandleTypeFlagBits>(m, "ExternalMemoryHandleTypeFlagBits", py::arithmetic())
		.value("VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT", VkExternalMemoryHandleTypeFlagBits::VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT)
		.value("VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT", VkExternalMemoryHandleTypeFlagBits::VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_BIT)
		.value("VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT", VkExternalMemoryHandleTypeFlagBits::VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT)
		.value("VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT", VkExternalMemoryHandleTypeFlagBits::VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_BIT)
		.value("VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT", VkExternalMemoryHandleTypeFlagBits::VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D11_TEXTURE_KMT_BIT)
		.value("VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT", VkExternalMemoryHandleTypeFlagBits::VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP_BIT)
		.value("VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT", VkExternalMemoryHandleTypeFlagBits::VK_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE_BIT)
		.export_values();
	py::enum_<VkExternalMemoryFeatureFlagBits>(m, "ExternalMemoryFeatureFlagBits", py::arithmetic())
		.value("VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT", VkExternalMemoryFeatureFlagBits::VK_EXTERNAL_MEMORY_FEATURE_DEDICATED_ONLY_BIT)
		.value("VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT", VkExternalMemoryFeatureFlagBits::VK_EXTERNAL_MEMORY_FEATURE_EXPORTABLE_BIT)
		.value("VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT", VkExternalMemoryFeatureFlagBits::VK_EXTERNAL_MEMORY_FEATURE_IMPORTABLE_BIT)
		.export_values();
	py::enum_<VkExternalSemaphoreHandleTypeFlagBits>(m, "ExternalSemaphoreHandleTypeFlagBits", py::arithmetic())
		.value("VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT", VkExternalSemaphoreHandleTypeFlagBits::VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT)
		.value("VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT", VkExternalSemaphoreHandleTypeFlagBits::VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT)
		.value("VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT", VkExternalSemaphoreHandleTypeFlagBits::VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT)
		.value("VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE_BIT", VkExternalSemaphoreHandleTypeFlagBits::VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE_BIT)
		.value("VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT", VkExternalSemaphoreHandleTypeFlagBits::VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT)
		.export_values();
	py::enum_<VkExternalSemaphoreFeatureFlagBits>(m, "ExternalSemaphoreFeatureFlagBits", py::arithmetic())
		.value("VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT", VkExternalSemaphoreFeatureFlagBits::VK_EXTERNAL_SEMAPHORE_FEATURE_EXPORTABLE_BIT)
		.value("VK_EXTERNAL_SEMAPHORE_FEATURE_IMPORTABLE_BIT", VkExternalSemaphoreFeatureFlagBits::VK_EXTERNAL_SEMAPHORE_FEATURE_IMPORTABLE_BIT)
		.export_values();
	py::enum_<VkSemaphoreImportFlagBits>(m, "SemaphoreImportFlagBits", py::arithmetic())
		.value("VK_SEMAPHORE_IMPORT_TEMPORARY_BIT", VkSemaphoreImportFlagBits::VK_SEMAPHORE_IMPORT_TEMPORARY_BIT)
		.export_values();
	py::enum_<VkExternalFenceHandleTypeFlagBits>(m, "ExternalFenceHandleTypeFlagBits", py::arithmetic())
		.value("VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_FD_BIT", VkExternalFenceHandleTypeFlagBits::VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_FD_BIT)
		.value("VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT", VkExternalFenceHandleTypeFlagBits::VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_BIT)
		.value("VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT", VkExternalFenceHandleTypeFlagBits::VK_EXTERNAL_FENCE_HANDLE_TYPE_OPAQUE_WIN32_KMT_BIT)
		.value("VK_EXTERNAL_FENCE_HANDLE_TYPE_SYNC_FD_BIT", VkExternalFenceHandleTypeFlagBits::VK_EXTERNAL_FENCE_HANDLE_TYPE_SYNC_FD_BIT)
		.export_values();
	py::enum_<VkExternalFenceFeatureFlagBits>(m, "ExternalFenceFeatureFlagBits", py::arithmetic())
		.value("VK_EXTERNAL_FENCE_FEATURE_EXPORTABLE_BIT", VkExternalFenceFeatureFlagBits::VK_EXTERNAL_FENCE_FEATURE_EXPORTABLE_BIT)
		.value("VK_EXTERNAL_FENCE_FEATURE_IMPORTABLE_BIT", VkExternalFenceFeatureFlagBits::VK_EXTERNAL_FENCE_FEATURE_IMPORTABLE_BIT)
		.export_values();
	py::enum_<VkFenceImportFlagBits>(m, "FenceImportFlagBits", py::arithmetic())
		.value("VK_FENCE_IMPORT_TEMPORARY_BIT", VkFenceImportFlagBits::VK_FENCE_IMPORT_TEMPORARY_BIT)
		.export_values();
	py::enum_<VkSurfaceCounterFlagBitsEXT>(m, "SurfaceCounterFlagBitsEXT", py::arithmetic())
		.value("VK_SURFACE_COUNTER_VBLANK_EXT", VkSurfaceCounterFlagBitsEXT::VK_SURFACE_COUNTER_VBLANK_EXT)
		.export_values();
	py::enum_<VkDisplayPowerStateEXT>(m, "DisplayPowerStateEXT", py::arithmetic())
		.value("VK_DISPLAY_POWER_STATE_OFF_EXT", VkDisplayPowerStateEXT::VK_DISPLAY_POWER_STATE_OFF_EXT)
		.value("VK_DISPLAY_POWER_STATE_SUSPEND_EXT", VkDisplayPowerStateEXT::VK_DISPLAY_POWER_STATE_SUSPEND_EXT)
		.value("VK_DISPLAY_POWER_STATE_ON_EXT", VkDisplayPowerStateEXT::VK_DISPLAY_POWER_STATE_ON_EXT)
		.export_values();
	py::enum_<VkDeviceEventTypeEXT>(m, "DeviceEventTypeEXT", py::arithmetic())
		.value("VK_DEVICE_EVENT_TYPE_DISPLAY_HOTPLUG_EXT", VkDeviceEventTypeEXT::VK_DEVICE_EVENT_TYPE_DISPLAY_HOTPLUG_EXT)
		.export_values();
	py::enum_<VkDisplayEventTypeEXT>(m, "DisplayEventTypeEXT", py::arithmetic())
		.value("VK_DISPLAY_EVENT_TYPE_FIRST_PIXEL_OUT_EXT", VkDisplayEventTypeEXT::VK_DISPLAY_EVENT_TYPE_FIRST_PIXEL_OUT_EXT)
		.export_values();
	py::enum_<VkPeerMemoryFeatureFlagBits>(m, "PeerMemoryFeatureFlagBits", py::arithmetic())
		.value("VK_PEER_MEMORY_FEATURE_COPY_SRC_BIT", VkPeerMemoryFeatureFlagBits::VK_PEER_MEMORY_FEATURE_COPY_SRC_BIT)
		.value("VK_PEER_MEMORY_FEATURE_COPY_DST_BIT", VkPeerMemoryFeatureFlagBits::VK_PEER_MEMORY_FEATURE_COPY_DST_BIT)
		.value("VK_PEER_MEMORY_FEATURE_GENERIC_SRC_BIT", VkPeerMemoryFeatureFlagBits::VK_PEER_MEMORY_FEATURE_GENERIC_SRC_BIT)
		.value("VK_PEER_MEMORY_FEATURE_GENERIC_DST_BIT", VkPeerMemoryFeatureFlagBits::VK_PEER_MEMORY_FEATURE_GENERIC_DST_BIT)
		.export_values();
	py::enum_<VkMemoryAllocateFlagBits>(m, "MemoryAllocateFlagBits", py::arithmetic())
		.value("VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT", VkMemoryAllocateFlagBits::VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT)
		.export_values();
	py::enum_<VkDeviceGroupPresentModeFlagBitsKHR>(m, "DeviceGroupPresentModeFlagBitsKHR", py::arithmetic())
		.value("VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR", VkDeviceGroupPresentModeFlagBitsKHR::VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_BIT_KHR)
		.value("VK_DEVICE_GROUP_PRESENT_MODE_REMOTE_BIT_KHR", VkDeviceGroupPresentModeFlagBitsKHR::VK_DEVICE_GROUP_PRESENT_MODE_REMOTE_BIT_KHR)
		.value("VK_DEVICE_GROUP_PRESENT_MODE_SUM_BIT_KHR", VkDeviceGroupPresentModeFlagBitsKHR::VK_DEVICE_GROUP_PRESENT_MODE_SUM_BIT_KHR)
		.value("VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_MULTI_DEVICE_BIT_KHR", VkDeviceGroupPresentModeFlagBitsKHR::VK_DEVICE_GROUP_PRESENT_MODE_LOCAL_MULTI_DEVICE_BIT_KHR)
		.export_values();
	py::enum_<VkSwapchainCreateFlagBitsKHR>(m, "SwapchainCreateFlagBitsKHR", py::arithmetic())
		.export_values();
	py::enum_<VkViewportCoordinateSwizzleNV>(m, "ViewportCoordinateSwizzleNV", py::arithmetic())
		.value("VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_X_NV", VkViewportCoordinateSwizzleNV::VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_X_NV)
		.value("VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_X_NV", VkViewportCoordinateSwizzleNV::VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_X_NV)
		.value("VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Y_NV", VkViewportCoordinateSwizzleNV::VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Y_NV)
		.value("VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_Y_NV", VkViewportCoordinateSwizzleNV::VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_Y_NV)
		.value("VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Z_NV", VkViewportCoordinateSwizzleNV::VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_Z_NV)
		.value("VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_Z_NV", VkViewportCoordinateSwizzleNV::VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_Z_NV)
		.value("VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_W_NV", VkViewportCoordinateSwizzleNV::VK_VIEWPORT_COORDINATE_SWIZZLE_POSITIVE_W_NV)
		.value("VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_W_NV", VkViewportCoordinateSwizzleNV::VK_VIEWPORT_COORDINATE_SWIZZLE_NEGATIVE_W_NV)
		.export_values();
	py::enum_<VkDiscardRectangleModeEXT>(m, "DiscardRectangleModeEXT", py::arithmetic())
		.value("VK_DISCARD_RECTANGLE_MODE_INCLUSIVE_EXT", VkDiscardRectangleModeEXT::VK_DISCARD_RECTANGLE_MODE_INCLUSIVE_EXT)
		.value("VK_DISCARD_RECTANGLE_MODE_EXCLUSIVE_EXT", VkDiscardRectangleModeEXT::VK_DISCARD_RECTANGLE_MODE_EXCLUSIVE_EXT)
		.export_values();
	py::enum_<VkSubpassDescriptionFlagBits>(m, "SubpassDescriptionFlagBits", py::arithmetic())
		.export_values();
	py::enum_<VkPointClippingBehavior>(m, "PointClippingBehavior", py::arithmetic())
		.value("VK_POINT_CLIPPING_BEHAVIOR_ALL_CLIP_PLANES", VkPointClippingBehavior::VK_POINT_CLIPPING_BEHAVIOR_ALL_CLIP_PLANES)
		.value("VK_POINT_CLIPPING_BEHAVIOR_USER_CLIP_PLANES_ONLY", VkPointClippingBehavior::VK_POINT_CLIPPING_BEHAVIOR_USER_CLIP_PLANES_ONLY)
		.export_values();
	py::enum_<VkSamplerReductionModeEXT>(m, "SamplerReductionModeEXT", py::arithmetic())
		.value("VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_EXT", VkSamplerReductionModeEXT::VK_SAMPLER_REDUCTION_MODE_WEIGHTED_AVERAGE_EXT)
		.value("VK_SAMPLER_REDUCTION_MODE_MIN_EXT", VkSamplerReductionModeEXT::VK_SAMPLER_REDUCTION_MODE_MIN_EXT)
		.value("VK_SAMPLER_REDUCTION_MODE_MAX_EXT", VkSamplerReductionModeEXT::VK_SAMPLER_REDUCTION_MODE_MAX_EXT)
		.export_values();
	py::enum_<VkTessellationDomainOrigin>(m, "TessellationDomainOrigin", py::arithmetic())
		.value("VK_TESSELLATION_DOMAIN_ORIGIN_UPPER_LEFT", VkTessellationDomainOrigin::VK_TESSELLATION_DOMAIN_ORIGIN_UPPER_LEFT)
		.value("VK_TESSELLATION_DOMAIN_ORIGIN_LOWER_LEFT", VkTessellationDomainOrigin::VK_TESSELLATION_DOMAIN_ORIGIN_LOWER_LEFT)
		.export_values();
	py::enum_<VkSamplerYcbcrModelConversion>(m, "SamplerYcbcrModelConversion", py::arithmetic())
		.value("VK_SAMPLER_YCBCR_MODEL_CONVERSION_RGB_IDENTITY", VkSamplerYcbcrModelConversion::VK_SAMPLER_YCBCR_MODEL_CONVERSION_RGB_IDENTITY)
		.value("VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_IDENTITY", VkSamplerYcbcrModelConversion::VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_IDENTITY)
		.value("VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_709", VkSamplerYcbcrModelConversion::VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_709)
		.value("VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_601", VkSamplerYcbcrModelConversion::VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_601)
		.value("VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_2020", VkSamplerYcbcrModelConversion::VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_2020)
		.export_values();
	py::enum_<VkSamplerYcbcrRange>(m, "SamplerYcbcrRange", py::arithmetic())
		.value("VK_SAMPLER_YCBCR_RANGE_ITU_FULL", VkSamplerYcbcrRange::VK_SAMPLER_YCBCR_RANGE_ITU_FULL)
		.value("VK_SAMPLER_YCBCR_RANGE_ITU_NARROW", VkSamplerYcbcrRange::VK_SAMPLER_YCBCR_RANGE_ITU_NARROW)
		.export_values();
	py::enum_<VkChromaLocation>(m, "ChromaLocation", py::arithmetic())
		.value("VK_CHROMA_LOCATION_COSITED_EVEN", VkChromaLocation::VK_CHROMA_LOCATION_COSITED_EVEN)
		.value("VK_CHROMA_LOCATION_MIDPOINT", VkChromaLocation::VK_CHROMA_LOCATION_MIDPOINT)
		.export_values();
	py::enum_<VkBlendOverlapEXT>(m, "BlendOverlapEXT", py::arithmetic())
		.value("VK_BLEND_OVERLAP_UNCORRELATED_EXT", VkBlendOverlapEXT::VK_BLEND_OVERLAP_UNCORRELATED_EXT)
		.value("VK_BLEND_OVERLAP_DISJOINT_EXT", VkBlendOverlapEXT::VK_BLEND_OVERLAP_DISJOINT_EXT)
		.value("VK_BLEND_OVERLAP_CONJOINT_EXT", VkBlendOverlapEXT::VK_BLEND_OVERLAP_CONJOINT_EXT)
		.export_values();
	py::enum_<VkCoverageModulationModeNV>(m, "CoverageModulationModeNV", py::arithmetic())
		.value("VK_COVERAGE_MODULATION_MODE_NONE_NV", VkCoverageModulationModeNV::VK_COVERAGE_MODULATION_MODE_NONE_NV)
		.value("VK_COVERAGE_MODULATION_MODE_RGB_NV", VkCoverageModulationModeNV::VK_COVERAGE_MODULATION_MODE_RGB_NV)
		.value("VK_COVERAGE_MODULATION_MODE_ALPHA_NV", VkCoverageModulationModeNV::VK_COVERAGE_MODULATION_MODE_ALPHA_NV)
		.value("VK_COVERAGE_MODULATION_MODE_RGBA_NV", VkCoverageModulationModeNV::VK_COVERAGE_MODULATION_MODE_RGBA_NV)
		.export_values();
	py::enum_<VkCoverageReductionModeNV>(m, "CoverageReductionModeNV", py::arithmetic())
		.value("VK_COVERAGE_REDUCTION_MODE_MERGE_NV", VkCoverageReductionModeNV::VK_COVERAGE_REDUCTION_MODE_MERGE_NV)
		.value("VK_COVERAGE_REDUCTION_MODE_TRUNCATE_NV", VkCoverageReductionModeNV::VK_COVERAGE_REDUCTION_MODE_TRUNCATE_NV)
		.export_values();
	py::enum_<VkValidationCacheHeaderVersionEXT>(m, "ValidationCacheHeaderVersionEXT", py::arithmetic())
		.value("VK_VALIDATION_CACHE_HEADER_VERSION_ONE_EXT", VkValidationCacheHeaderVersionEXT::VK_VALIDATION_CACHE_HEADER_VERSION_ONE_EXT)
		.export_values();
	py::enum_<VkShaderInfoTypeAMD>(m, "ShaderInfoTypeAMD", py::arithmetic())
		.value("VK_SHADER_INFO_TYPE_STATISTICS_AMD", VkShaderInfoTypeAMD::VK_SHADER_INFO_TYPE_STATISTICS_AMD)
		.value("VK_SHADER_INFO_TYPE_BINARY_AMD", VkShaderInfoTypeAMD::VK_SHADER_INFO_TYPE_BINARY_AMD)
		.value("VK_SHADER_INFO_TYPE_DISASSEMBLY_AMD", VkShaderInfoTypeAMD::VK_SHADER_INFO_TYPE_DISASSEMBLY_AMD)
		.export_values();
	py::enum_<VkQueueGlobalPriorityEXT>(m, "QueueGlobalPriorityEXT", py::arithmetic())
		.value("VK_QUEUE_GLOBAL_PRIORITY_LOW_EXT", VkQueueGlobalPriorityEXT::VK_QUEUE_GLOBAL_PRIORITY_LOW_EXT)
		.value("VK_QUEUE_GLOBAL_PRIORITY_MEDIUM_EXT", VkQueueGlobalPriorityEXT::VK_QUEUE_GLOBAL_PRIORITY_MEDIUM_EXT)
		.value("VK_QUEUE_GLOBAL_PRIORITY_HIGH_EXT", VkQueueGlobalPriorityEXT::VK_QUEUE_GLOBAL_PRIORITY_HIGH_EXT)
		.value("VK_QUEUE_GLOBAL_PRIORITY_REALTIME_EXT", VkQueueGlobalPriorityEXT::VK_QUEUE_GLOBAL_PRIORITY_REALTIME_EXT)
		.export_values();
	py::enum_<VkDebugUtilsMessageSeverityFlagBitsEXT>(m, "DebugUtilsMessageSeverityFlagBitsEXT", py::arithmetic())
		.value("VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT", VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
		.value("VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT", VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
		.value("VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT", VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		.value("VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT", VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
		.export_values();
	py::enum_<VkDebugUtilsMessageTypeFlagBitsEXT>(m, "DebugUtilsMessageTypeFlagBitsEXT", py::arithmetic())
		.value("VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT", VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
		.value("VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT", VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
		.value("VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT", VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
		.export_values();
	py::enum_<VkConservativeRasterizationModeEXT>(m, "ConservativeRasterizationModeEXT", py::arithmetic())
		.value("VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT", VkConservativeRasterizationModeEXT::VK_CONSERVATIVE_RASTERIZATION_MODE_DISABLED_EXT)
		.value("VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT", VkConservativeRasterizationModeEXT::VK_CONSERVATIVE_RASTERIZATION_MODE_OVERESTIMATE_EXT)
		.value("VK_CONSERVATIVE_RASTERIZATION_MODE_UNDERESTIMATE_EXT", VkConservativeRasterizationModeEXT::VK_CONSERVATIVE_RASTERIZATION_MODE_UNDERESTIMATE_EXT)
		.export_values();
	py::enum_<VkDescriptorBindingFlagBitsEXT>(m, "DescriptorBindingFlagBitsEXT", py::arithmetic())
		.value("VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT", VkDescriptorBindingFlagBitsEXT::VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT)
		.value("VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT_EXT", VkDescriptorBindingFlagBitsEXT::VK_DESCRIPTOR_BINDING_UPDATE_UNUSED_WHILE_PENDING_BIT_EXT)
		.value("VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT", VkDescriptorBindingFlagBitsEXT::VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT)
		.value("VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT_EXT", VkDescriptorBindingFlagBitsEXT::VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT_EXT)
		.export_values();
	py::enum_<VkVendorId>(m, "VendorId", py::arithmetic())
		.value("VK_VENDOR_ID_VIV", VkVendorId::VK_VENDOR_ID_VIV)
		.value("VK_VENDOR_ID_VSI", VkVendorId::VK_VENDOR_ID_VSI)
		.value("VK_VENDOR_ID_KAZAN", VkVendorId::VK_VENDOR_ID_KAZAN)
		.export_values();
	py::enum_<VkDriverIdKHR>(m, "DriverIdKHR", py::arithmetic())
		.value("VK_DRIVER_ID_AMD_PROPRIETARY_KHR", VkDriverIdKHR::VK_DRIVER_ID_AMD_PROPRIETARY_KHR)
		.value("VK_DRIVER_ID_AMD_OPEN_SOURCE_KHR", VkDriverIdKHR::VK_DRIVER_ID_AMD_OPEN_SOURCE_KHR)
		.value("VK_DRIVER_ID_MESA_RADV_KHR", VkDriverIdKHR::VK_DRIVER_ID_MESA_RADV_KHR)
		.value("VK_DRIVER_ID_NVIDIA_PROPRIETARY_KHR", VkDriverIdKHR::VK_DRIVER_ID_NVIDIA_PROPRIETARY_KHR)
		.value("VK_DRIVER_ID_INTEL_PROPRIETARY_WINDOWS_KHR", VkDriverIdKHR::VK_DRIVER_ID_INTEL_PROPRIETARY_WINDOWS_KHR)
		.value("VK_DRIVER_ID_INTEL_OPEN_SOURCE_MESA_KHR", VkDriverIdKHR::VK_DRIVER_ID_INTEL_OPEN_SOURCE_MESA_KHR)
		.value("VK_DRIVER_ID_IMAGINATION_PROPRIETARY_KHR", VkDriverIdKHR::VK_DRIVER_ID_IMAGINATION_PROPRIETARY_KHR)
		.value("VK_DRIVER_ID_QUALCOMM_PROPRIETARY_KHR", VkDriverIdKHR::VK_DRIVER_ID_QUALCOMM_PROPRIETARY_KHR)
		.value("VK_DRIVER_ID_ARM_PROPRIETARY_KHR", VkDriverIdKHR::VK_DRIVER_ID_ARM_PROPRIETARY_KHR)
		.value("VK_DRIVER_ID_GOOGLE_SWIFTSHADER_KHR", VkDriverIdKHR::VK_DRIVER_ID_GOOGLE_SWIFTSHADER_KHR)
		.value("VK_DRIVER_ID_GGP_PROPRIETARY_KHR", VkDriverIdKHR::VK_DRIVER_ID_GGP_PROPRIETARY_KHR)
		.export_values();
	py::enum_<VkConditionalRenderingFlagBitsEXT>(m, "ConditionalRenderingFlagBitsEXT", py::arithmetic())
		.value("VK_CONDITIONAL_RENDERING_INVERTED_BIT_EXT", VkConditionalRenderingFlagBitsEXT::VK_CONDITIONAL_RENDERING_INVERTED_BIT_EXT)
		.export_values();
	py::enum_<VkResolveModeFlagBitsKHR>(m, "ResolveModeFlagBitsKHR", py::arithmetic())
		.value("VK_RESOLVE_MODE_NONE_KHR", VkResolveModeFlagBitsKHR::VK_RESOLVE_MODE_NONE_KHR)
		.value("VK_RESOLVE_MODE_SAMPLE_ZERO_BIT_KHR", VkResolveModeFlagBitsKHR::VK_RESOLVE_MODE_SAMPLE_ZERO_BIT_KHR)
		.value("VK_RESOLVE_MODE_AVERAGE_BIT_KHR", VkResolveModeFlagBitsKHR::VK_RESOLVE_MODE_AVERAGE_BIT_KHR)
		.value("VK_RESOLVE_MODE_MIN_BIT_KHR", VkResolveModeFlagBitsKHR::VK_RESOLVE_MODE_MIN_BIT_KHR)
		.value("VK_RESOLVE_MODE_MAX_BIT_KHR", VkResolveModeFlagBitsKHR::VK_RESOLVE_MODE_MAX_BIT_KHR)
		.export_values();
	py::enum_<VkShadingRatePaletteEntryNV>(m, "ShadingRatePaletteEntryNV", py::arithmetic())
		.value("VK_SHADING_RATE_PALETTE_ENTRY_NO_INVOCATIONS_NV", VkShadingRatePaletteEntryNV::VK_SHADING_RATE_PALETTE_ENTRY_NO_INVOCATIONS_NV)
		.value("VK_SHADING_RATE_PALETTE_ENTRY_16_INVOCATIONS_PER_PIXEL_NV", VkShadingRatePaletteEntryNV::VK_SHADING_RATE_PALETTE_ENTRY_16_INVOCATIONS_PER_PIXEL_NV)
		.value("VK_SHADING_RATE_PALETTE_ENTRY_8_INVOCATIONS_PER_PIXEL_NV", VkShadingRatePaletteEntryNV::VK_SHADING_RATE_PALETTE_ENTRY_8_INVOCATIONS_PER_PIXEL_NV)
		.value("VK_SHADING_RATE_PALETTE_ENTRY_4_INVOCATIONS_PER_PIXEL_NV", VkShadingRatePaletteEntryNV::VK_SHADING_RATE_PALETTE_ENTRY_4_INVOCATIONS_PER_PIXEL_NV)
		.value("VK_SHADING_RATE_PALETTE_ENTRY_2_INVOCATIONS_PER_PIXEL_NV", VkShadingRatePaletteEntryNV::VK_SHADING_RATE_PALETTE_ENTRY_2_INVOCATIONS_PER_PIXEL_NV)
		.value("VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_PIXEL_NV", VkShadingRatePaletteEntryNV::VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_PIXEL_NV)
		.value("VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X1_PIXELS_NV", VkShadingRatePaletteEntryNV::VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X1_PIXELS_NV)
		.value("VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_1X2_PIXELS_NV", VkShadingRatePaletteEntryNV::VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_1X2_PIXELS_NV)
		.value("VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X2_PIXELS_NV", VkShadingRatePaletteEntryNV::VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X2_PIXELS_NV)
		.value("VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_4X2_PIXELS_NV", VkShadingRatePaletteEntryNV::VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_4X2_PIXELS_NV)
		.value("VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X4_PIXELS_NV", VkShadingRatePaletteEntryNV::VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_2X4_PIXELS_NV)
		.value("VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_4X4_PIXELS_NV", VkShadingRatePaletteEntryNV::VK_SHADING_RATE_PALETTE_ENTRY_1_INVOCATION_PER_4X4_PIXELS_NV)
		.export_values();
	py::enum_<VkCoarseSampleOrderTypeNV>(m, "CoarseSampleOrderTypeNV", py::arithmetic())
		.value("VK_COARSE_SAMPLE_ORDER_TYPE_DEFAULT_NV", VkCoarseSampleOrderTypeNV::VK_COARSE_SAMPLE_ORDER_TYPE_DEFAULT_NV)
		.value("VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV", VkCoarseSampleOrderTypeNV::VK_COARSE_SAMPLE_ORDER_TYPE_CUSTOM_NV)
		.value("VK_COARSE_SAMPLE_ORDER_TYPE_PIXEL_MAJOR_NV", VkCoarseSampleOrderTypeNV::VK_COARSE_SAMPLE_ORDER_TYPE_PIXEL_MAJOR_NV)
		.value("VK_COARSE_SAMPLE_ORDER_TYPE_SAMPLE_MAJOR_NV", VkCoarseSampleOrderTypeNV::VK_COARSE_SAMPLE_ORDER_TYPE_SAMPLE_MAJOR_NV)
		.export_values();
	py::enum_<VkGeometryInstanceFlagBitsNV>(m, "GeometryInstanceFlagBitsNV", py::arithmetic())
		.value("VK_GEOMETRY_INSTANCE_TRIANGLE_CULL_DISABLE_BIT_NV", VkGeometryInstanceFlagBitsNV::VK_GEOMETRY_INSTANCE_TRIANGLE_CULL_DISABLE_BIT_NV)
		.value("VK_GEOMETRY_INSTANCE_TRIANGLE_FRONT_COUNTERCLOCKWISE_BIT_NV", VkGeometryInstanceFlagBitsNV::VK_GEOMETRY_INSTANCE_TRIANGLE_FRONT_COUNTERCLOCKWISE_BIT_NV)
		.value("VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_NV", VkGeometryInstanceFlagBitsNV::VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_NV)
		.value("VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_NV", VkGeometryInstanceFlagBitsNV::VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_NV)
		.export_values();
	py::enum_<VkGeometryFlagBitsNV>(m, "GeometryFlagBitsNV", py::arithmetic())
		.value("VK_GEOMETRY_OPAQUE_BIT_NV", VkGeometryFlagBitsNV::VK_GEOMETRY_OPAQUE_BIT_NV)
		.value("VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_NV", VkGeometryFlagBitsNV::VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_NV)
		.export_values();
	py::enum_<VkBuildAccelerationStructureFlagBitsNV>(m, "BuildAccelerationStructureFlagBitsNV", py::arithmetic())
		.value("VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_NV", VkBuildAccelerationStructureFlagBitsNV::VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_NV)
		.value("VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_NV", VkBuildAccelerationStructureFlagBitsNV::VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_NV)
		.value("VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_NV", VkBuildAccelerationStructureFlagBitsNV::VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_NV)
		.value("VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_NV", VkBuildAccelerationStructureFlagBitsNV::VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_NV)
		.value("VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_NV", VkBuildAccelerationStructureFlagBitsNV::VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_NV)
		.export_values();
	py::enum_<VkCopyAccelerationStructureModeNV>(m, "CopyAccelerationStructureModeNV", py::arithmetic())
		.value("VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_NV", VkCopyAccelerationStructureModeNV::VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_NV)
		.value("VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_NV", VkCopyAccelerationStructureModeNV::VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_NV)
		.export_values();
	py::enum_<VkAccelerationStructureTypeNV>(m, "AccelerationStructureTypeNV", py::arithmetic())
		.value("VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV", VkAccelerationStructureTypeNV::VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV)
		.value("VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV", VkAccelerationStructureTypeNV::VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV)
		.export_values();
	py::enum_<VkGeometryTypeNV>(m, "GeometryTypeNV", py::arithmetic())
		.value("VK_GEOMETRY_TYPE_TRIANGLES_NV", VkGeometryTypeNV::VK_GEOMETRY_TYPE_TRIANGLES_NV)
		.value("VK_GEOMETRY_TYPE_AABBS_NV", VkGeometryTypeNV::VK_GEOMETRY_TYPE_AABBS_NV)
		.export_values();
	py::enum_<VkAccelerationStructureMemoryRequirementsTypeNV>(m, "AccelerationStructureMemoryRequirementsTypeNV", py::arithmetic())
		.value("VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV", VkAccelerationStructureMemoryRequirementsTypeNV::VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV)
		.value("VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_NV", VkAccelerationStructureMemoryRequirementsTypeNV::VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_NV)
		.value("VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_UPDATE_SCRATCH_NV", VkAccelerationStructureMemoryRequirementsTypeNV::VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_UPDATE_SCRATCH_NV)
		.export_values();
	py::enum_<VkRayTracingShaderGroupTypeNV>(m, "RayTracingShaderGroupTypeNV", py::arithmetic())
		.value("VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_NV", VkRayTracingShaderGroupTypeNV::VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_NV)
		.value("VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_NV", VkRayTracingShaderGroupTypeNV::VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_NV)
		.value("VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_NV", VkRayTracingShaderGroupTypeNV::VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_NV)
		.export_values();
	py::enum_<VkMemoryOverallocationBehaviorAMD>(m, "MemoryOverallocationBehaviorAMD", py::arithmetic())
		.value("VK_MEMORY_OVERALLOCATION_BEHAVIOR_DEFAULT_AMD", VkMemoryOverallocationBehaviorAMD::VK_MEMORY_OVERALLOCATION_BEHAVIOR_DEFAULT_AMD)
		.value("VK_MEMORY_OVERALLOCATION_BEHAVIOR_ALLOWED_AMD", VkMemoryOverallocationBehaviorAMD::VK_MEMORY_OVERALLOCATION_BEHAVIOR_ALLOWED_AMD)
		.value("VK_MEMORY_OVERALLOCATION_BEHAVIOR_DISALLOWED_AMD", VkMemoryOverallocationBehaviorAMD::VK_MEMORY_OVERALLOCATION_BEHAVIOR_DISALLOWED_AMD)
		.export_values();
	py::enum_<VkScopeNV>(m, "ScopeNV", py::arithmetic())
		.value("VK_SCOPE_DEVICE_NV", VkScopeNV::VK_SCOPE_DEVICE_NV)
		.value("VK_SCOPE_WORKGROUP_NV", VkScopeNV::VK_SCOPE_WORKGROUP_NV)
		.value("VK_SCOPE_SUBGROUP_NV", VkScopeNV::VK_SCOPE_SUBGROUP_NV)
		.value("VK_SCOPE_QUEUE_FAMILY_NV", VkScopeNV::VK_SCOPE_QUEUE_FAMILY_NV)
		.export_values();
	py::enum_<VkComponentTypeNV>(m, "ComponentTypeNV", py::arithmetic())
		.value("VK_COMPONENT_TYPE_FLOAT16_NV", VkComponentTypeNV::VK_COMPONENT_TYPE_FLOAT16_NV)
		.value("VK_COMPONENT_TYPE_FLOAT32_NV", VkComponentTypeNV::VK_COMPONENT_TYPE_FLOAT32_NV)
		.value("VK_COMPONENT_TYPE_FLOAT64_NV", VkComponentTypeNV::VK_COMPONENT_TYPE_FLOAT64_NV)
		.value("VK_COMPONENT_TYPE_SINT8_NV", VkComponentTypeNV::VK_COMPONENT_TYPE_SINT8_NV)
		.value("VK_COMPONENT_TYPE_SINT16_NV", VkComponentTypeNV::VK_COMPONENT_TYPE_SINT16_NV)
		.value("VK_COMPONENT_TYPE_SINT32_NV", VkComponentTypeNV::VK_COMPONENT_TYPE_SINT32_NV)
		.value("VK_COMPONENT_TYPE_SINT64_NV", VkComponentTypeNV::VK_COMPONENT_TYPE_SINT64_NV)
		.value("VK_COMPONENT_TYPE_UINT8_NV", VkComponentTypeNV::VK_COMPONENT_TYPE_UINT8_NV)
		.value("VK_COMPONENT_TYPE_UINT16_NV", VkComponentTypeNV::VK_COMPONENT_TYPE_UINT16_NV)
		.value("VK_COMPONENT_TYPE_UINT32_NV", VkComponentTypeNV::VK_COMPONENT_TYPE_UINT32_NV)
		.value("VK_COMPONENT_TYPE_UINT64_NV", VkComponentTypeNV::VK_COMPONENT_TYPE_UINT64_NV)
		.export_values();
	py::enum_<VkPipelineCreationFeedbackFlagBitsEXT>(m, "PipelineCreationFeedbackFlagBitsEXT", py::arithmetic())
		.value("VK_PIPELINE_CREATION_FEEDBACK_VALID_BIT_EXT", VkPipelineCreationFeedbackFlagBitsEXT::VK_PIPELINE_CREATION_FEEDBACK_VALID_BIT_EXT)
		.value("VK_PIPELINE_CREATION_FEEDBACK_APPLICATION_PIPELINE_CACHE_HIT_BIT_EXT", VkPipelineCreationFeedbackFlagBitsEXT::VK_PIPELINE_CREATION_FEEDBACK_APPLICATION_PIPELINE_CACHE_HIT_BIT_EXT)
		.value("VK_PIPELINE_CREATION_FEEDBACK_BASE_PIPELINE_ACCELERATION_BIT_EXT", VkPipelineCreationFeedbackFlagBitsEXT::VK_PIPELINE_CREATION_FEEDBACK_BASE_PIPELINE_ACCELERATION_BIT_EXT)
		.export_values();
	py::enum_<VkFullScreenExclusiveEXT>(m, "FullScreenExclusiveEXT", py::arithmetic())
		.value("VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT", VkFullScreenExclusiveEXT::VK_FULL_SCREEN_EXCLUSIVE_DEFAULT_EXT)
		.value("VK_FULL_SCREEN_EXCLUSIVE_ALLOWED_EXT", VkFullScreenExclusiveEXT::VK_FULL_SCREEN_EXCLUSIVE_ALLOWED_EXT)
		.value("VK_FULL_SCREEN_EXCLUSIVE_DISALLOWED_EXT", VkFullScreenExclusiveEXT::VK_FULL_SCREEN_EXCLUSIVE_DISALLOWED_EXT)
		.value("VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT", VkFullScreenExclusiveEXT::VK_FULL_SCREEN_EXCLUSIVE_APPLICATION_CONTROLLED_EXT)
		.export_values();
	py::enum_<VkPerformanceConfigurationTypeINTEL>(m, "PerformanceConfigurationTypeINTEL", py::arithmetic())
		.value("VK_PERFORMANCE_CONFIGURATION_TYPE_COMMAND_QUEUE_METRICS_DISCOVERY_ACTIVATED_INTEL", VkPerformanceConfigurationTypeINTEL::VK_PERFORMANCE_CONFIGURATION_TYPE_COMMAND_QUEUE_METRICS_DISCOVERY_ACTIVATED_INTEL)
		.export_values();
	py::enum_<VkQueryPoolSamplingModeINTEL>(m, "QueryPoolSamplingModeINTEL", py::arithmetic())
		.value("VK_QUERY_POOL_SAMPLING_MODE_MANUAL_INTEL", VkQueryPoolSamplingModeINTEL::VK_QUERY_POOL_SAMPLING_MODE_MANUAL_INTEL)
		.export_values();
	py::enum_<VkPerformanceOverrideTypeINTEL>(m, "PerformanceOverrideTypeINTEL", py::arithmetic())
		.value("VK_PERFORMANCE_OVERRIDE_TYPE_NULL_HARDWARE_INTEL", VkPerformanceOverrideTypeINTEL::VK_PERFORMANCE_OVERRIDE_TYPE_NULL_HARDWARE_INTEL)
		.value("VK_PERFORMANCE_OVERRIDE_TYPE_FLUSH_GPU_CACHES_INTEL", VkPerformanceOverrideTypeINTEL::VK_PERFORMANCE_OVERRIDE_TYPE_FLUSH_GPU_CACHES_INTEL)
		.export_values();
	py::enum_<VkPerformanceParameterTypeINTEL>(m, "PerformanceParameterTypeINTEL", py::arithmetic())
		.value("VK_PERFORMANCE_PARAMETER_TYPE_HW_COUNTERS_SUPPORTED_INTEL", VkPerformanceParameterTypeINTEL::VK_PERFORMANCE_PARAMETER_TYPE_HW_COUNTERS_SUPPORTED_INTEL)
		.value("VK_PERFORMANCE_PARAMETER_TYPE_STREAM_MARKER_VALID_BITS_INTEL", VkPerformanceParameterTypeINTEL::VK_PERFORMANCE_PARAMETER_TYPE_STREAM_MARKER_VALID_BITS_INTEL)
		.export_values();
	py::enum_<VkPerformanceValueTypeINTEL>(m, "PerformanceValueTypeINTEL", py::arithmetic())
		.value("VK_PERFORMANCE_VALUE_TYPE_UINT32_INTEL", VkPerformanceValueTypeINTEL::VK_PERFORMANCE_VALUE_TYPE_UINT32_INTEL)
		.value("VK_PERFORMANCE_VALUE_TYPE_UINT64_INTEL", VkPerformanceValueTypeINTEL::VK_PERFORMANCE_VALUE_TYPE_UINT64_INTEL)
		.value("VK_PERFORMANCE_VALUE_TYPE_FLOAT_INTEL", VkPerformanceValueTypeINTEL::VK_PERFORMANCE_VALUE_TYPE_FLOAT_INTEL)
		.value("VK_PERFORMANCE_VALUE_TYPE_BOOL_INTEL", VkPerformanceValueTypeINTEL::VK_PERFORMANCE_VALUE_TYPE_BOOL_INTEL)
		.value("VK_PERFORMANCE_VALUE_TYPE_STRING_INTEL", VkPerformanceValueTypeINTEL::VK_PERFORMANCE_VALUE_TYPE_STRING_INTEL)
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

