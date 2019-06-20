#pragma once
#include "volk.h"


#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H


class DescriptorSetLayout
{
public:
	DescriptorSetLayout();
	~DescriptorSetLayout();

	bool isValid();
	
	VkDescriptorSetLayout vkHandle = VK_NULL_HANDLE;

};




#endif // !DESCRIPTORS_H
