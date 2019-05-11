
#include "image.h"
#include "exception.h"


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

ImageView::ImageView()
{
}

ImageView::ImageView(VkDevice device, py::dict creatInfo) : _device(device)
{
	_vkCreateImageView = (PFN_vkCreateImageView)vkGetDeviceProcAddr(_device, "vkCreateImageView");
	_vkDestroyImageView = (PFN_vkDestroyImageView)vkGetDeviceProcAddr(_device, "vkDestroyImageView");

	create(creatInfo);
}

ImageView::~ImageView()
{
	if (isValid())
	{
		if (_vkDestroyImageView != nullptr)
			_vkDestroyImageView(_device, vkHandle, nullptr);
		else
		{
			vkDestroyImageView(_device, vkHandle, nullptr);
		}
		vkHandle = VK_NULL_HANDLE;
		_device = VK_NULL_HANDLE;
	}
}

bool ImageView::create(py::dict creatInfo)
{
	if (_device == VK_NULL_HANDLE || _vkCreateImageView == nullptr)
		return false;

	Image im = creatInfo["image"].cast<Image>();

	VkImageViewCreateInfo _createInfo = {};
	_createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	_createInfo.image = im.vkHandle;
	_createInfo.viewType = creatInfo["viewType"].cast<VkImageViewType>();
	_createInfo.format = creatInfo["format"].cast<VkFormat>();
	_createInfo.components = creatInfo["components"].cast<VkComponentMapping>();
	_createInfo.subresourceRange = creatInfo["subresourceRange"].cast<VkImageSubresourceRange>();

	checkVKResult(_vkCreateImageView(_device, &_createInfo, nullptr, &vkHandle));

	return true;
}

bool ImageView::isValid()
{
	return vkHandle != VK_NULL_HANDLE;
}
