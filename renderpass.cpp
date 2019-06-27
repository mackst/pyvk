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

	uint32_t inputAttachmentCount = static_cast<uint32_t>(inputAttachments.size());
	if (inputAttachmentCount > 0)
	{
		info->inputAttachmentCount = inputAttachmentCount;
		info->pInputAttachments = inputAttachments.data();
	}
	else
	{
		info->inputAttachmentCount = 0;
	}

	uint32_t colorAttachmentCount = static_cast<uint32_t>(colorAttachments.size());
	if (colorAttachmentCount > 0)
	{
		info->colorAttachmentCount = colorAttachmentCount;
		info->pColorAttachments = colorAttachments.data();
	}
	else
	{
		info->colorAttachmentCount = 0;
	}

	if (resolveAttachments.size() > 0)
		info->pResolveAttachments = resolveAttachments.data();
	
	if (depthStencilAttachment != nullptr)
		info->pDepthStencilAttachment = depthStencilAttachment;

	uint32_t preserveAttachmentCount = static_cast<uint32_t>(preserveAttachments.size());
	if (preserveAttachmentCount > 0)
	{
		info->preserveAttachmentCount = preserveAttachmentCount;
		info->pPreserveAttachments = preserveAttachments.data();
	}
	else
	{
		info->preserveAttachmentCount = 0;
	}
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

	uint32_t attachmentCount = static_cast<uint32_t>(attachments.size());
	if (attachmentCount > 0)
	{
		info->attachmentCount = attachmentCount;
		info->pAttachments = attachments.data();
	}
	else
	{
		info->attachmentCount = 0;
	}

	uint32_t subpassCount = static_cast<uint32_t>(_subpasses.size());
	if (subpassCount > 0)
	{
		info->subpassCount = subpassCount;
		info->pSubpasses = _subpasses.data();
	}
	else
	{
		info->subpassCount = 0;
	}

	uint32_t dependencyCount = static_cast<uint32_t>(dependencies.size());
	if (dependencyCount > 0)
	{
		info->dependencyCount = dependencyCount;
		info->pDependencies = dependencies.data();
	}
	else
	{
		info->dependencyCount = 0;
	}
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
