#include "shadermodule.h"
#include "exception.h"
#include "utils.h"

ShaderModule::ShaderModule()
{
}

ShaderModule::ShaderModule(VkDevice device, const std::string & filename) : _device(device)
{
	_vkCreateShaderModule = (PFN_vkCreateShaderModule)vkGetDeviceProcAddr(_device, "vkCreateShaderModule");
	_vkDestroyShaderModule = (PFN_vkDestroyShaderModule)vkGetDeviceProcAddr(_device, "vkDestroyShaderModule");

	auto code = readFile(filename);

	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	checkVKResult(_vkCreateShaderModule(_device, &createInfo, nullptr, &vkHandle));
}

//ShaderModule::ShaderModule(ShaderModule & other)
//{
//	if (other.isValid())
//	{
//		vkHandle = other.vkHandle;
//		_device = other._device;
//		_vkCreateShaderModule = other._vkCreateShaderModule;
//		_vkDestroyShaderModule = other._vkDestroyShaderModule;
//	}
//}

ShaderModule::~ShaderModule()
{
	if (isValid() || _vkDestroyShaderModule != nullptr)
	{
		_vkDestroyShaderModule(_device, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = VK_NULL_HANDLE;
	}
	py::print("destroy shader module.");
}

bool ShaderModule::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}