#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "volk.h"


namespace py = pybind11;


class Device;


#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H


class DescriptorSetLayout
{
public:
	DescriptorSetLayout();
	~DescriptorSetLayout();

	bool isValid();
	
	VkDescriptorSetLayout vkHandle = VK_NULL_HANDLE;
	Device* _device = nullptr;
};


class DescriptorPool
{
public:
	DescriptorPool();
	~DescriptorPool();

	bool isValid();

	VkDescriptorPool vkHandle = VK_NULL_HANDLE;
	Device* _device = nullptr;
};


class DescriptorSet
{
public:
	DescriptorSet();
	~DescriptorSet();

	bool isValid();

	VkDescriptorSet vkHandle = VK_NULL_HANDLE;
	DescriptorPool* _pool = nullptr;
};



#endif // !DESCRIPTORS_H
