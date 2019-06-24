#pragma once

#include <string>

#include "volk.h"



VkExtent2D* getExtent2D(uint32_t width, uint32_t height);
VkExtent3D* getExtent3D(uint32_t width, uint32_t height, uint32_t depth);

VkOffset2D* getOffset2D(int x, int y);
VkOffset3D* getOffset3D(int x, int y, int z);

std::string extent2DToString(VkExtent2D &extent);
std::string extent3DToString(VkExtent3D &extent);

std::string offset2DToString(VkOffset2D &offset);
std::string offset3DToString(VkOffset3D &offset);

VkRect2D* getRect2D(VkOffset2D &offset, VkExtent2D &extent);
std::string rect2DToString(VkRect2D &rect);

VkViewport* getViewport(float x, float y, float width, float height, float minDepth, float maxDepth);
std::string viewportToString(VkViewport &viewport);

