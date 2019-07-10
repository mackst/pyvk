#include "image.h"
#include "device.h"
#include "exception.h"


Image::Image()
{
}

Image::~Image()
{
	if (isValid())
	{
		_device->table.vkDestroyImage(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
	}
}

bool Image::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

ImageView::ImageView()
{
}

ImageView::ImageView(Device *device, ImageViewCreateInfo &createInfo) : _device(device)
{
	create(createInfo);
}

ImageView::~ImageView()
{
	if (isValid())
	{
		_device->table.vkDestroyImageView(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = VK_NULL_HANDLE;
	}
}

bool ImageView::create(ImageViewCreateInfo &createInfo)
{
	VkImageViewCreateInfo _createInfo = {};
	createInfo.getVKStruct(&_createInfo);

	checkVKResult(_device->table.vkCreateImageView(_device->vkHandle, &_createInfo, nullptr, &vkHandle));

	return true;
}

bool ImageView::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}

Sampler::Sampler()
{
}

Sampler::~Sampler()
{
	if (isValid())
	{
		_device->table.vkDestroySampler(_device->vkHandle, vkHandle, nullptr);
		vkHandle = VK_NULL_HANDLE;
		_device = nullptr;
	}
}

bool Sampler::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
