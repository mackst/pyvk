#include "pipeline.h"
#include "exception.h"

PipelineLayout::PipelineLayout()
{
}

PipelineLayout::PipelineLayout(VkDevice device, py::dict createInfo) : _device(device)
{
	getFuncPointers();

	py::list setLayoutList = createInfo["setLayouts"].cast<py::list>();
	py::list pushConstantRangeList = createInfo["pushConstantRanges"].cast<py::list>();

	VkPipelineLayoutCreateInfo _createInfo = {};
	_createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	_createInfo.setLayoutCount = 0;
	_createInfo.pushConstantRangeCount = 0;

	checkVKResult(_vkCreatePipelineLayout(_device, &_createInfo, nullptr, &vkHandle));
}

PipelineLayout::PipelineLayout(VkDevice device, PipelineLayoutCreateInfo & createInfo): _device(device)
{
	getFuncPointers();

	auto _createInfo = createInfo.to_vktype();
	checkVKResult(_vkCreatePipelineLayout(_device, &_createInfo, nullptr, &vkHandle));
}

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

PipelineShaderStageCreateInfo::PipelineShaderStageCreateInfo(ShaderModule *shaderModule, std::string &funcName) : module(shaderModule), name(funcName)
{
}

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
