#pragma once

#ifndef EXCEPTION_H
#define EXCEPTION_H



#include <string>
#include <vulkan/vulkan.h>


class OutOfHostMemory : public std::exception {
public:
	explicit OutOfHostMemory(const char * m) : message{ m } {}
	virtual const char * what() const noexcept override { return message.c_str(); }
private:
	std::string message = "";
};


class OutOfDeviceMemory : public std::exception {
public:
	explicit OutOfDeviceMemory(const char * m) : message{ m } {}
	virtual const char * what() const noexcept override { return message.c_str(); }
private:
	std::string message = "";
};


class InitializationFailed : public std::exception {
public:
	explicit InitializationFailed(const char * m) : message{ m } {}
	virtual const char * what() const noexcept override { return message.c_str(); }
private:
	std::string message = "";
};


class LayerNotPresent : public std::exception {
public:
	explicit LayerNotPresent(const char * m) : message{ m } {}
	virtual const char * what() const noexcept override { return message.c_str(); }
private:
	std::string message = "";
};


class ExtensionNotPresent : public std::exception {
public:
	explicit ExtensionNotPresent(const char * m) : message{ m } {}
	virtual const char * what() const noexcept override { return message.c_str(); }
private:
	std::string message = "";
};


class IncompatibleDriver : public std::exception {
public:
	explicit IncompatibleDriver(const char * m) : message{ m } {}
	virtual const char * what() const noexcept override { return message.c_str(); }
private:
	std::string message = "";
};


void checkVKResult(VkResult result);



#endif // !EXCEPTION_H
