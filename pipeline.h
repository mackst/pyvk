#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vulkan/vulkan.h>

namespace py = pybind11;


#ifndef PIPELINE_H
#define PIPELINE_H



class PipelineLayout
{
public:
	PipelineLayout();
	PipelineLayout(VkDevice device, py::dict createInfo);
	~PipelineLayout();

	bool isValid();

	VkPipelineLayout vkHandle = VK_NULL_HANDLE;
private:
	VkDevice _device = VK_NULL_HANDLE;

	PFN_vkCreatePipelineLayout _vkCreatePipelineLayout = nullptr;
	PFN_vkDestroyPipelineLayout _vkDestroyPipelineLayout = nullptr;

};





#endif // !PIPELINE_H

