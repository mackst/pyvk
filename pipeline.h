#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#include "volk.h"
#include "shadermodule.h"
#include "renderpass.h"

namespace py = pybind11;

class PipelineLayoutCreateInfo;

#ifndef PIPELINE_H
#define PIPELINE_H



class PipelineLayout
{
public:
	PipelineLayout();
	PipelineLayout(VkDevice device, py::dict createInfo);
	PipelineLayout(VkDevice device, PipelineLayoutCreateInfo &createInfo);
	//PipelineLayout(PipelineLayout &other);
	~PipelineLayout();

	bool isValid();

	VkPipelineLayout vkHandle = VK_NULL_HANDLE;

protected:
	void getFuncPointers();

	PFN_vkCreatePipelineLayout _vkCreatePipelineLayout = nullptr;
	PFN_vkDestroyPipelineLayout _vkDestroyPipelineLayout = nullptr;

private:
	VkDevice _device = VK_NULL_HANDLE;

};


class Pipeline
{
public:
	Pipeline();
	//Pipeline(Pipeline &other);
	~Pipeline();

	bool isValid();

	VkPipeline vkHandle = VK_NULL_HANDLE;
	VkDevice _device = VK_NULL_HANDLE;
	PFN_vkDestroyPipeline _vkDestroyPipeline = nullptr;
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

