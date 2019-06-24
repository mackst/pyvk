# -*- coding: UTF-8 -*-

import _vk
from PySide2 import (QtGui, QtCore)


validationLayers = [
    'VK_LAYER_KHRONOS_validation'
]

VK_EXT_DEBUG_UTILS_EXTENSION_NAME = 'VK_EXT_debug_utils'

enableValidationLayers = True



def debugCallback(messageSeverity, messageType, callbackData, userData):
    #print(messageSeverity, messageType, callbackData)
    print(callbackData.message)


class QueueFamilyIndices(object):

    def __init__(self):
        self.graphicsFamily = -1

    @property
    def isComplete(self):
        return self.graphicsFamily >= 0


class HelloTriangleApplication(QtGui.QWindow):

    def __init__(self):
        super(HelloTriangleApplication, self).__init__()

        self.setWidth(1280)
        self.setHeight(720)

        self.setTitle("Vulkan Python - PySide2")

        #self.setSurfaceType(self.OpenGLSurface)

        self.__instance = None
        self.__debugMessenger = None
        self.__physicalDevice = None

        self.initVulkan()

    def __del__(self):
        del self.__debugMessenger
        del self.__instance
        print('instance destroyed')

    def initVulkan(self):
        self.__cretaeInstance()
        self.__setupDebugCallback()
        self.__pickPhysicalDevice()

    def __cretaeInstance(self):
        createInfo = _vk.InstanceCreateInfo()
        createInfo.applicationInfo.applicationName = 'pyvkApp'
        createInfo.applicationInfo.engineName = 'pyvkEngine'
        createInfo.applicationInfo.engineVersion = _vk.makeVersion()
        createInfo.applicationInfo.applicationVersion = _vk.makeVersion()
        createInfo.applicationInfo.apiVersion = _vk.makeVersion()

        debugInfo = _vk.DebugUtilsMessengerCreateInfoEXT()
        messageSeverity = _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT #| _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
        debugInfo.messageSeverity = messageSeverity
        debugInfo.messageType = _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
        debugInfo.userCallback = debugCallback

        createInfo.pNext = debugInfo

        if enableValidationLayers:
            extensionNames = self.__getRequiredExtensions()
            #extensionNames = ['VK_LAYER_KHRONOS_validation', 'VK_KHR_get_surface_capabilities2', 'VK_KHR_surface', 'VK_KHR_win32_surface']
            createInfo.enabledExtensionNames = extensionNames
            createInfo.enabledLayerNames = validationLayers

        self.__instance = _vk.Instance(createInfo)
        print(self.__instance.isValid)

    def __setupDebugCallback(self):
        if not enableValidationLayers:
            return

        messageSeverity = _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
        messageType = _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | _vk.VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT

        createInfo = _vk.DebugUtilsMessengerCreateInfoEXT()
        createInfo.messageSeverity = messageSeverity
        createInfo.messageType = messageType
        createInfo.userCallback = debugCallback

        self.__debugMessenger = self.__instance.createDebugUtilsMessengerEXT(createInfo)
        print(self.__debugMessenger.isValid)

    def __pickPhysicalDevice(self):
        physicalDevices = self.__instance.getPhysicalDevices()

        for device in physicalDevices:
            if self.__isDeviceSuitable(device):
                self.__physicalDevice = device
                break

        assert self.__physicalDevice.isValid
        print(self.__physicalDevice)

        rayTracingProperties = _vk.PhysicalDeviceRayTracingPropertiesNV()
        rayTracingProperties.maxRecursionDepth = 0
        rayTracingProperties.shaderGroupHandleSize = 0

        properties2 = _vk.PhysicalDeviceProperties2()
        properties2.pNext = rayTracingProperties

        properties2 = self.__physicalDevice.getProperties2(properties2)

        print((rayTracingProperties.maxRecursionDepth, rayTracingProperties.shaderGroupHandleSize))

    def __isDeviceSuitable(self, device):
        indices = self.__findQueueFamilies(device)

        return indices.isComplete

    def __findQueueFamilies(self, device):
        indices = QueueFamilyIndices()

        for i, prop in enumerate(device.queueFamilyProperties):
            if prop.queueCount > 0 and prop.queueFlags & _vk.VK_QUEUE_GRAPHICS_BIT:
                indices.graphicsFamily = i

            if indices.isComplete:
                break

        return indices

    def __getRequiredExtensions(self):
        extensionNames = [e.extensionName for e in _vk.Instance.getExtensionProperties()]
        if enableValidationLayers:
            if VK_EXT_DEBUG_UTILS_EXTENSION_NAME not in extensionNames:
                extensionNames.append(VK_EXT_DEBUG_UTILS_EXTENSION_NAME)

        return extensionNames



if __name__ == '__main__':
    import sys

    app = QtGui.QGuiApplication(sys.argv)

    win = HelloTriangleApplication()
    win.show()

    def clenaup():
        global win
        del win

    app.aboutToQuit.connect(clenaup)

    sys.exit(app.exec_())
