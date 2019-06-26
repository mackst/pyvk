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
