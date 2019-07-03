#pragma once

#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "volk.h"

namespace py = pybind11;


class Device;
class ImageView;


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


class FramebufferCreateInfo
{
public:
	FramebufferCreateInfo();
	~FramebufferCreateInfo();

	void setAttachments(std::vector<ImageView*> &imageViews);
	std::vector<ImageView*> getAttachments() { return attachments; }

	void getVKStruct(VkFramebufferCreateInfo *info);

	const void* pNext = nullptr;
	VkFramebufferCreateFlags flags = 0;
	RenderPass *renderPass = nullptr;
	std::vector<ImageView*> attachments = {};
	std::vector<VkImageView> _attachments = {};
	uint32_t width = 0;
	uint32_t height = 0;
	uint32_t layers = 0;
};


class Framebuffer
{
public:
	Framebuffer();
	Framebuffer(Device *device, FramebufferCreateInfo &createInfo);
	~Framebuffer();

	bool isValid();

	VkFramebuffer vkHandle = VK_NULL_HANDLE;
	Device *_device = nullptr;
};




#endif // !RENDERPASS_H

