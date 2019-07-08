#include "cmdBuffers.h"
#include "device.h"
#include "exception.h"


CommandPool::CommandPool()
{
}

CommandPool::CommandPool(Device * device, VkCommandPoolCreateInfo & createInfo)
	: _device(device)
{
	checkVKResult(_device->table.vkCreateCommandPool(_device->vkHandle, &createInfo, nullptr, &vkHandle));
}

CommandPool::~CommandPool()
{
	if (isValid())
	{
		_device->table.vkDestroyCommandPool(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
	}
}

bool CommandPool::reset(VkCommandPoolResetFlags flags)
{
	if (isValid())
	{
		auto result = _device->table.vkResetCommandPool(_device->vkHandle, vkHandle, flags);
		return result == VK_SUCCESS;
	}
	return false;
}

bool CommandPool::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

CommandBuffer::CommandBuffer()
{
}

CommandBuffer::~CommandBuffer()
{
	if (isValid())
	{
		_device->table.vkFreeCommandBuffers(_device->vkHandle, _cmdPool->vkHandle, 1, &vkHandle);
		vkHandle = VK_NULL_HANDLE;
		_cmdPool = nullptr;
		_device = nullptr;
	}
}

bool CommandBuffer::begin(CommandBufferBeginInfo & info)
{
	VkCommandBufferBeginInfo beginInfo = {};
	info.getVKStruct(&beginInfo);
	auto result = _device->table.vkBeginCommandBuffer(vkHandle, &beginInfo);
	checkVKResult(result);
	return result == VK_SUCCESS;
}

bool CommandBuffer::end()
{
	auto result = _device->table.vkEndCommandBuffer(vkHandle);
	checkVKResult(result);
	return result == VK_SUCCESS;
}

CommandBuffer* CommandBuffer::beginRenderPass(RenderPassBeginInfo & renderPassBegin, VkSubpassContents contents)
{
	VkRenderPassBeginInfo info = {};
	renderPassBegin.getVKStruct(&info);
	_device->table.vkCmdBeginRenderPass(vkHandle, &info, contents);
	return this;
}

CommandBuffer* CommandBuffer::endRenderPass()
{
	_device->table.vkCmdEndRenderPass(vkHandle);
	return this;
}

CommandBuffer* CommandBuffer::executeCommands(std::vector<CommandBuffer*>& cmdBuffers)
{
	std::vector<VkCommandBuffer> cmds;
	for (auto cmd : cmdBuffers)
	{
		cmds.emplace_back(cmd->vkHandle);
	}
	_device->table.vkCmdExecuteCommands(vkHandle, static_cast<uint32_t>(cmds.size()), cmds.data());
	return this;
}

CommandBuffer* CommandBuffer::bindPipeline(VkPipelineBindPoint pipelineBindPoint, Pipeline * pipeline)
{
	_device->table.vkCmdBindPipeline(vkHandle, pipelineBindPoint, pipeline->vkHandle);
	return this;
}

CommandBuffer * CommandBuffer::bindVertexBuffer(uint32_t firstBinding, std::vector<Buffer*> _buffers, std::vector<VkDeviceSize> &_offsets)
{
	std::vector<VkDeviceSize> offsets = _offsets;
	std::vector<VkBuffer> buffers;
	for (auto buf : _buffers)
		buffers.emplace_back(buf->vkHandle);
	_device->table.vkCmdBindVertexBuffers(vkHandle, firstBinding, static_cast<uint32_t>(_buffers.size()), buffers.data(), offsets.data());
	return this;
}

CommandBuffer* CommandBuffer::draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
{
	_device->table.vkCmdDraw(vkHandle, vertexCount, instanceCount, firstVertex, firstInstance);
	return this;
}

bool CommandBuffer::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
