#include "renderpass.h"
#include "exception.h"

SubpassDescription::SubpassDescription()
{
}

SubpassDescription::~SubpassDescription()
{
}

VkSubpassDescription SubpassDescription::to_vktype()
{
	VkSubpassDescription out = {};
	out.pipelineBindPoint = pipelineBindPoint;

	uint32_t inputAttachmentCount = static_cast<uint32_t>(inputAttachments.size());
	if (inputAttachmentCount > 0)
	{
		out.inputAttachmentCount = inputAttachmentCount;
		out.pInputAttachments = inputAttachments.data();
	}
	else
	{
		out.inputAttachmentCount = 0;
	}

	uint32_t colorAttachmentCount = static_cast<uint32_t>(colorAttachments.size());
	if (colorAttachmentCount > 0)
	{
		out.colorAttachmentCount = colorAttachmentCount;
		out.pColorAttachments = colorAttachments.data();
	}
	else
	{
		out.colorAttachmentCount = 0;
	}

	if (resolveAttachments.size() > 0)
		out.pResolveAttachments = resolveAttachments.data();
	
	if (depthStencilAttachment != nullptr)
		out.pDepthStencilAttachment = depthStencilAttachment;

	uint32_t preserveAttachmentCount = static_cast<uint32_t>(preserveAttachments.size());
	if (preserveAttachmentCount > 0)
	{
		out.preserveAttachmentCount = preserveAttachmentCount;
		out.pPreserveAttachments = preserveAttachments.data();
	}
	else
	{
		out.preserveAttachmentCount = 0;
	}

	return out;
}

RenderPassCreateInfo::RenderPassCreateInfo()
{
}

RenderPassCreateInfo::~RenderPassCreateInfo()
{
}

VkRenderPassCreateInfo RenderPassCreateInfo::to_vktype()
{
	VkRenderPassCreateInfo out = {};
	out.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

	uint32_t attachmentCount = static_cast<uint32_t>(attachments.size());
	if (attachmentCount > 0)
	{
		out.attachmentCount = attachmentCount;
		out.pAttachments = attachments.data();
	}
	else
	{
		out.attachmentCount = 0;
	}

	uint32_t subpassCount = static_cast<uint32_t>(subpasses.size());
	if (subpassCount > 0)
	{
		out.subpassCount = subpassCount;

		std::vector<VkSubpassDescription> _subpasses(subpassCount);
		for (auto item : subpasses)
			_subpasses.push_back(item.to_vktype());
		out.pSubpasses = _subpasses.data();
	}
	else
	{
		out.subpassCount = 0;
	}

	uint32_t dependencyCount = static_cast<uint32_t>(dependencies.size());
	if (dependencyCount > 0)
	{
		out.dependencyCount = dependencyCount;
		out.pDependencies = dependencies.data();
	}
	else
	{
		out.dependencyCount = 0;
	}

	return out;
}

RenderPass::RenderPass()
{
}

RenderPass::RenderPass(VkDevice device, RenderPassCreateInfo & createInfo): _device(device)
{
	if (_device == VK_NULL_HANDLE)
		throw std::runtime_error("VKDevice has been destroyed");
	_vkCreateRenderPass = (PFN_vkCreateRenderPass)vkGetDeviceProcAddr(_device, "vkCreateRenderPass");
	_vkDestroyRenderPass = (PFN_vkDestroyRenderPass)vkGetDeviceProcAddr(_device, "vkDestroyRenderPass");

	auto _createInfo = createInfo.to_vktype();
	checkVKResult(_vkCreateRenderPass(_device, &_createInfo, nullptr, &vkHandle));
}

RenderPass::RenderPass(RenderPass & other)
{
	if (other.isValid())
	{
		vkHandle = other.vkHandle;
		_device = other._device;
		_vkCreateRenderPass = other._vkCreateRenderPass;
		_vkDestroyRenderPass = other._vkDestroyRenderPass;
	}
}

RenderPass::~RenderPass()
{
	if (isValid())
	{
		_vkDestroyRenderPass(_device, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = VK_NULL_HANDLE;
	}
}

bool RenderPass::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
