#include "renderpass.h"
#include "exception.h"
#include "device.h"

SubpassDescription::SubpassDescription()
{
}

SubpassDescription::~SubpassDescription()
{
}

void SubpassDescription::getVKStruct(VkSubpassDescription *info)
{
	info->pipelineBindPoint = pipelineBindPoint;

	info->inputAttachmentCount = static_cast<uint32_t>(inputAttachments.size());
	if (info->inputAttachmentCount > 0)
		info->pInputAttachments = inputAttachments.data();

	info->colorAttachmentCount = static_cast<uint32_t>(colorAttachments.size());
	if (info->colorAttachmentCount > 0)
		info->pColorAttachments = colorAttachments.data();

	if (resolveAttachments.size() > 0)
		info->pResolveAttachments = resolveAttachments.data();
	
	if (depthStencilAttachment != nullptr)
		info->pDepthStencilAttachment = depthStencilAttachment;

	info->preserveAttachmentCount = static_cast<uint32_t>(preserveAttachments.size());
	if (info->preserveAttachmentCount > 0)
		info->pPreserveAttachments = preserveAttachments.data();
}

RenderPassCreateInfo::RenderPassCreateInfo()
{
}

RenderPassCreateInfo::~RenderPassCreateInfo()
{
	pNext = nullptr;
}

void RenderPassCreateInfo::setSubpasses(std::vector<SubpassDescription>& descriptions)
{
	subpasses = descriptions;
	for (auto i : subpasses)
	{
		VkSubpassDescription description = {};
		i.getVKStruct(&description);
		_subpasses.emplace_back(description);
	}
}

void RenderPassCreateInfo::getVKStruct(VkRenderPassCreateInfo *info)
{
	info->sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	info->pNext = pNext;

	info->attachmentCount = static_cast<uint32_t>(attachments.size());
	if (info->attachmentCount > 0)
		info->pAttachments = attachments.data();

	info->subpassCount = static_cast<uint32_t>(_subpasses.size());
	if (info->subpassCount > 0)
		info->pSubpasses = _subpasses.data();

	info->dependencyCount = static_cast<uint32_t>(dependencies.size());
	if (info->dependencyCount > 0)
		info->pDependencies = dependencies.data();
}

RenderPass::RenderPass()
{
}

RenderPass::RenderPass(Device *device, RenderPassCreateInfo & createInfo): _device(device)
{
	VkRenderPassCreateInfo _createInfo = {};
	createInfo.getVKStruct(&_createInfo);
	checkVKResult(_device->table.vkCreateRenderPass(_device->vkHandle, &_createInfo, nullptr, &vkHandle));
}


RenderPass::~RenderPass()
{
	if (isValid())
	{
		_device->table.vkDestroyRenderPass(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = VK_NULL_HANDLE;
	}
}

bool RenderPass::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

Framebuffer::Framebuffer()
{
}

Framebuffer::Framebuffer(Device * device, FramebufferCreateInfo & createInfo)
	: _device(device)
{
	VkFramebufferCreateInfo _createInfo = {};
	createInfo.getVKStruct(&_createInfo);
	checkVKResult(_device->table.vkCreateFramebuffer(_device->vkHandle, &_createInfo, nullptr, &vkHandle));
}

Framebuffer::~Framebuffer()
{
	if (isValid())
	{
		//py::print("in Framebuffer::~Framebuffer()");
		_device->table.vkDestroyFramebuffer(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = VK_NULL_HANDLE;
		//py::print("Framebuffer destroyed.");
	}
}

bool Framebuffer::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

FramebufferCreateInfo::FramebufferCreateInfo()
{
}

FramebufferCreateInfo::~FramebufferCreateInfo()
{
	renderPass = nullptr;
	pNext = nullptr;
}

void FramebufferCreateInfo::setAttachments(std::vector<ImageView*>& imageViews)
{
	_attachments.clear();
	attachments = imageViews;
	for (auto iv : attachments)
	{
		_attachments.emplace_back(iv->vkHandle);
	}
}

void FramebufferCreateInfo::getVKStruct(VkFramebufferCreateInfo * info)
{
	info->sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	info->pNext = pNext;
	info->flags = flags;
	info->attachmentCount = static_cast<uint32_t>(_attachments.size());
	if (info->attachmentCount > 0)
		info->pAttachments = _attachments.data();
	if (renderPass != nullptr)
		info->renderPass = renderPass->vkHandle;
	info->width = width;
	info->height = height;
	info->layers = layers;
}
