#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "volk.h"

namespace py = pybind11;


class Device;


#ifndef SHADERMODULE_H
#define SHADERMODULE_H



class ShaderModule
{
public:
	ShaderModule();
	ShaderModule(Device *device, const std::string &filename);
	~ShaderModule();

	bool isValid();

	VkShaderModule vkHandle = VK_NULL_HANDLE;
private:
	Device *_device = VK_NULL_HANDLE;
};



#endif // !SHADERMODULE_H
