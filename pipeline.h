#pragma once

#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "volk.h"
#include "shadermodule.h"
#include "renderpass.h"

namespace py = pybind11;


#ifndef PIPELINE_H
#define PIPELINE_H





class PipelineColorBlendStateCreateInfo
{
public:
	PipelineColorBlendStateCreateInfo();
	//PipelineColorBlendStateCreateInfo(PipelineColorBlendStateCreateInfo &other);
	~PipelineColorBlendStateCreateInfo();

	VkPipelineColorBlendStateCreateInfo to_vktype();

	VkBool32 logicOpEnable;
	VkLogicOp logicOp;
	std::vector<VkPipelineColorBlendAttachmentState> attachments;
	std::vector<float> blendConstants;
};


class PipelineLayoutCreateInfo
{
public:
	PipelineLayoutCreateInfo();
	~PipelineLayoutCreateInfo();

	VkPipelineLayoutCreateInfo to_vktype();

	py::list setLayouts;
	std::vector<VkPushConstantRange> pushConstantRanges;
};




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




class GraphicsPipelineCreateInfo
{
public:
	GraphicsPipelineCreateInfo();
	~GraphicsPipelineCreateInfo();

	VkGraphicsPipelineCreateInfo to_vktype();

	std::vector<PipelineShaderStageCreateInfo*> stages;
	PipelineVertexInputStateCreateInfo *vertexInputState = nullptr;
	PipelineInputAssemblyStateCreateInfo *inputAssemblyState = nullptr;
	PipelineViewportStateCreateInfo *viewportState = nullptr;
	PipelineRasterizationStateCreateInfo *rasterizationState = nullptr;
	PipelineMultisampleStateCreateInfo *multisampleState = nullptr;
	PipelineColorBlendStateCreateInfo *colorBlendState = nullptr;
	PipelineLayout *layout = nullptr;
	RenderPass *renderPass = nullptr;
	uint32_t subpass;
	Pipeline *basePipelineHandle = nullptr;
	int32_t basePipelineIndex;
};





#endif // !PIPELINE_H

