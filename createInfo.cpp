#include "createInfo.h"
#include "extensions.h"
#include "image.h"
#include "shadermodule.h"
#include "utils.h"
#include "cmdBuffers.h"

ApplicationInfo::ApplicationInfo()
{
}

ApplicationInfo::ApplicationInfo(std::string _appName, std::string _engineName, uint32_t _appVersion, uint32_t _engineVersion, uint32_t _apiVersion):
	appName(_appName), engineName(_engineName), appVersion(_appVersion), engineVersion(_engineVersion), apiVersion(_apiVersion)
{
}

ApplicationInfo::~ApplicationInfo()
{
}

void ApplicationInfo::getVKStruct(VkApplicationInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info->apiVersion = apiVersion;
	info->applicationVersion = appVersion;
	info->engineVersion = engineVersion;
	info->pApplicationName = appName.c_str();
	info->pEngineName = engineName.c_str();
}

InstanceCreateInfo::InstanceCreateInfo()
{
}

InstanceCreateInfo::InstanceCreateInfo(ApplicationInfo & _appInfo, std::vector<std::string>& _layerNames, std::vector<std::string>& _extentsionNames):
	appInfo(_appInfo)
{
	setLayerNames(_layerNames);
	setExtensionNames(_extentsionNames);
}

InstanceCreateInfo::~InstanceCreateInfo()
{
	pNext = nullptr;
}

void InstanceCreateInfo::setLayerNames(std::vector<std::string>& names)
{
	layerNames = names;
	lnames = vecStrToVecChar(layerNames);
}

void InstanceCreateInfo::setExtensionNames(std::vector<std::string>& names)
{
	extensionNames = names;
	enames = vecStrToVecChar(extensionNames);
}

void InstanceCreateInfo::getVKStruct(VkInstanceCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

	info->enabledLayerCount = static_cast<uint32_t>(layerNames.size());
	info->enabledExtensionCount = static_cast<uint32_t>(extensionNames.size());

	if (info->enabledLayerCount > 0)
		info->ppEnabledLayerNames = lnames.data();
	if (info->enabledExtensionCount > 0)
		info->ppEnabledExtensionNames = enames.data();
}



DebugUtilsMessengerCreateInfoEXT::DebugUtilsMessengerCreateInfoEXT()
{
}

DebugUtilsMessengerCreateInfoEXT::DebugUtilsMessengerCreateInfoEXT(DebugUtilsMessengerCreateInfoEXT & info)
{
	messageSeverity = info.messageSeverity;
	messageType = info.messageType;
	userData = info.userData;
}

DebugUtilsMessengerCreateInfoEXT::~DebugUtilsMessengerCreateInfoEXT()
{
	userData = {};
}

VKAPI_ATTR VkBool32 VKAPI_CALL DebugUtilsMessengerCreateInfoEXT::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData, void * pUserData)
{
	if (pUserData == nullptr) return VK_FALSE;
	//auto data = reinterpret_cast<DebugUtilsMessengerUserData*>(pUserData);
	auto data = (DebugUtilsMessengerUserData*)pUserData;

	if (!data->pycallback.is_none())
		data->pycallback(messageSeverity, messageType, pCallbackData, data->data);
 
	return VK_FALSE;
}

void DebugUtilsMessengerCreateInfoEXT::getVKStruct(VkDebugUtilsMessengerCreateInfoEXT * info)
{
	info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	info->messageSeverity = messageSeverity;
	info->messageType = messageType;
	info->pfnUserCallback = debugCallback;
	info->pUserData = &userData;
}

DebugUtilsMessengerUserData::DebugUtilsMessengerUserData()
{
}

DebugUtilsMessengerUserData::~DebugUtilsMessengerUserData()
{
	pycallback = py::none();
	//data.clear();
}

DeviceCreateInfo::DeviceCreateInfo()
{
}

DeviceCreateInfo::~DeviceCreateInfo()
{
}

void DeviceCreateInfo::setLayerNames(std::vector<std::string>& names)
{
	layerNames = names;
	lnames = vecStrToVecChar(layerNames);
}

void DeviceCreateInfo::setExtensionNames(std::vector<std::string>& names)
{
	extensionNames = names;
	enames = vecStrToVecChar(extensionNames);
}

void DeviceCreateInfo::setQueueCreateInfos(std::vector<DeviceQueueCreateInfo> infos)
{
	queueCreateInfos = infos;
	for (auto info : queueCreateInfos)
	{
		VkDeviceQueueCreateInfo _info = {};
		info.getVKStruct(&_info);
		_queueCreateInfos.emplace_back(_info);
	}
}

void DeviceCreateInfo::getVKStruct(VkDeviceCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	info->pNext = pNext;
	info->flags = flags;
	info->pEnabledFeatures = &enabledFeatures;
	info->enabledExtensionCount = static_cast<uint32_t>(enames.size());
	if (info->enabledExtensionCount > 0)
		info->ppEnabledExtensionNames = enames.data();
	info->enabledLayerCount = static_cast<uint32_t>(lnames.size());
	if (info->enabledLayerCount > 0)
		info->ppEnabledLayerNames = lnames.data();
	info->queueCreateInfoCount = static_cast<uint32_t>(_queueCreateInfos.size());
	if (info->queueCreateInfoCount > 0)
		info->pQueueCreateInfos = _queueCreateInfos.data();
}

DeviceQueueCreateInfo::DeviceQueueCreateInfo()
{
}

DeviceQueueCreateInfo::DeviceQueueCreateInfo(uint32_t _queueFamilyIndex, std::vector<float>& _queuePriorities)
	:queueFamilyIndex(_queueFamilyIndex), queuePriorities(_queuePriorities)
{
}

DeviceQueueCreateInfo::~DeviceQueueCreateInfo()
{
}

//void DeviceQueueCreateInfo::setQueuePriorities(std::vector<float>& _queuePriorities)
//{
//}

void DeviceQueueCreateInfo::getVKStruct(VkDeviceQueueCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	info->pNext = pNext;
	info->flags = flags;
	info->queueFamilyIndex = queueFamilyIndex;
	info->queueCount = static_cast<uint32_t>(queuePriorities.size());
	if (info->queueCount > 0)
		info->pQueuePriorities = queuePriorities.data();
}

SwapchainCreateInfoKHR::SwapchainCreateInfoKHR()
{
}

SwapchainCreateInfoKHR::~SwapchainCreateInfoKHR()
{
	pNext = nullptr;
	surface = nullptr;
	oldSwapchain = nullptr;
}

void SwapchainCreateInfoKHR::getVKStruct(VkSwapchainCreateInfoKHR * info)
{
	info->sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	info->clipped = clipped;
	info->compositeAlpha = compositeAlpha;
	info->flags = flags;
	info->imageArrayLayers = imageArrayLayers;
	info->imageColorSpace = imageColorSpace;
	info->imageExtent = imageExtent;
	info->imageFormat = imageFormat;
	info->imageSharingMode = imageSharingMode;
	info->imageUsage = imageUsage;
	info->minImageCount = minImageCount;
	info->pNext = pNext;
	info->presentMode = presentMode;
	info->preTransform = preTransform;
	info->queueFamilyIndexCount = static_cast<uint32_t>(queueFamilyIndices.size());
	if (info->queueFamilyIndexCount > 0)
		info->pQueueFamilyIndices = queueFamilyIndices.data();
	if (surface)
		info->surface = surface->vkHandle;
	else
		info->surface = VK_NULL_HANDLE;
	if (oldSwapchain)
		info->oldSwapchain = oldSwapchain->vkHandle;
	else
		info->oldSwapchain = VK_NULL_HANDLE;
}

ImageViewCreateInfo::ImageViewCreateInfo()
{
}

ImageViewCreateInfo::~ImageViewCreateInfo()
{
	image = nullptr;
}

void ImageViewCreateInfo::getVKStruct(VkImageViewCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	info->pNext = pNext;
	info->flags = flags;
	info->image = image->vkHandle;
	info->viewType = viewType;
	info->format = format;
	info->components = components;
	info->subresourceRange = subresourceRange;
}

PipelineShaderStageCreateInfo::PipelineShaderStageCreateInfo()
{
}

PipelineShaderStageCreateInfo::PipelineShaderStageCreateInfo(VkShaderStageFlagBits shaderStage, ShaderModule *shaderModule, std::string &funcName)
	:stage(shaderStage), module(shaderModule), name(funcName)
{
}


PipelineShaderStageCreateInfo::~PipelineShaderStageCreateInfo()
{
	module = nullptr;
	pNext = nullptr;
}

void PipelineShaderStageCreateInfo::getVKStruct(VkPipelineShaderStageCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	info->module = module->vkHandle;
	info->pName = name.c_str();
	info->stage = stage;
	info->pNext = pNext;
}


PipelineVertexInputStateCreateInfo::PipelineVertexInputStateCreateInfo()
{
}

PipelineVertexInputStateCreateInfo::~PipelineVertexInputStateCreateInfo()
{
	pNext = nullptr;
}

void PipelineVertexInputStateCreateInfo::getVKStruct(VkPipelineVertexInputStateCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	info->pNext = pNext;
	info->vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexAttributeDescriptions.size());
	if (info->vertexAttributeDescriptionCount > 0)
		info->pVertexAttributeDescriptions = vertexAttributeDescriptions.data();
	info->vertexBindingDescriptionCount = static_cast<uint32_t>(vertexBindingDescriptions.size());
	if (info->vertexBindingDescriptionCount > 0)
		info->pVertexBindingDescriptions = vertexBindingDescriptions.data();
}

PipelineViewportStateCreateInfo::PipelineViewportStateCreateInfo()
{
}

PipelineViewportStateCreateInfo::~PipelineViewportStateCreateInfo()
{
	pNext = nullptr;
}

void PipelineViewportStateCreateInfo::getVKStruct(VkPipelineViewportStateCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	info->pNext = pNext;
	info->scissorCount = static_cast<uint32_t>(scissors.size());
	if (info->scissorCount > 0)
		info->pScissors = scissors.data();
	info->viewportCount = static_cast<uint32_t>(viewports.size());
	if (info->viewportCount > 0)
		info->pViewports = viewports.data();
}


PipelineColorBlendStateCreateInfo::PipelineColorBlendStateCreateInfo()
{
}

PipelineColorBlendStateCreateInfo::~PipelineColorBlendStateCreateInfo()
{
	pNext = nullptr;
}

void PipelineColorBlendStateCreateInfo::getVKStruct(VkPipelineColorBlendStateCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	info->pNext = pNext;
	info->logicOp = logicOp;
	info->logicOpEnable = logicOpEnable;
	info->attachmentCount = static_cast<uint32_t>(attachments.size());
	if (info->attachmentCount > 0)
		info->pAttachments = attachments.data();
	info->blendConstants[0] = blendConstants[0];
	info->blendConstants[1] = blendConstants[1];
	info->blendConstants[2] = blendConstants[2];
	info->blendConstants[3] = blendConstants[3];
}


PipelineLayoutCreateInfo::PipelineLayoutCreateInfo()
{
}

PipelineLayoutCreateInfo::~PipelineLayoutCreateInfo()
{
	pNext = nullptr;
	setLayouts = {};
	_setLayouts = {};
}

void PipelineLayoutCreateInfo::setSetLayouts(std::vector<DescriptorSetLayout>& layouts)
{
	setLayouts = layouts;
	for (auto setLayout : setLayouts)
	{
		_setLayouts.emplace_back(setLayout.vkHandle);
	}
}

void PipelineLayoutCreateInfo::getVKStruct(VkPipelineLayoutCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	info->pNext = pNext;
	info->setLayoutCount = static_cast<uint32_t>(setLayouts.size());
	if (info->setLayoutCount > 0)
		info->pSetLayouts = _setLayouts.data();
	info->pushConstantRangeCount = static_cast<uint32_t>(pushConstantRanges.size());
	if (info->pushConstantRangeCount > 0)
		info->pPushConstantRanges = pushConstantRanges.data();
}

GraphicsPipelineCreateInfo::GraphicsPipelineCreateInfo()
{
}

GraphicsPipelineCreateInfo::~GraphicsPipelineCreateInfo()
{
	pNext = nullptr;
	inputAssemblyState = nullptr;
	tessellationState = nullptr;
	rasterizationState = nullptr;
	multisampleState = nullptr;
	depthStencilState = nullptr;
	layout = nullptr;
	renderPass = nullptr;
	basePipelineHandle = nullptr;
	stages = {};
	_stages = {};
}

void GraphicsPipelineCreateInfo::setStages(std::vector<PipelineShaderStageCreateInfo*>& infos)
{
	stages = infos;
	for (auto i : stages)
	{
		VkPipelineShaderStageCreateInfo info = {};
		i->getVKStruct(&info);
		_stages.emplace_back(info);
	}
}

void GraphicsPipelineCreateInfo::setVertexInputState(PipelineVertexInputStateCreateInfo & info)
{
	vertexInputState = info;
	vertexInputState.getVKStruct(&_vertexInputState);
}

void GraphicsPipelineCreateInfo::setViewportState(PipelineViewportStateCreateInfo & info)
{
	viewportState = info;
	viewportState.getVKStruct(&_viewportState);
}

void GraphicsPipelineCreateInfo::setColorBlendState(PipelineColorBlendStateCreateInfo & info)
{
	colorBlendState = info;
	colorBlendState.getVKStruct(&_colorBlendState);
}

void GraphicsPipelineCreateInfo::getVKStruct(VkGraphicsPipelineCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	info->pNext = pNext;
	info->stageCount = static_cast<uint32_t>(stages.size());
	if (info->stageCount > 0)
		info->pStages = _stages.data();

	info->pVertexInputState = &_vertexInputState;
	info->pInputAssemblyState = inputAssemblyState;
	info->pTessellationState = tessellationState;
	info->pViewportState = &_viewportState;
	info->pRasterizationState = rasterizationState;
	info->pMultisampleState = multisampleState;
	info->pDepthStencilState = depthStencilState;
	info->pColorBlendState = &_colorBlendState;
	info->layout = layout->vkHandle;
	info->renderPass = renderPass->vkHandle;
	info->basePipelineIndex = basePipelineIndex;
	info->subpass = subpass;
	if (basePipelineHandle != nullptr)
	{
		info->basePipelineHandle = basePipelineHandle->vkHandle;
	}
	else
	{
		info->basePipelineHandle = VK_NULL_HANDLE;
	}
}

ComputePipelineCreateInfo::ComputePipelineCreateInfo()
{
}

ComputePipelineCreateInfo::~ComputePipelineCreateInfo()
{
	layout = nullptr;
	basePipelineHandle = nullptr;
}

void ComputePipelineCreateInfo::setStage(PipelineShaderStageCreateInfo & info)
{
	stage = info;
	stage.getVKStruct(&_stage);
}

void ComputePipelineCreateInfo::getVKStruct(VkComputePipelineCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
	info->flags = flags;
	info->stage = _stage;
	info->layout = layout->vkHandle;
	info->basePipelineHandle = basePipelineHandle->vkHandle;
	info->basePipelineIndex = basePipelineIndex;
}

CommandBufferAllocateInfo::CommandBufferAllocateInfo()
{
}

CommandBufferAllocateInfo::~CommandBufferAllocateInfo()
{
	pNext = nullptr;
	commandPool = nullptr;
}

void CommandBufferAllocateInfo::getVKStruct(VkCommandBufferAllocateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	info->pNext = pNext;
	info->commandBufferCount = commandBufferCount;
	info->commandPool = commandPool->vkHandle;
	info->level = level;
}
