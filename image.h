#pragma once

#include <vulkan/vulkan.h>


#ifndef VKTYPES_H
#define VKTYPES_H



class Image
{
public:
	Image();
	~Image();

	bool isValid();

	VkImage vkHandle = VK_NULL_HANDLE;
private:

};




#endif // !VKTYPES_H

