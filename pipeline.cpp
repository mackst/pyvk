#include "pipeline.h"
#include "exception.h"
#include "device.h"

PipelineLayout::PipelineLayout()
{
}


PipelineLayout::~PipelineLayout()
{
	if (isValid())
	{
		_device->table.vkDestroyPipelineLayout(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = VK_NULL_HANDLE;
	}
}

bool PipelineLayout::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}



Pipeline::Pipeline()
{
}


Pipeline::~Pipeline()
{
	if (isValid())
	{
		_device->table.vkDestroyPipeline(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
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
