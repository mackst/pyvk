#include "shadermodule.h"
#include "exception.h"
#include "utils.h"
#include "device.h"

ShaderModule::ShaderModule()
{
}

ShaderModule::ShaderModule(Device *device, const std::string & filename) : _device(device)
{
	auto code = readFile(filename);

	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	checkVKResult(_device->table.vkCreateShaderModule(_device->vkHandle, &createInfo, nullptr, &vkHandle));
}

ShaderModule::~ShaderModule()
{
	if (isValid())
	{
		_device->table.vkDestroyShaderModule(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = VK_NULL_HANDLE;
	}
	py::print("destroy shader module.");
}

bool ShaderModule::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}