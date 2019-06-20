#pragma once

#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "volk.h"

namespace py = pybind11;

#ifndef RENDERPASS_H
#define RENDERPASS_H



class SubpassDescription
{
public:
	SubpassDescription();
	~SubpassDescription();

	VkSubpassDescription to_vktype();

	VkPipelineBindPoint pipelineBindPoint;
	std::vector<VkAttachmentReference> inputAttachments;
	std::vector<VkAttachmentReference> colorAttachments;
	std::vector<VkAttachmentReference> resolveAttachments;
	VkAttachmentReference* depthStencilAttachment = nullptr;
	std::vector<uint32_t> preserveAttachments;
};


class RenderPassCreateInfo
{
public:
	RenderPassCreateInfo();
	~RenderPassCreateInfo();

	VkRenderPassCreateInfo to_vktype();

	std::vector<VkAttachmentDescription> attachments;
	std::vector<SubpassDescription> subpasses;
	std::vector<VkSubpassDependency> dependencies;
};


class RenderPass
{
public:
	RenderPass();
	RenderPass(VkDevice device, RenderPassCreateInfo &createInfo);
	RenderPass(RenderPass &other);
	~RenderPass();

	bool isValid();

	VkRenderPass vkHandle = VK_NULL_HANDLE;
private:
	VkDevice _device = VK_NULL_HANDLE;

	PFN_vkCreateRenderPass _vkCreateRenderPass = nullptr;
	PFN_vkDestroyRenderPass _vkDestroyRenderPass = nullptr;
};



#endif // !RENDERPASS_H

