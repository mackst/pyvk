#pragma once

#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vulkan/vulkan.h>

#include "shadermodule.h"

namespace py = pybind11;


#ifndef PIPELINE_H
#define PIPELINE_H


class PipelineShaderStageCreateInfo
{
public:
	PipelineShaderStageCreateInfo();
	PipelineShaderStageCreateInfo(ShaderModule *shaderModule, std::string &funcName);
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
	~PipelineInputAssemblyStateCreateInfo();

	VkPipelineInputAssemblyStateCreateInfo to_vktype();

	VkPrimitiveTopology                        topology;
	VkBool32                                   primitiveRestartEnable;
};


class PipelineViewportStateCreateInfo
{
public:
	PipelineViewportStateCreateInfo();
	~PipelineViewportStateCreateInfo();

	VkPipelineViewportStateCreateInfo to_vktype();

	std::vector<VkViewport> viewports;
	std::vector<VkRect2D> scissors;
};


class PipelineRasterizationStateCreateInfo
{
public:
	PipelineRasterizationStateCreateInfo();
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
	~PipelineLayout();

	bool isValid();

	VkPipelineLayout vkHandle = VK_NULL_HANDLE;

protected:
	void getFuncPointers();

private:
	VkDevice _device = VK_NULL_HANDLE;

	PFN_vkCreatePipelineLayout _vkCreatePipelineLayout = nullptr;
	PFN_vkDestroyPipelineLayout _vkDestroyPipelineLayout = nullptr;

};





#endif // !PIPELINE_H

