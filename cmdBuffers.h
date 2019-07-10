#pragma once


#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "volk.h"


namespace py = pybind11;


class Device;
class DeviceQueue;
class CommandBufferBeginInfo;
class SubmitInfo;
class RenderPassBeginInfo;
class Fence;
class Pipeline;
class PipelineLayout;
class Buffer;
class DescriptorSet;


#ifndef CMDBUFFERS_H
#define CMDBUFFERS_H


class CommandPool
{
public:
	CommandPool();
	CommandPool(Device *device, VkCommandPoolCreateInfo &createInfo);
	~CommandPool();

	bool reset(VkCommandPoolResetFlags flags=0);

	bool isValid();

	VkCommandPool vkHandle = VK_NULL_HANDLE;
	Device *_device = nullptr;

};


class CommandBuffer
{
public:
	CommandBuffer();
	~CommandBuffer();

	bool begin(CommandBufferBeginInfo &info);
	bool end();

	CommandBuffer* beginRenderPass(RenderPassBeginInfo &renderPassBegin, VkSubpassContents contents);
	CommandBuffer* endRenderPass();
	CommandBuffer* executeCommands(std::vector<CommandBuffer*> &cmdBuffers);
	CommandBuffer* bindPipeline(VkPipelineBindPoint pipelineBindPoint, Pipeline *pipeline);
	CommandBuffer* bindVertexBuffer(uint32_t firstBinding, std::vector<Buffer*> _buffers, std::vector<VkDeviceSize> &_offsets);
	CommandBuffer* draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
	CommandBuffer* dispatch(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
	CommandBuffer* bindDescriptorSets(VkPipelineBindPoint pipelineBindPoint, PipelineLayout *layout, uint32_t firstSet, std::vector<DescriptorSet*> &descriptorSets, std::vector<uint32_t> &dynamicOffsets);

	bool isValid();

	VkCommandBuffer vkHandle = VK_NULL_HANDLE;
	Device *_device = nullptr;
	CommandPool *_cmdPool = nullptr;

};



#endif // !CMDBUFFERS_H


