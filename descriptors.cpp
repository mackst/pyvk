#include "descriptors.h"

DescriptorSetLayout::DescriptorSetLayout()
{
}

DescriptorSetLayout::~DescriptorSetLayout()
{
	if (isValid())
	{
		vkHandle = VK_NULL_HANDLE;
	}
}

bool DescriptorSetLayout::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
