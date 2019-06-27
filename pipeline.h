#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#include "volk.h"
#include "shadermodule.h"
#include "renderpass.h"

namespace py = pybind11;


class Device;
class PipelineLayoutCreateInfo;



#ifndef PIPELINE_H
#define PIPELINE_H



class PipelineLayout
{
public:
	PipelineLayout();
	//PipelineLayout(Device *device, PipelineLayoutCreateInfo &createInfo);
	~PipelineLayout();

	bool isValid();

	VkPipelineLayout vkHandle = VK_NULL_HANDLE;

	Device *_device = nullptr;

};


class Pipeline
{
public:
	Pipeline();
	~Pipeline();

	bool isValid();

	VkPipeline vkHandle = VK_NULL_HANDLE;
	Device *_device = nullptr;
};


class PipelineCache
{
public:
	PipelineCache();
	~PipelineCache();

	bool isValid();

	VkPipelineCache vkHandle = VK_NULL_HANDLE;
};



#endif // !PIPELINE_H

