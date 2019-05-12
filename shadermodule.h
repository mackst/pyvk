#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vulkan/vulkan.h>

namespace py = pybind11;


#ifndef SHADERMODULE_H
#define SHADERMODULE_H



class ShaderModule
{
public:
	ShaderModule();
	ShaderModule(VkDevice device, const std::string &filename);
	ShaderModule(ShaderModule &other);
	~ShaderModule();

	bool isValid();

	VkShaderModule vkHandle = VK_NULL_HANDLE;
private:
	VkDevice _device = VK_NULL_HANDLE;
	PFN_vkCreateShaderModule _vkCreateShaderModule = nullptr;
	PFN_vkDestroyShaderModule _vkDestroyShaderModule = nullptr;
};



#endif // !SHADERMODULE_H
