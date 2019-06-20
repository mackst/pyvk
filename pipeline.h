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


class PipelineShaderStageCreateInfo
{
public:
	PipelineShaderStageCreateInfo();
	PipelineShaderStageCreateInfo(VkShaderStageFlagBits shaderStage, ShaderModule *shaderModule, std::string &funcName);
	//PipelineShaderStageCreateInfo(PipelineShaderStageCreateInfo &other);
	~PipelineShaderStageCreateInfo();

	VkPipelineShaderStageCreateInfo to_vktype();

	VkShaderStageFlagBits stage;
	ShaderModule *module = nullptr;
	std::string name;
};


class PipelineVertexInputStateCreateInfo
{
public:
	PipelineVertexInputStateCreateInfo();
	//PipelineVertexInputStateCreateInfo(PipelineVertexInputStateCreateInfo&);
	~PipelineVertexInputStateCreateInfo();

	VkPipelineVertexInputStateCreateInfo to_vktype();

	std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions;
	std::vector<VkVertexInputAttributeDescription> vertexAttributeDescriptions;
};


class PipelineInputAssemblyStateCreateInfo
{
public:
	PipelineInputAssemblyStateCreateInfo();
	PipelineInputAssemblyStateCreateInfo(VkPrimitiveTopology primitiveTopology, VkBool32 enable);
	//PipelineInputAssemblyStateCreateInfo(PipelineInputAssemblyStateCreateInfo&);
	~PipelineInputAssemblyStateCreateInfo();

	VkPipelineInputAssemblyStateCreateInfo to_vktype();

	VkPrimitiveTopology                        topology;
	VkBool32                                   primitiveRestartEnable;
};


class PipelineViewportStateCreateInfo
{
public:
	PipelineViewportStateCreateInfo();
	//PipelineViewportStateCreateInfo(PipelineViewportStateCreateInfo &other);
	~PipelineViewportStateCreateInfo();

	VkPipelineViewportStateCreateInfo to_vktype();

	std::vector<VkViewport> viewports;
	std::vector<VkRect2D> scissors;
};


class PipelineRasterizationStateCreateInfo
{
public:
	PipelineRasterizationStateCreateInfo();
	//PipelineRasterizationStateCreateInfo(PipelineRasterizationStateCreateInfo &other);
	~PipelineRasterizationStateCreateInfo();

	VkPipelineRasterizationStateCreateInfo to_vktype();

	VkBool32                                   depthClampEnable;
	VkBool32                                   rasterizerDiscardEnable;
	VkPolygonMode                              polygonMode;
	VkCullModeFlagBits                         cullMode;
	VkFrontFace                                frontFace;
	VkBool32                                   depthBiasEnable;
	float                                      depthBiasConstantFactor;
	float                                      depthBiasClamp;
	float                                      depthBiasSlopeFactor;
	float                                      lineWidth;
};


class PipelineMultisampleStateCreateInfo
{
public:
	PipelineMultisampleStateCreateInfo();
	//PipelineMultisampleStateCreateInfo(PipelineMultisampleStateCreateInfo &other);
	~PipelineMultisampleStateCreateInfo();

	VkPipelineMultisampleStateCreateInfo to_vktype();

	VkSampleCountFlagBits rasterizationSamples;
	VkBool32 sampleShadingEnable;
	float minSampleShading;
	uint32_t sampleMask;
	VkBool32 alphaToCoverageEnable;
	VkBool32 alphaToOneEnable;
};


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

