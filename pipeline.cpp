#include "pipeline.h"
#include "exception.h"

PipelineLayout::PipelineLayout()
{
}

PipelineLayout::PipelineLayout(VkDevice device, py::dict createInfo) : _device(device)
{
	_vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)vkGetDeviceProcAddr(_device, "vkCreatePipelineLayout");
	_vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)vkGetDeviceProcAddr(_device, "vkDestroyPipelineLayout");

	py::list setLayoutList = createInfo["setLayouts"].cast<py::list>();
	py::list pushConstantRangeList = createInfo["pushConstantRanges"].cast<py::list>();

	VkPipelineLayoutCreateInfo _createInfo = {};
	_createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	_createInfo.setLayoutCount = 0;
	_createInfo.pushConstantRangeCount = 0;

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
