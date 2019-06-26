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
