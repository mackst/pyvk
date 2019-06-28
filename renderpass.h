#pragma once

#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "volk.h"

namespace py = pybind11;


class Device;


#ifndef RENDERPASS_H
#define RENDERPASS_H



class SubpassDescription
{
public:
	SubpassDescription();
	~SubpassDescription();

	void getVKStruct(VkSubpassDescription *info);

	VkPipelineBindPoint pipelineBindPoint;
	std::vector<VkAttachmentReference> inputAttachments = {};
	std::vector<VkAttachmentReference> colorAttachments = {};
	std::vector<VkAttachmentReference> resolveAttachments = {};
	VkAttachmentReference* depthStencilAttachment = nullptr;
	std::vector<uint32_t> preserveAttachments = {};
};


class RenderPassCreateInfo
{
public:
	RenderPassCreateInfo();
	~RenderPassCreateInfo();

	void setSubpasses(std::vector<SubpassDescription> &descriptions);
	std::vector<SubpassDescription> getSubpasses() { return subpasses; }

	void getVKStruct(VkRenderPassCreateInfo *info);

	const void* pNext = nullptr;
	std::vector<VkAttachmentDescription> attachments;
	std::vector<SubpassDescription> subpasses;
	std::vector<VkSubpassDescription> _subpasses = {};
	std::vector<VkSubpassDependency> dependencies;
};


class RenderPass
{
public:
	RenderPass();
	RenderPass(Device *device, RenderPassCreateInfo &createInfo);
	~RenderPass();

	bool isValid();

	VkRenderPass vkHandle = VK_NULL_HANDLE;
	Device *_device = nullptr;

};



#endif // !RENDERPASS_H

