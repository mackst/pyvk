#include "pipeline.h"
#include "exception.h"
#include "createInfo.h"

PipelineLayout::PipelineLayout()
{
}

PipelineLayout::PipelineLayout(VkDevice device, py::dict createInfo) : _device(device)
{
	getFuncPointers();

	//py::list setLayoutList = createInfo["setLayouts"].cast<py::list>();
	//py::list pushConstantRangeList = createInfo["pushConstantRanges"].cast<py::list>();

	VkPipelineLayoutCreateInfo _createInfo = {};
	_createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	_createInfo.setLayoutCount = 0;
	_createInfo.pushConstantRangeCount = 0;
	//auto _createInfo = dictToVkPipelineLayoutCreateInfo(createInfo);
	checkVKResult(_vkCreatePipelineLayout(_device, &_createInfo, nullptr, &vkHandle));
}

PipelineLayout::PipelineLayout(VkDevice device, PipelineLayoutCreateInfo & createInfo): _device(device)
{
	getFuncPointers();

	auto _createInfo = createInfo.to_vktype();
	checkVKResult(_vkCreatePipelineLayout(_device, &_createInfo, nullptr, &vkHandle));
}

//PipelineLayout::PipelineLayout(PipelineLayout & other)
//{
//	if (other.isValid())
//	{
//		vkHandle = other.vkHandle;
//		_device = other._device;
//		_vkCreatePipelineLayout = other._vkCreatePipelineLayout;
//		_vkDestroyPipelineLayout = other._vkDestroyPipelineLayout;
//	}
//}

PipelineLayout::~PipelineLayout()
{
	if (isValid())
	{
		_vkDestroyPipelineLayout(_device, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = VK_NULL_HANDLE;
	}
}

bool PipelineLayout::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

void PipelineLayout::getFuncPointers()
{
	_vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)vkGetDeviceProcAddr(_device, "vkCreatePipelineLayout");
	_vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)vkGetDeviceProcAddr(_device, "vkDestroyPipelineLayout");
}

PipelineShaderStageCreateInfo::PipelineShaderStageCreateInfo()
{
}

PipelineShaderStageCreateInfo::PipelineShaderStageCreateInfo(VkShaderStageFlagBits shaderStage, ShaderModule *shaderModule, std::string &funcName) 
	:stage(shaderStage), module(shaderModule), name(funcName)
{
}

//PipelineShaderStageCreateInfo::PipelineShaderStageCreateInfo(PipelineShaderStageCreateInfo & other)
//{
//	stage = other.stage;
//	module = other.module;
//	name = other.name;
//}

PipelineShaderStageCreateInfo::~PipelineShaderStageCreateInfo()
{
}

VkPipelineShaderStageCreateInfo PipelineShaderStageCreateInfo::to_vktype()
{
	VkPipelineShaderStageCreateInfo out = {};
	out.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	out.stage = stage;
	out.module = module->vkHandle;
	out.pName = name.c_str();
	return out;
}

PipelineVertexInputStateCreateInfo::PipelineVertexInputStateCreateInfo()
{
}

//PipelineVertexInputStateCreateInfo::PipelineVertexInputStateCreateInfo(PipelineVertexInputStateCreateInfo &other)
//{
//	vertexAttributeDescriptions = other.vertexAttributeDescriptions;
//	vertexBindingDescriptions = other.vertexBindingDescriptions;
//}

PipelineVertexInputStateCreateInfo::~PipelineVertexInputStateCreateInfo()
{
}

VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateCreateInfo::to_vktype()
{
	VkPipelineVertexInputStateCreateInfo out = {};
	out.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	uint32_t vbdCount = static_cast<uint32_t>(vertexBindingDescriptions.size());
	if (vbdCount > 0)
	{
		out.vertexBindingDescriptionCount = vbdCount;
		out.pVertexBindingDescriptions = vertexBindingDescriptions.data();
	}
	else
	{
		out.vertexBindingDescriptionCount = 0;
	}

	uint32_t vadCount = static_cast<uint32_t>(vertexAttributeDescriptions.size());
	if (vadCount > 0)
	{
		out.vertexAttributeDescriptionCount = vadCount;
		out.pVertexAttributeDescriptions = vertexAttributeDescriptions.data();
	}
	else
	{
		out.vertexBindingDescriptionCount = 0;
	}

	return out;
}

PipelineInputAssemblyStateCreateInfo::PipelineInputAssemblyStateCreateInfo()
{
}

PipelineInputAssemblyStateCreateInfo::PipelineInputAssemblyStateCreateInfo(VkPrimitiveTopology primitiveTopology, VkBool32 enable): topology(primitiveTopology), primitiveRestartEnable(enable)
{
}

//PipelineInputAssemblyStateCreateInfo::PipelineInputAssemblyStateCreateInfo(PipelineInputAssemblyStateCreateInfo &other)
//{
//	topology = other.topology;
//	primitiveRestartEnable = other.primitiveRestartEnable;
//}

PipelineInputAssemblyStateCreateInfo::~PipelineInputAssemblyStateCreateInfo()
{
}

VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateCreateInfo::to_vktype()
{
	VkPipelineInputAssemblyStateCreateInfo out = {};
	out.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	out.topology = topology;
	out.primitiveRestartEnable = primitiveRestartEnable;
	return out;
}

PipelineViewportStateCreateInfo::PipelineViewportStateCreateInfo()
{
}

//PipelineViewportStateCreateInfo::PipelineViewportStateCreateInfo(PipelineViewportStateCreateInfo & other)
//{
//	viewports = other.viewports;
//	scissors = other.scissors;
//}

PipelineViewportStateCreateInfo::~PipelineViewportStateCreateInfo()
{
}

VkPipelineViewportStateCreateInfo PipelineViewportStateCreateInfo::to_vktype()
{
	VkPipelineViewportStateCreateInfo out = {};
	out.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

	uint32_t vpCount = static_cast<uint32_t>(viewports.size());
	if (vpCount > 0)
	{
		out.viewportCount = vpCount;
		out.pViewports = viewports.data();
		py::print("set viewports.");
	}
	else
	{
		out.viewportCount = 0;
	}

	uint32_t sCount = static_cast<uint32_t>(scissors.size());
	if (sCount > 0)
	{
		out.scissorCount = sCount;
		out.pScissors = scissors.data();
	}
	else
	{
		out.scissorCount = 0;
	}

	return out;
}

PipelineRasterizationStateCreateInfo::PipelineRasterizationStateCreateInfo()
{
}

//PipelineRasterizationStateCreateInfo::PipelineRasterizationStateCreateInfo(PipelineRasterizationStateCreateInfo & other)
//{
//	depthClampEnable = other.depthClampEnable;
//	rasterizerDiscardEnable = other.rasterizerDiscardEnable;
//	polygonMode = other.polygonMode;
//	cullMode = other.cullMode;
//	frontFace = other.frontFace;
//	depthBiasEnable = other.depthBiasEnable;
//	depthBiasConstantFactor = other.depthBiasConstantFactor;
//	depthBiasClamp = other.depthBiasClamp;
//	depthBiasSlopeFactor = other.depthBiasSlopeFactor;
//	lineWidth = other.lineWidth;
//}

PipelineRasterizationStateCreateInfo::~PipelineRasterizationStateCreateInfo()
{
}

VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateCreateInfo::to_vktype()
{
	VkPipelineRasterizationStateCreateInfo out = {};
	out.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	out.depthClampEnable = depthClampEnable;
	out.rasterizerDiscardEnable = rasterizerDiscardEnable;
	out.polygonMode = polygonMode;
	out.cullMode = cullMode;
	out.frontFace = frontFace;
	out.depthBiasEnable = depthBiasEnable;
	out.depthBiasConstantFactor = depthBiasConstantFactor;
	out.depthBiasClamp = depthBiasClamp;
	out.depthBiasSlopeFactor = depthBiasSlopeFactor;
	out.lineWidth = lineWidth;

	return out;
}

PipelineMultisampleStateCreateInfo::PipelineMultisampleStateCreateInfo()
{
}

//PipelineMultisampleStateCreateInfo::PipelineMultisampleStateCreateInfo(PipelineMultisampleStateCreateInfo & other)
//{
//	rasterizationSamples = other.rasterizationSamples;
//	sampleShadingEnable = other.sampleShadingEnable;
//	minSampleShading = other.minSampleShading;
//	sampleMask = other.sampleMask;
//	alphaToCoverageEnable = other.alphaToCoverageEnable;
//	alphaToOneEnable = other.alphaToOneEnable;
//}

PipelineMultisampleStateCreateInfo::~PipelineMultisampleStateCreateInfo()
{
}

VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateCreateInfo::to_vktype()
{
	VkPipelineMultisampleStateCreateInfo out = {};
	out.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	out.rasterizationSamples = rasterizationSamples;
	out.sampleShadingEnable = sampleShadingEnable;
	out.minSampleShading = minSampleShading;
	out.pSampleMask = &sampleMask;
	out.alphaToCoverageEnable = alphaToCoverageEnable;
	out.alphaToOneEnable = alphaToOneEnable;
	return out;
}

PipelineColorBlendStateCreateInfo::PipelineColorBlendStateCreateInfo()
{
}

//PipelineColorBlendStateCreateInfo::PipelineColorBlendStateCreateInfo(PipelineColorBlendStateCreateInfo & other)
//{
//	logicOpEnable = other.logicOpEnable;
//	logicOp = other.logicOp;
//	attachments = other.attachments;
//	blendConstants = other.blendConstants;
//}

PipelineColorBlendStateCreateInfo::~PipelineColorBlendStateCreateInfo()
{
}

VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateCreateInfo::to_vktype()
{
	VkPipelineColorBlendStateCreateInfo out = {};
	out.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	out.logicOpEnable = logicOpEnable;
	out.logicOp = logicOp;
	out.blendConstants[0] = blendConstants[0];
	out.blendConstants[1] = blendConstants[1];
	out.blendConstants[2] = blendConstants[2];
	out.blendConstants[3] = blendConstants[3];

	uint32_t attachmentCount = static_cast<uint32_t>(attachments.size());
	if (attachmentCount > 0)
	{
		out.attachmentCount = attachmentCount;
		out.pAttachments = attachments.data();
	}
	else
	{
		out.attachmentCount = 0;
	}
	return out;
}

PipelineLayoutCreateInfo::PipelineLayoutCreateInfo()
{
}

PipelineLayoutCreateInfo::~PipelineLayoutCreateInfo()
{
}

VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo::to_vktype()
{
	VkPipelineLayoutCreateInfo out = {};
	out.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	out.setLayoutCount = 0;
	
	uint32_t pushConstantRangeCount = static_cast<uint32_t>(pushConstantRanges.size());
	if (pushConstantRangeCount > 0)
	{
		out.pushConstantRangeCount = pushConstantRangeCount;
		out.pPushConstantRanges = pushConstantRanges.data();
	}
	else
	{
		out.pushConstantRangeCount = 0;
	}

	return out;
}

Pipeline::Pipeline()
{
}

//Pipeline::Pipeline(Pipeline & other)
//{
//	if (other.isValid())
//	{
//		vkHandle = other.vkHandle;
//		_device = other._device;
//		_vkDestroyPipeline = other._vkDestroyPipeline;
//	}
//}

Pipeline::~Pipeline()
{
	if (isValid() && _vkDestroyPipeline != nullptr && _device != VK_NULL_HANDLE)
	{
		_vkDestroyPipeline(_device, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = VK_NULL_HANDLE;
		_vkDestroyPipeline = nullptr;
	}
}

bool Pipeline::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

GraphicsPipelineCreateInfo::GraphicsPipelineCreateInfo()
{
}

GraphicsPipelineCreateInfo::~GraphicsPipelineCreateInfo()
{
}

VkGraphicsPipelineCreateInfo GraphicsPipelineCreateInfo::to_vktype()
{
	VkGraphicsPipelineCreateInfo out = {};
	out.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	if (vertexInputState != nullptr)
		out.pVertexInputState = &vertexInputState->to_vktype();
	if (inputAssemblyState != nullptr)
		out.pInputAssemblyState = &inputAssemblyState->to_vktype();
	if (viewportState != nullptr)
	{
		auto vps = viewportState->to_vktype();
		py::print((int)vps.sType);
		out.pViewportState = &vps;
		py::print((int)out.pViewportState->sType);
	}
	if (rasterizationState != nullptr)
		out.pRasterizationState = &rasterizationState->to_vktype();
	if (multisampleState != nullptr)
		out.pMultisampleState = &multisampleState->to_vktype();
	if (colorBlendState != nullptr)
		out.pColorBlendState = &colorBlendState->to_vktype();
	out.layout = layout->vkHandle;
	out.renderPass = renderPass->vkHandle;
	if (basePipelineHandle != nullptr)
		out.basePipelineHandle = basePipelineHandle->vkHandle;
	else
		out.basePipelineHandle = VK_NULL_HANDLE;
	out.subpass = subpass;
	out.basePipelineIndex = basePipelineIndex;

	uint32_t stageCount = static_cast<uint32_t>(stages.size());
	if (stageCount > 0)
	{
		out.stageCount = stageCount;
		std::vector<VkPipelineShaderStageCreateInfo> _stages;
		for (auto item : stages)
			_stages.emplace_back(item->to_vktype());
		out.pStages = _stages.data();
	}
	else
		out.stageCount = 0;

	return out;
}

PipelineCache::PipelineCache()
{
}

PipelineCache::~PipelineCache()
{
}

bool PipelineCache::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
