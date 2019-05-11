#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vulkan/vulkan.h>


namespace py = pybind11;


#ifndef VKTYPES_H
#define VKTYPES_H


class ImageView
{
public:
	ImageView();
	ImageView(VkDevice device, py::dict creatInfo);
	~ImageView();

	bool create(py::dict creatInfo);

	bool isValid();

	VkImageView vkHandle = VK_NULL_HANDLE;

	
private:
	VkDevice _device = VK_NULL_HANDLE;
	PFN_vkCreateImageView _vkCreateImageView = nullptr;
	PFN_vkDestroyImageView _vkDestroyImageView = nullptr;
};



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

