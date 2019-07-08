#include "vktypes.h"

VkExtent2D * getExtent2D(uint32_t width, uint32_t height)
{
	VkExtent2D *out = new VkExtent2D();
	out->width = width;
	out->height = height;
	return out;
}

VkExtent3D * getExtent3D(uint32_t width, uint32_t height, uint32_t depth)
{
	VkExtent3D *out = new VkExtent3D();
	out->width = width;
	out->height = height;
	out->depth = depth;
	return out;
}

VkOffset2D * getOffset2D(int x, int y)
{
	VkOffset2D *out = new VkOffset2D();
	out->x = x;
	out->y = y;
	return out;
}

VkOffset3D * getOffset3D(int x, int y, int z)
{
	VkOffset3D *out = new VkOffset3D();
	out->x = x;
	out->y = y;
	out->z = z;
	return out;
}

std::string extent2DToString(VkExtent2D & extent)
{
	std::string a = "<Extent2D( width = " + std::to_string(extent.width) 
		+ ", height = " + std::to_string(extent.height) + ")>";
	return a;
}

std::string extent3DToString(VkExtent3D & extent)
{
	std::string a = "<Extent3D( width = " + std::to_string(extent.width)
		+ ", height = " + std::to_string(extent.height) 
		+ ", depth = " + std::to_string(extent.depth) + ")>";
	return a;
}

std::string offset2DToString(VkOffset2D & offset)
{
	std::string a = "<Offset2D( x = " + std::to_string(offset.x)
		+ ", y = " + std::to_string(offset.y) + ")>";
	return a;
}

std::string offset3DToString(VkOffset3D & offset)
{
	std::string a = "<Offset3D( x = " + std::to_string(offset.x)
		+ ", y = " + std::to_string(offset.y)
		+ ", z = " + std::to_string(offset.z) + ")>";
	return a;
}

VkRect2D * getRect2D(VkOffset2D & offset, VkExtent2D & extent)
{
	VkRect2D *out = new VkRect2D();
	out->extent = extent;
	out->offset = offset;
	return out;
}

std::string rect2DToString(VkRect2D & rect)
{
	std::string a = "<Rect2D( offset = " + offset2DToString(rect.offset) + ", extent = " + extent2DToString(rect.extent) + ")>";
	return a;
}

VkViewport * getViewport(float x, float y, float width, float height, float minDepth, float maxDepth)
{
	VkViewport *out = new VkViewport();
	out->x = x;
	out->y = y;
	out->width = width;
	out->height = height;
	out->maxDepth = maxDepth;
	out->minDepth = minDepth;
	return out;
}

std::string viewportToString(VkViewport & viewport)
{
	std::string a = "<Viewport( x=" + std::to_string(viewport.x) + 
		", y=" + std::to_string(viewport.y) + 
		", width=" + std::to_string(viewport.width) + 
		", height=" + std::to_string(viewport.height) +
		", minDepth=" + std::to_string(viewport.minDepth) +
		", maxDepth=" + std::to_string(viewport.maxDepth) + " )>";
	return a;
}

std::vector<VkMemoryType> getPhysicalDeviceMemoryTypes(VkPhysicalDeviceMemoryProperties & properties)
{
	std::vector<VkMemoryType> out;
	for (auto i = 0; i < properties.memoryTypeCount; i++)
		out.emplace_back(properties.memoryTypes[i]);
	return out;
}

std::vector<VkMemoryHeap> getPhysicalDeviceMemoryHeaps(VkPhysicalDeviceMemoryProperties & properties)
{
	std::vector<VkMemoryHeap> out;
	for (auto i = 0; i < properties.memoryHeapCount; i++)
		out.emplace_back(properties.memoryHeaps[i]);
	return out;
}

void setPhysicalDeviceMemoryTypes(VkPhysicalDeviceMemoryProperties & properties, std::vector<VkMemoryType>& mts)
{
	properties.memoryTypeCount = static_cast<uint32_t>(mts.size());
	for (auto i = 0; i < properties.memoryTypeCount; i++)
		properties.memoryTypes[i] = mts[i];
}

void setPhysicalDeviceMemoryHeaps(VkPhysicalDeviceMemoryProperties & properties, std::vector<VkMemoryHeap>& mhs)
{
	properties.memoryHeapCount = static_cast<uint32_t>(mhs.size());
	for (auto i = 0; i < properties.memoryHeapCount; i++)
		properties.memoryHeaps[i] = mhs[i];
}
