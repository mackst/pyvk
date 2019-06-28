#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#include "volk.h"
#include "pipeline.h"
#include "descriptors.h"

namespace py = pybind11;


class SurfaceKHR;
class SwapchainKHR;
class Image;
class ShaderModule;


#ifndef CREATEINFO_H
#define CREATEINFO_H


class ApplicationInfo
{
public:
	ApplicationInfo();
	ApplicationInfo(std::string _appName, std::string _engineName, uint32_t _appVersion, uint32_t _engineVersion, uint32_t _apiVersion);
	~ApplicationInfo();

	void getVKStruct(VkApplicationInfo *info);

	uint32_t appVersion = 0;
	uint32_t engineVersion = 0;
	uint32_t apiVersion = 0;
	std::string appName = "";
	std::string engineName = "";
};


class DebugUtilsMessengerUserData
{
public:
	DebugUtilsMessengerUserData();
	~DebugUtilsMessengerUserData();

	py::function pycallback = py::none();
	py::dict data;
};


class DebugUtilsMessengerCreateInfoEXT
{
public:
	DebugUtilsMessengerCreateInfoEXT();
	DebugUtilsMessengerCreateInfoEXT(DebugUtilsMessengerCreateInfoEXT &info);
	~DebugUtilsMessengerCreateInfoEXT();

	py::function getUserCallback() { return userData.pycallback; }
	void setUserCallback(py::function func) { userData.pycallback = func; }

	py::dict getUserData() { return userData.data; }
	void setUserData(py::dict data) { userData.data = data; }

	void setMessageSeverity(VkDebugUtilsMessageSeverityFlagBitsEXT ms) { messageSeverity = ms; }
	void setMessageSeverity(uint32_t ms) { messageSeverity = (VkDebugUtilsMessageSeverityFlagBitsEXT)ms; }
	VkDebugUtilsMessageSeverityFlagBitsEXT getMessageSeverity() { return messageSeverity; }

	//void setMessageType(VkDebugUtilsMessageTypeFlagsEXT mt) { messageType = mt; }
	void setMessageType(uint32_t mt) { messageType = (VkDebugUtilsMessageTypeFlagsEXT)mt; }
	VkDebugUtilsMessageTypeFlagsEXT getMessageType() { return messageType; }

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

	void getVKStruct(VkDebugUtilsMessengerCreateInfoEXT *info);

	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity;
	VkDebugUtilsMessageTypeFlagsEXT messageType;

	DebugUtilsMessengerUserData userData;
};


class InstanceCreateInfo
{
public:
	InstanceCreateInfo();
	InstanceCreateInfo(ApplicationInfo &appInfo, std::vector<std::string> &layerNames, std::vector<std::string> &extentsionNames);
	~InstanceCreateInfo();

	void setLayerNames(std::vector<std::string> &names);
	std::vector<std::string> getLayerNames() { return layerNames; }
	void setExtensionNames(std::vector<std::string> &names);
	std::vector<std::string> getExtensionNames() { return extensionNames; }
	void setpNext(DebugUtilsMessengerCreateInfoEXT *info) { pNext = info; }
	DebugUtilsMessengerCreateInfoEXT * getpNext() { return pNext; }

	void getVKStruct(VkInstanceCreateInfo *info);

	ApplicationInfo appInfo;
	std::vector<std::string> layerNames = {};
	std::vector<std::string> extensionNames = {};
	std::vector<const char*> lnames = {};
	std::vector<const char*> enames = {};

	DebugUtilsMessengerCreateInfoEXT *pNext = nullptr;
};


class DeviceQueueCreateInfo
{
public:
	DeviceQueueCreateInfo();
	DeviceQueueCreateInfo(uint32_t _queueFamilyIndex, std::vector<float> &_queuePriorities);
	~DeviceQueueCreateInfo();

	//std::vector<float> getQueuePriorities() { return queuePriorities; }
	//void setQueuePriorities(std::vector<float> &_queuePriorities);

	void getVKStruct(VkDeviceQueueCreateInfo *info);

	void* pNext = nullptr;
	VkDeviceQueueCreateFlags flags = 0;
	uint32_t queueFamilyIndex;
	std::vector<float> queuePriorities;
};



class DeviceCreateInfo
{
public:
	DeviceCreateInfo();
	~DeviceCreateInfo();

	void setLayerNames(std::vector<std::string> &names);
	std::vector<std::string> getLayerNames() { return layerNames; }
	void setExtensionNames(std::vector<std::string> &names);
	std::vector<std::string> getExtensionNames() { return extensionNames; }
	void setQueueCreateInfos(std::vector<DeviceQueueCreateInfo> infos);
	std::vector<DeviceQueueCreateInfo> getQueueCreateInfos() { return queueCreateInfos; }

	void getVKStruct(VkDeviceCreateInfo *info);

	std::vector<std::string> layerNames = {};
	std::vector<std::string> extensionNames = {};
	std::vector<const char*> lnames = {};
	std::vector<const char*> enames = {};
	std::vector<DeviceQueueCreateInfo> queueCreateInfos = {};
	std::vector<VkDeviceQueueCreateInfo> _queueCreateInfos = {};

	VkDeviceCreateFlags flags = 0;
	VkPhysicalDeviceFeatures enabledFeatures;
	void* pNext = nullptr;
};


class SwapchainCreateInfoKHR
{
public:
	SwapchainCreateInfoKHR();
	~SwapchainCreateInfoKHR();

	void getVKStruct(VkSwapchainCreateInfoKHR *info);

	const void* pNext = nullptr;
	VkSwapchainCreateFlagsKHR flags = 0;
	SurfaceKHR *surface = nullptr;
	uint32_t minImageCount = 0;
	VkFormat imageFormat = VK_FORMAT_UNDEFINED;
	VkColorSpaceKHR imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	VkExtent2D imageExtent;
	uint32_t imageArrayLayers = 1;
	VkImageUsageFlags imageUsage;
	VkSharingMode imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	std::vector<uint32_t> queueFamilyIndices = {};
	VkSurfaceTransformFlagBitsKHR preTransform;
	VkCompositeAlphaFlagBitsKHR compositeAlpha;
	VkPresentModeKHR presentMode;
	VkBool32 clipped = false;
	SwapchainKHR *oldSwapchain = nullptr;
};


class ImageViewCreateInfo
{
public:
	ImageViewCreateInfo();
	~ImageViewCreateInfo();

	void getVKStruct(VkImageViewCreateInfo *info);

	const void* pNext = nullptr;
	VkImageViewCreateFlags flags = 0;
	Image *image = nullptr;
	VkImageViewType viewType;
	VkFormat format;
	VkComponentMapping components;
	VkImageSubresourceRange subresourceRange;
};


class PipelineShaderStageCreateInfo
{
public:
	PipelineShaderStageCreateInfo();
	PipelineShaderStageCreateInfo(VkShaderStageFlagBits shaderStage, ShaderModule *shaderModule, std::string &funcName);
	~PipelineShaderStageCreateInfo();

	void getVKStruct(VkPipelineShaderStageCreateInfo *info);

	const void* pNext = nullptr;
	VkShaderStageFlagBits stage;
	ShaderModule *module = nullptr;
	std::string name;
};


class PipelineVertexInputStateCreateInfo
{
public:
	PipelineVertexInputStateCreateInfo();
	~PipelineVertexInputStateCreateInfo();

	void getVKStruct(VkPipelineVertexInputStateCreateInfo *info);

	const void* pNext = nullptr;
	std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
	std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;
};


class PipelineViewportStateCreateInfo
{
public:
	PipelineViewportStateCreateInfo();
	~PipelineViewportStateCreateInfo();

	void getVKStruct(VkPipelineViewportStateCreateInfo *info);

	const void* pNext = nullptr;
	std::vector<VkViewport> viewports;
	std::vector<VkRect2D> scissors;
};


class PipelineColorBlendStateCreateInfo
{
public:
	PipelineColorBlendStateCreateInfo();
	~PipelineColorBlendStateCreateInfo();

	void getVKStruct(VkPipelineColorBlendStateCreateInfo *info);

	const void* pNext = nullptr;
	VkBool32 logicOpEnable;
	VkLogicOp logicOp;
	std::vector<VkPipelineColorBlendAttachmentState> attachments;
	std::vector<float> blendConstants;
};


class PipelineLayoutCreateInfo
{
public:
	PipelineLayoutCreateInfo();
	~PipelineLayoutCreateInfo();

	std::vector<DescriptorSetLayout> getSetLayouts() { return setLayouts; }
	void setSetLayouts(std::vector<DescriptorSetLayout> &layouts);

	void getVKStruct(VkPipelineLayoutCreateInfo *info);

	const void* pNext = nullptr;
	std::vector<DescriptorSetLayout> setLayouts;
	std::vector<VkDescriptorSetLayout> _setLayouts;
	std::vector<VkPushConstantRange> pushConstantRanges;
};


class GraphicsPipelineCreateInfo
{
public:
	GraphicsPipelineCreateInfo();
	~GraphicsPipelineCreateInfo();

	void setStages(std::vector<PipelineShaderStageCreateInfo*> &infos);
	std::vector<PipelineShaderStageCreateInfo*> getStages() { return stages; }
	void setVertexInputState(PipelineVertexInputStateCreateInfo &info);
	PipelineVertexInputStateCreateInfo getVertexInputState() { return vertexInputState; }
	void setViewportState(PipelineViewportStateCreateInfo &info);
	PipelineViewportStateCreateInfo getViewportState() { return viewportState; }
	void setColorBlendState(PipelineColorBlendStateCreateInfo &info);
	PipelineColorBlendStateCreateInfo getColorBlendState() { return colorBlendState; }

	void getVKStruct(VkGraphicsPipelineCreateInfo *info);

	const void* pNext = nullptr;
	std::vector<PipelineShaderStageCreateInfo*> stages;
	std::vector<VkPipelineShaderStageCreateInfo> _stages;
	PipelineVertexInputStateCreateInfo vertexInputState;
	VkPipelineVertexInputStateCreateInfo _vertexInputState = {};
	const VkPipelineInputAssemblyStateCreateInfo *inputAssemblyState = nullptr;
	const VkPipelineTessellationStateCreateInfo *tessellationState = nullptr;
	PipelineViewportStateCreateInfo viewportState;
	VkPipelineViewportStateCreateInfo _viewportState = {};
	const VkPipelineRasterizationStateCreateInfo *rasterizationState = nullptr;
	const VkPipelineMultisampleStateCreateInfo *multisampleState = nullptr;
	const VkPipelineDepthStencilStateCreateInfo *depthStencilState = nullptr;
	PipelineColorBlendStateCreateInfo colorBlendState;
	VkPipelineColorBlendStateCreateInfo _colorBlendState = {};
	PipelineLayout *layout = nullptr;
	RenderPass *renderPass = nullptr;
	uint32_t subpass;
	Pipeline *basePipelineHandle = nullptr;
	int32_t basePipelineIndex = 0;
};

#endif // !CREATEINFO_H
