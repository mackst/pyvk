#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include "instance.h"
#include "device.h"



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
		.def("getPhysicalDevices", &Instance::getPhysicalDevices)
		.def_property_readonly("isValid", &Instance::isValid)
		.def_static("version", &Instance::version)
		.def_static("getLayerProperties", &Instance::layerProperties)
		.def_static("getExtensionProperties", &Instance::extensionProperties, py::arg("layerName") = nullptr);

	py::class_<PhysicalDevice> PhysicalDeviceClass(m, "PhysicalDevice");
	PhysicalDeviceClass
		.def(py::init<>())
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
		.def_property_readonly("isValid", &Device::isValid);

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
		.value("TRANSFER", VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT)
		.export_values();


	// extensions

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

