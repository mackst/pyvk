#include "descriptors.h"
#include "device.h"
#include "exception.h"


DescriptorSetLayout::DescriptorSetLayout()
{
}

DescriptorSetLayout::~DescriptorSetLayout()
{
	if (isValid())
	{
		_device->table.vkDestroyDescriptorSetLayout(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
	}
}

bool DescriptorSetLayout::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

DescriptorPool::DescriptorPool()
{
}

DescriptorPool::~DescriptorPool()
{
	if (isValid())
	{
		_device->table.vkDestroyDescriptorPool(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
	}
}

bool DescriptorPool::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

DescriptorSet::DescriptorSet()
{
}

DescriptorSet::~DescriptorSet()
{
	if (isValid())
	{
		checkVKResult(_pool->_device->table.vkFreeDescriptorSets(_pool->_device->vkHandle, _pool->vkHandle, 1, &vkHandle));
		vkHandle = VK_NULL_HANDLE;
		_pool = nullptr;
	}
}

bool DescriptorSet::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
