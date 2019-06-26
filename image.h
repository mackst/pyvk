#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "volk.h"


namespace py = pybind11;


class Device;
class ImageViewCreateInfo;


#ifndef VKTYPES_H
#define VKTYPES_H


class ImageView
{
public:
	ImageView();
	ImageView(Device * device, ImageViewCreateInfo &createInfo);
	~ImageView();

	bool create(ImageViewCreateInfo &createInfo);

	bool isValid();

	VkImageView vkHandle = VK_NULL_HANDLE;

	
private:
	Device *_device = nullptr;
};



class Image
{
public:
	Image();
	~Image();

	bool isValid();

	VkImage vkHandle = VK_NULL_HANDLE;
};




#endif // !VKTYPES_H

