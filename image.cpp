#include "image.h"

Image::Image()
{
}

Image::~Image()
{
	if (isValid())
	{
		vkHandle = VK_NULL_HANDLE;
	}
}

bool Image::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
